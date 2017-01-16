#ifndef VTW_SERVER_LINUX_TCPTHREAD_H
#define VTW_SERVER_LINUX_TCPTHREAD_H


#include "../Threads/Thread.h"
#include "../tcpServer/tcpServer.h"

class TcpThread : public Thread {

public:
    virtual void ThreadCode();
    void StopServer();

private:
    tcpServer tcpServerInstance;
};


#endif //VTW_SERVER_LINUX_TCPTHREAD_H
