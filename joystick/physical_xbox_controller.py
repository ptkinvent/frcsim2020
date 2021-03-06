#
# Copyright (c) 2020 FRC Team 3260
#

from lib.frc4564_xbox_python.xbox import Joystick
from comms import *
from threading import Thread


class CommsThread(Thread):
    def __init__(self, comms_config, controller_state, verbose):
        super(CommsThread, self).__init__()
        self.verbose = verbose
        self.comms = Comms(comms_config)
        self.controller_state = controller_state

    def run(self):
        while True:
            # Send controller state
            tx_msg = self.controller_state.toJson()
            self.comms.tx(tx_msg)
            if self.verbose:
                print tx_msg

            # Receive heartbeat
            rx_msg = self.comms.rx()
            if rx_msg is None:
                print "Disconnected"

    def join(self, **kwargs):
        Thread.join(self)


class PhysicalXboxController:
    def __init__(self, player, comms_config, verbose):
        self.joystick = Joystick()
        self.controller_state = ControllerState()

        # Launch comms thread
        self.comms = CommsThread(comms_config, self.controller_state, verbose)
        self.comms.daemon = True
        self.comms.start()
        print "Controller: Launched player", player

        # Run indefinitely
        self.run()

    def run(self):
        try:
            while True:
                (left_joystick_x, left_joystick_y) = self.joystick.leftStick()
                (right_joystick_x, right_joystick_y) = self.joystick.rightStick()
                self.controller_state.left_joystick.x = int(left_joystick_x * 512)
                self.controller_state.left_joystick.y = int(left_joystick_y * 512)
                self.controller_state.right_joystick.x = int(right_joystick_x * 512)
                self.controller_state.right_joystick.y = int(right_joystick_y * 512)
                self.controller_state.dpad.up.pressed = self.joystick.dpadUp()
                self.controller_state.dpad.down.pressed = self.joystick.dpadDown()
                self.controller_state.dpad.left.pressed = self.joystick.dpadLeft()
                self.controller_state.dpad.right.pressed = self.joystick.dpadRight()
                self.controller_state.left_trigger.value = int(self.joystick.leftTrigger() * 512)
                self.controller_state.right_trigger.value = int(self.joystick.rightTrigger() * 512)
                self.controller_state.left_bumper.pressed = self.joystick.leftBumper()
                self.controller_state.right_bumper.pressed = self.joystick.rightBumper()
                self.controller_state.a.pressed = self.joystick.A()
                self.controller_state.b.pressed = self.joystick.B()
                self.controller_state.x.pressed = self.joystick.X()
                self.controller_state.y.pressed = self.joystick.Y()
                self.controller_state.start.pressed = self.joystick.Start()
                self.controller_state.guide.pressed = self.joystick.Guide()
                self.controller_state.back.pressed = self.joystick.Back()
        except KeyboardInterrupt:
            self.joystick.close()
