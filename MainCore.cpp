#include <pthread.h>
#include "tcpServer/tcpServer.h"

//void* threadTcp(void *) {
//    tcpServer tcpServer;
//    tcpServer.createTCPServer();
//    return nullptr;
//}
//
//int main(void) {
//    //start tcp server 'protocol json'
//    pthread_t _threadTcp;
//    int eval = pthread_create(&_threadTcp, NULL, threadTcp, NULL);
//    if (eval) {
//        fprintf(stderr, "Error thread Tcp");
//        exit(EXIT_FAILURE);
//    }
//    pthread_join(_threadTcp, NULL);
//    return -1;
//}

int main(void) {
    tcpServer tcpServer;
    tcpServer.createTCPServer();
}