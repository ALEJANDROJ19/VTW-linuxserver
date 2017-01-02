//
// Created by pau on 6/12/16.
//

#ifndef VTW_SERVER_LINUX_TCPSERVER_H
#define VTW_SERVER_LINUX_TCPSERVER_H

#define TCP_PORT 21211
#define BUFFLEN 1024

#include <stdlib.h>    //exit(0);
#include "../Portocol/HeaderDef.h"
#include "JsonHandler.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <ifaddrs.h>
#include <errno.h>
#include "/usr/include/python3.5/Python.h"

class tcpServer {

public:
    int createTCPServer();

private:
    void checkandSetKeepAlive();
    void receivedNewMessage(json_object*, char&);
    void ext(char*);
    char* getIpAddress();
    char* cleanBuffer(char[]);

    struct sockaddr_in server;
    int _Socket;
    char _Buffer[BUFFLEN];
    char* _IP;
    JsonHandler jsonHandler;
};


#endif //VTW_SERVER_LINUX_TCPSERVER_H
