/**
 * Storage class for holding parameters to be received from the robot
 */
public class RobotState
{
    public int leftDriveEncoderPosition; // Integer from 0-1024
    public int rightDriveEncoderPosition; // Integer from 0-1024
    public int elevatorEncoderPos; // Integer from 0-1024

    public void fromJson(String str)
    {
        leftDriveEncoderPosition = Integer.parseInt(str.substring(2, 7));
        rightDriveEncoderPosition = Integer.parseInt(str.substring(8, 13));
        elevatorEncoderPos = Integer.parseInt(str.substring(14, 19));
    }
}
