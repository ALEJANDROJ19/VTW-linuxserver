#include "UDPReceiver.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int UDPReceiver::StartReceiver() {
    initUDPSocket();
    do {
        printf("Waiting for udp data...");
        fflush(stdout);

        // try to receive some data, this is a blocking call
        if ((recvfrom(_Socket, _Buffer, BUFLEN, 0,
                             (struct sockaddr *)&si_other, &slen)) == -1) {
            ext((char *)"recvfrom()");
        }

        // json parser
        //char *string = _Buffer;
        json_object *jobj, *jobjX, *jobjY, *jobjZ;
        jobj = json_tokener_parse(_Buffer);
        json_object_object_get_ex(jobj,"x",&jobjX);
        double coordX = json_object_get_double(jobjX);
        json_object_object_get_ex(jobj,"y",&jobjY);
        double coordY = json_object_get_double(jobjY);
        json_object_object_get_ex(jobj,"z",&jobjZ);
        double coordZ = json_object_get_double(jobjZ);

        //mouse movement
        module.input(CoordinatesXYZ((float)coordX, (float)coordY, (float)coordZ));

        // debug print details of the client/peer and the data received
//        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr),
//           ntohs(si_other.sin_port));
//        printf("data: %s\n", _Buffer);
//        printf("coord_x: %f\n", coordX);
//        printf("coord_y: %f\n", coordY);
//        printf("coord_z: %f\n", coordZ);
        // end debug

    } while (true);
}
#pragma clang diagnostic pop

void UDPReceiver::initUDPSocket() {
    slen = sizeof(si_other);
    // create a UDP socket
    if ((_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) { ext((char *)"socket"); }
    // zero out the structure
    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind socket to port
    if (bind(_Socket, (struct sockaddr *)&server, sizeof(server)) == -1) { ext((char *)"bind"); }
}

void UDPReceiver::ext(char *s) {
    perror(s);
    exit(1);
}
