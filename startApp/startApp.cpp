#include "startApp.h"

int startApp::start(int app_id){

    if (status)
        return -1;
    forkThread.Start();
    udpThread.Start();

    status = true;
    return 0;
}

int startApp::stop(int app_id) {

    if (!status)
        return -1;
    //todo kill things maybe thread or who knows
    forkThread.stopForkedChilds();
    udpThread.StopReceiver();
    forkThread.Wait();
    udpThread.Wait();
    status = false;
    return 0;
}