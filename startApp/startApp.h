#include "../udpServer/UDPReceiver.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef VTW_SERVER_LINUX_STARTAPP_H
#define VTW_SERVER_LINUX_STARTAPP_H

class startApp {
public:
    int start(int);
    void stop(int);
    char* getAppList();
    char* updateAppList(char[]);
    char* getAppThumb();

private:
    void *threadUdp(void);
    static void *threadUdp_Starter(void *);
    void ExecFfmpeg();
    void ExecFfserver();
    pthread_t _threadUdp;
    pid_t _threadFfmpeg, _threadFfserver;
    bool status = false;

};


#endif //VTW_SERVER_LINUX_STARTAPP_H
