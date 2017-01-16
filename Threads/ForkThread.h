#ifndef VTW_SERVER_LINUX_FORKTHREAD_H
#define VTW_SERVER_LINUX_FORKTHREAD_H

#include "Thread.h"

class ForkThread : public Thread {

public:
    virtual void ThreadCode();
    void stopForkedChilds();

private:
    pid_t  _threadFfserver, _threadFfmpeg;
    void ExecFfmpeg();
    void ExecFfserver();
};


#endif //VTW_SERVER_LINUX_FORKTHREAD_H
