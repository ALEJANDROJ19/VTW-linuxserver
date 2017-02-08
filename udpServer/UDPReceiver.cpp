#include "UDPReceiver.h"
#include "../Portocol/HeaderDef.h"

int UDPReceiver::StartReceiver() {
    initUDPSocket();
    controlmodule module;
    printf("Udp started...\n");
    ssize_t n;
    fd_set rs;
    json_object *Jarray,*Jdata, *Jobj, *jobjX, *jobjY, *jobjZ;

    while (!exitRecvLoop) {
        fflush(stdout);
        FD_ZERO(&rs);
        FD_SET(_Socket, &rs);

        // 1 milli
        timeval timeout = { 0, 1000 };
        if (select(_Socket + 1, &rs, NULL, NULL, &timeout) < 0)
            ext((char *)"recvfrom()");
        if (FD_ISSET(_Socket, &rs)) {
            //recive data non-bloking call
            n = recvfrom(_Socket, _Buffer, BUFLEN, 0, (struct sockaddr *)&si_other, &slen);
            if (n < 0) { ext((char *) "socket UDP recv"); }
            Jdata = json_tokener_parse(_Buffer);
            if(Jdata != nullptr) {
                json_object_object_get_ex(Jdata, J_VTWDATA, &Jarray);
                if (Jarray != nullptr) {
                    Jobj = json_object_array_get_idx(Jarray, 0);
                    json_object_object_get_ex(Jobj, J_CODE_X, &jobjX);
                    Jobj = json_object_array_get_idx(Jarray, 1);
                    json_object_object_get_ex(Jobj, J_CODE_Y, &jobjY);
                    Jobj = json_object_array_get_idx(Jarray, 2);
                    json_object_object_get_ex(Jobj, J_CODE_Z, &jobjZ);
                    if(jobjX != nullptr && jobjY != nullptr && jobjZ != nullptr) {
                        double coordX = json_object_get_double(jobjX);
                        double coordY = json_object_get_double(jobjY);
                        double coordZ = json_object_get_double(jobjZ);
                        module.input(CoordinatesXYZ((float) coordX, (float) coordY, (float) coordZ));
                    }
                }
            }
        }
    }
    close(_Socket);
    printf("Stopped udp...\n");
    return 0;
}

void UDPReceiver::initUDPSocket() {
    slen = sizeof(si_other);

    // create a UDP socket
    if ((_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        ext((char *)"socket");

    // zero out the structure
    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind socket to port
    if (bind(_Socket, (struct sockaddr *)&server, sizeof(server)) == -1)
        ext((char *)"bind");
    exitRecvLoop = false;
}

void UDPReceiver::ext(char *s) {
    perror(s);
    exit(1);
}

void UDPReceiver::StopReceiver() {
    exitRecvLoop = true;
}

