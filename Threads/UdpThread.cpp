#include "UdpThread.h"

void UdpThread::ThreadCode() {
    UdpReceiver.StartReceiver();
}

void UdpThread::StopReceiver() {
    UdpReceiver.StopReceiver();
}
