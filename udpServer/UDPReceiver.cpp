#include "UDPReceiver.h"
#include "../Portocol/HeaderDef.h"

int UDPReceiver::StartReceiver() {
    initUDPSocket();

    printf("Udp started...");

    fd_set rs;
    json_object *Jarray,*Jdata, *Jobj, *jobjX, *jobjY, *jobjZ;

    while (!exitRecvLoop) {
        fflush(stdout);
        FD_ZERO(&rs);
        FD_SET(_Socket, &rs);

        // 1 milli
        timeval timeout = { 0, 1000 };
        if (select(_Socket, &rs, NULL, NULL, &timeout) < 0)
            ext((char *)"recvfrom()");
        if (FD_ISSET(_Socket, &rs)) {
            //recive data non-bloking call
            recvfrom(_Socket, _Buffer, BUFLEN, MSG_DONTWAIT, (struct sockaddr *)&si_other, &slen);

            Jdata = json_tokener_parse(_Buffer);
            json_object_object_get_ex(Jdata, J_VTWDATA, &Jarray);
            Jobj = json_object_array_get_idx(Jarray, 0);
            json_object_object_get_ex(Jobj, J_CODE_X, &jobjX);
            Jobj = json_object_array_get_idx(Jarray, 1);
            json_object_object_get_ex(Jobj, J_CODE_Y, &jobjY);
            Jobj = json_object_array_get_idx(Jarray, 2);
            json_object_object_get_ex(Jobj, J_CODE_Z, &jobjZ);

            double coordX = json_object_get_double(jobjX);
            double coordY = json_object_get_double(jobjY);
            double coordZ = json_object_get_double(jobjZ);
            module.input(CoordinatesXYZ((float)coordX, (float)coordY, (float)coordZ));
        }
    }
    close(_Socket);
    printf("Stopped udp...");
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

