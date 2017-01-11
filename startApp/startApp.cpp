#include "startApp.h"

int startApp::start(int app_id){

    if (status)
        return -1;

    //todo start app with id 'app_id'
    forkThread.Start();
    udpThreadCode.Start();

    status = true;
    return 0;
}

int startApp::stop(int app_id) {

    if (!status)
        return -1;

    //todo stop the app with 'app_id'

    //todo kill things maybe thread or who knows
    forkThread.stopForkedChilds();
    udpThreadCode.StopReceiver();
    forkThread.Wait();
    udpThreadCode.Wait();
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

