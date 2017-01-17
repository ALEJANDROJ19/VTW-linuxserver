#include "startApp.h"

int startApp::start(int app_id){

    if (status)
        return -1;

    //todo start app with id 'app_id'
    forkThread.Start();
    udpThread.Start();

    status = true;
    return 0;
}

int startApp::stop(int app_id) {

    if (!status)
        return -1;

    //todo stop the app with 'app_id'

    //todo kill things maybe thread or who knows
    forkThread.stopForkedChilds();
    udpThread.StopReceiver();
    forkThread.Wait();
    udpThread.Wait();
    status = false;
    return 0;
}