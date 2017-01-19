#ifndef VTW_SERVER_LINUX_TCPTHREAD_H
#define VTW_SERVER_LINUX_TCPTHREAD_H


#include "Thread.h"
#include "../tcpServer/TcpServer.h"

class TcpThread : public Thread {

public:
    virtual void ThreadCode();
    void StopServer();

    void SetStartAppCallback(int(*StartAppCallback)(int));
    void SetStopAppCallback(int(*StopAppCallback)(int));
    void SetgetAppListCallback(char*(*getAppList)());
    void SetupdateAppListCallback(char*(*updateAppList)(char*));
    void SetgetAppThumbCallback(char*(*getAppThumb)());

private:
    TcpServer tcpServerInstance;
};


#endif //VTW_SERVER_LINUX_TCPTHREAD_H
