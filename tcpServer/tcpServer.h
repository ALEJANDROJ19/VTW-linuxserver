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
#include "../Threads/TcpThread.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <ifaddrs.h>
#include <errno.h>

class tcpServer {

public:
    int createTCPServer();
    int Stop();
    void SetStartAppCallback(int(*StartAppCallback)(int));
    void SetStopAppCallback(int(*StopAppCallback)(int));
    void SetgetAppListCallback(char*(*getAppList)());
    void SetupdateAppListCallback(char*(*updateAppList)(char*));
    void SetgetAppThumbCallback(char*(*getAppThumb)());

    struct CallBacks {
        f_int_int_t StartAppCallback;
        f_int_int_t StopAppCallback;
        f_char_void_t getAppList;
        f_char_char_t updateAppList;
        f_char_void_t getAppThumb;
    };

private:
    typedef int (*f_int_int_t) (int);
    typedef char* (*f_char_void_t) ();
    typedef char* (*f_char_char_t) (char*);

    void checkandSetKeepAlive();
    void receivedNewMessage(json_object*, char&);
    void ext(char*);
    char* getIpAddress();
    char* cleanBuffer(char[]);

    CallBacks callBacks;
    struct sockaddr_in server;
    int _Socket;
    char _Buffer[BUFFLEN];
    char* _IP;
    JsonHandler jsonHandler;
};


#endif //VTW_SERVER_LINUX_TCPSERVER_H
