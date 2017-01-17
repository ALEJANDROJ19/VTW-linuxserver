#include "TcpThread.h"

void TcpThread::ThreadCode() {
    tcpServerInstance.createTCPServer();
}

void TcpThread::StopServer() {
    tcpServerInstance.Stop();
}

void TcpThread::SetStartAppCallback(int (*StartAppCallback)(int)) {
    tcpServerInstance.SetStartAppCallback(StartAppCallback);
}

void TcpThread::SetStopAppCallback(int (*StopAppCallback)(int)) {
    tcpServerInstance.SetStopAppCallback(StopAppCallback);
}

void TcpThread::SetgetAppListCallback(char *(*getAppList)()) {
    tcpServerInstance.SetgetAppListCallback(getAppList);
}

void TcpThread::SetupdateAppListCallback(char *(*updateAppList)(char *)) {
    tcpServerInstance.SetupdateAppListCallback(updateAppList);
}

void TcpThread::SetgetAppThumbCallback(char *(*getAppThumb)()) {
    tcpServerInstance.SetgetAppThumbCallback(getAppThumb);
}
