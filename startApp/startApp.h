#include "../udpServer/UDPReceiver.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../Threads/UdpThread.h"
#include "../Threads/ForkThread.h"

#ifndef VTW_SERVER_LINUX_STARTAPP_H
#define VTW_SERVER_LINUX_STARTAPP_H

class startApp {
public:
    int start(int);
    int stop(int);
    char* getAppList();
    char* updateAppList(char[]);
    char* getAppThumb();

private:
    bool status = false;
    ForkThread forkThread;
    UdpThreadCode udpThreadCode;
};


#endif //VTW_SERVER_LINUX_STARTAPP_H
