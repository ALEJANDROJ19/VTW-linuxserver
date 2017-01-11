#ifndef VTW_SERVER_LINUX_UDPTHREAD_H
#define VTW_SERVER_LINUX_UDPTHREAD_H

#include <pthread.h>

class Thread
{
public:
    Thread() {/* empty */}
    virtual ~Thread() {/* empty */}

    bool Start()
    {
        return (pthread_create(&_thread, NULL, ThreadI, this) == 0);
    }

    void Wait()
    {
        (void) pthread_join(_thread, NULL);
    }

protected:
    virtual void ThreadCode() = 0;

private:
    static void * ThreadI(void * This) {((Thread *)This)->ThreadCode(); return NULL;}

    pthread_t _thread;
};

#endif //VTW_SERVER_LINUX_UDPTHREAD_H
