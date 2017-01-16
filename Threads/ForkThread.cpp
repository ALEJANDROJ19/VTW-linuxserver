#include <zconf.h>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <cstdlib>
#include <wait.h>
#include "ForkThread.h"

void ForkThread::ThreadCode() {
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

    int status;
    waitpid(_threadFfserver, &status, 0);
    waitpid(_threadFfmpeg, &status, 0);

    return;
}

void ForkThread::ExecFfmpeg() {
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

void ForkThread::ExecFfserver() {
    static char *argv[] = {
            (char *)"ffserver",
            (char *) NULL
    };
    execv("/usr/bin/ffserver", argv);
    printf("%s%s\n", "Error on 'exec' ffserver: ", strerror(errno));
    exit(1);
}

void ForkThread::stopForkedChilds() {
    kill(_threadFfmpeg, SIGTERM);
    kill(_threadFfserver, SIGTERM);
}