#ifndef VTW_SERVER_LINUX_UDPRECEIVER_H
#define VTW_SERVER_LINUX_UDPRECEIVER_H

#include <arpa/inet.h>
#include <json/json.h> //json library -> json-c
#include <stdio.h>     //printf
#include <stdlib.h>    //exit(0);
#include <string.h>    //memset
#include <sys/socket.h>
#include "../mouseController/controlmodule.h"

#define PORT 21210
#define BUFLEN 128

class UDPReceiver {
public:
    int StartReceiver();

private:
    // functions
    void initUDPSocket();
    void ext(char *);

    // objects
    struct sockaddr_in server, si_other;
    int _Socket;
    socklen_t slen;
    char _Buffer[BUFLEN];
    controlmodule module = controlmodule();
};

#endif //VTW_SERVER_LINUX_UDPRECEIVER_H