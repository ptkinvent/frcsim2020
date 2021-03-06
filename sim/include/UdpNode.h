/**
 * Copyright (c) 2020 FRC Team 3260
 */

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


class UdpNode
{
public:
    /**
     * Constructor
     */
    UdpNode(uint16_t rxPort, const std::string& txIp, uint16_t txPort);

    /**
     * Destructor
     */
    ~UdpNode();

    /**
     * Send over UDP
     */
    void send(const std::string &msg);

    /**
     * Receive over UDP (max 1024 bytes)
     * @return Received message
     */
    std::string receive();

private:
    int _sockfd;
    struct sockaddr_in _rxAddr, _txAddr;
};
