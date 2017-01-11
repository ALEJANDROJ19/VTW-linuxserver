#ifndef VTW_SERVER_LINUX_UDPTHREADCODE_H
#define VTW_SERVER_LINUX_UDPTHREADCODE_H
#include "Thread.h"
#include "../../udpServer/UDPReceiver.h"

class UdpThreadCode : public Thread {

public:
    virtual void ThreadCode();
    void StopReceiver();

private:
    UDPReceiver UdpReceiver;
};


#endif //VTW_SERVER_LINUX_UDPTHREADCODE_H
