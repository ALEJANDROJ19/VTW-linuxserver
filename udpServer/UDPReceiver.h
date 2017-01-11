#ifndef VTW_SERVER_LINUX_UDPRECEIVER_H
#define VTW_SERVER_LINUX_UDPRECEIVER_H

#include <arpa/inet.h>
#include <json/json.h> //json library -> json-c
#include <stdio.h>     //printf
#include <stdlib.h>    //exit(0);
#include <string.h>    //memset
#include <sys/socket.h>
#include <unistd.h>
#include "../mouseController/controlmodule.h"
#include <fcntl.h>

#define PORT 21210
#define BUFLEN 128

class UDPReceiver {
public:
    int StartReceiver();
    void StopReceiver();

private:
    void initUDPSocket();
    void ext(char *);

    char _Buffer[BUFLEN];
    int _Socket;
    bool exitRecvLoop;
    struct sockaddr_in server, si_other;
    socklen_t slen;
    controlmodule module = controlmodule();

};

#endif //VTW_SERVER_LINUX_UDPRECEIVER_H