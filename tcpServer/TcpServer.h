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

class TcpServer {

public:
    int createTCPServer();
    int Stop();
    void SetStartAppCallback(int(*StartAppCallback)(int));
    void SetStopAppCallback(int(*StopAppCallback)(int));
    void SetgetAppListCallback(char*(*getAppList)());
    void SetupdateAppListCallback(char*(*updateAppList)(char*));
    void SetgetAppThumbCallback(char*(*getAppThumb)());

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
    bool exitRecvLoop;
    JsonHandler jsonHandler;
    Callbacks::CallBacks callBacks;
};


#endif //VTW_SERVER_LINUX_TCPSERVER_H
