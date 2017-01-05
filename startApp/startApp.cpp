#include "startApp.h"

void *startApp::threadUdp(void) {
    UDPReceiver UdpReceiver;
    UdpReceiver.StartReceiver();
    return nullptr;
}

void *startApp::threadUdp_Starter(void *context) {
    return ((startApp *)context)->threadUdp();
}


void startApp::ExecFfmpeg() {
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

void startApp::ExecFfserver() {
    static char *argv[] = {
            (char *)"ffserver",
            (char *) NULL
    };
    execv("/usr/bin/ffserver", argv);
    printf("%s%s\n", "Error on 'exec' ffserver: ", strerror(errno));
    exit(1);
}

int startApp::start(int app_id){

    if (status)
        return -1;

    //todo start app with id 'app_id'

    //todo uncomment ffserver ffmpeg and udpserver execs
//    // ffserver fork
//    _threadFfserver = fork();
//    if (_threadFfserver == 0) {
//        ExecFfserver();
//    } else if (_threadFfserver < 0) {
//        printf("%s%s\n", "Error on ffserver: ", strerror(errno));
//        exit(1);
//    }
//    // ffmpef fork
//    _threadFfmpeg = fork();
//    if (_threadFfmpeg == 0) {
//        sleep(3);
//        ExecFfmpeg();
//    } else if (_threadFfmpeg < 0) {
//        printf("%s%s\n", "error ffmpeg: ", strerror(errno));
//        exit(1);
//    }
//    // udpserver thread
//    startApp app;
//    int eval = pthread_create(&_threadUdp, NULL, &startApp::threadUdp_Starter, &app);
//    if (eval) {
//        fprintf(stderr, "Error thread UDP");
//        exit(EXIT_FAILURE);
//    }

    status = true;
    return 0;
}

int startApp::stop(int app_id) {

    if (!status)
        return -1;

    //todo stop the app with 'app_id'

    //todo uncomment ffserver ffmpeg and udpserver kills
//    int stat;
//    kill(_threadFfserver, 9);
//    kill(_threadFfmpeg, 9);
//    pthread_kill(_threadUdp, 9);
//    waitpid(_threadFfmpeg, &stat, WUNTRACED | WCONTINUED);
//    waitpid(_threadFfserver, &stat, WUNTRACED | WCONTINUED);
//    pthread_join(_threadUdp, NULL);

    status = false;
    return 0;
}

char *startApp::getAppList() {
    //todo get all the app ids
    return nullptr;
}

char *startApp::updateAppList(char *) {
    //todo update the app ids
    return nullptr;
}

char *startApp::getAppThumb() {
    //todo get the app thumbnails
    //index of this str is equal to app id index
    return nullptr;
}

