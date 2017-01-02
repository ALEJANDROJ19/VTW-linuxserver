#include "udpServer/UDPReceiver.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "tcpServer/tcpServer.h"

void *threadUdp(void *) {
    UDPReceiver UdpReceiver;
    UdpReceiver.StartReceiver();
    return nullptr;
}

void ExecFfmpeg() {
    static char *argv[] = {
            (char *)"ffmpeg",
            (char *)"-f",
            (char *)"x11grab",
            (char *)"-r",
            (char *)"25",
            (char *)"-s",
            (char *)"1366x768",
            (char *)"-i",
            (char *)":0.0",
            (char *)"-f",
            (char *)"alsa",
            (char *)"-i",
            (char *)"pulse",
            (char *)"http://localhost:8090/feed1.ffm",
            (char *) NULL
    };
    execv("/usr/bin/ffmpeg", argv);
    printf("%s%s\n", "error 'exec' ffmpeg: ", strerror(errno));
    exit(1);
}

void ExecFfserver() {
    static char *argv[] = {
            (char *)"ffserver",
            (char *) NULL
    };
    execv("/usr/bin/ffserver", argv);
    printf("%s%s\n", "Error on 'exec' ffserver: ", strerror(errno));
    exit(1);
}

int main(void) {
    tcpServer tcpServer;
    tcpServer.createTCPServer();
    pthread_t _threadUdp;
    pid_t _threadFfmpeg, _threadFfserver;

    // ffserver fork
      _threadFfserver = fork();
    if (_threadFfserver == 0) {
        ExecFfserver();
    } else if (_threadFfserver < 0) {
        printf("%s%s\n", "Error on ffserver: ", strerror(errno));
        exit(1);
    }
    // ffmpef fork
    _threadFfmpeg = fork();
    if (_threadFfmpeg == 0) {
        sleep(3);
        ExecFfmpeg();
    } else if (_threadFfmpeg < 0) {
          printf("%s%s\n", "error ffmpeg: ", strerror(errno));
          exit(1);
    }
    // udpserver thread
    int eval = pthread_create(&_threadUdp, NULL, threadUdp, NULL);
    if (eval) {
        fprintf(stderr, "Error thread UDP");
        exit(EXIT_FAILURE);
    }
    int status;
    waitpid(_threadFfmpeg, &status, WUNTRACED | WCONTINUED);
    kill(_threadFfserver, 9);
    pthread_kill(_threadUdp, 9);
    return 0;
}
