#include "UdpThreadCode.h"

void UdpThreadCode::ThreadCode() {
    UdpReceiver.StartReceiver();
}

void UdpThreadCode::StopReceiver() {
    UdpReceiver.StopReceiver();
}