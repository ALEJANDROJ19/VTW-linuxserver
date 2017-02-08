#include "TcpServer.h"

int TcpServer::createTCPServer() {
    _IP = getIpAddress();
    jsonHandler = JsonHandler();
    jsonHandler.setCallbacks(callBacks);
    jsonHandler.setIP(_IP);
    exitRecvLoop = false;
    if ((_Socket = socket(AF_INET , SOCK_STREAM , 0)) == -1)
        ext((char *)"socket");
    memset((char *)&server, 0, sizeof(server));
    server.sin_addr.s_addr = inet_addr("0.0.0.0");
    server.sin_family = AF_INET;
    server.sin_port = htons(TCP_PORT);

    if (bind(_Socket, (struct sockaddr *)&server , sizeof(server)) < 0)
        ext((char *)"connect");
    checkandSetKeepAlive();
    listen(_Socket,5);
    int clientfd;
    struct sockaddr_in cli_addr;
    ssize_t n;
    socklen_t client = sizeof(cli_addr);
    fd_set rs;

    while (!exitRecvLoop) {
        FD_ZERO(&rs);
        FD_SET(_Socket, &rs);

        timeval timeout = {0, 1000};
        if (select(_Socket + 1, &rs, NULL, NULL, &timeout) < 0)
            ext((char *) "accept");

        if (FD_ISSET(_Socket, &rs)) {
            clientfd = accept(_Socket, (struct sockaddr *) &cli_addr, &client);

            //read from the soket
            bzero(_Buffer, BUFFLEN);
            n = read(clientfd, _Buffer, BUFFLEN);

            if (n < 0) { ext((char *) "socket read"); }

            //if we got a post message clean the buffer
            if (strstr(_Buffer, "POST")) {
                json_object *jobj, *jobjres;
                char array[BUFFLEN];
                int i = 0;
                while (_Buffer[i] != '{') {
                    i++;
                }
                int c = 0;
                while (i < BUFFLEN) {
                    array[c] = _Buffer[i];
                    i++;
                    c++;
                }
                array[c] = '\0';

                char sourceIP[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(cli_addr.sin_addr), sourceIP, INET_ADDRSTRLEN);
                printf("\n ### new connection from: %s\n", sourceIP);
                printf("### Request:\n%s\n", array);

                jobj = json_tokener_parse(array);
                json_object_object_get_ex(jobj, J_VTWCONTROL, &jobjres);
                char tmpBuffer[BUFFLEN];

                //parse new message and get response
                if (jobjres != nullptr) {
                    receivedNewMessage(jobjres, *tmpBuffer);
                    printf("### Response:\n%s\n", tmpBuffer);
                    if ((write(clientfd, tmpBuffer, strlen(tmpBuffer))) < 0)
                        perror("sendto() error");
                }
            }
            //close the connection
            if (shutdown(clientfd, SHUT_RDWR) < 0)
                if (errno != ENOTCONN && errno != EINVAL)
                    perror("shutdown");
            if (close(clientfd) < 0)
                perror("close");
        }
    }
    close(_Socket);
    return 0;
}

void TcpServer::receivedNewMessage(json_object *jobj, char &buffer) {
    bzero(&buffer, BUFFLEN);
    char* ok_response = new char[248];
    sprintf(ok_response, "HTTP/1.0 200 OK\n"
            "Server: VTW Server\n"
            "Connection: Close\n"
            "Content-Type:application/json\n"
            "\r\n\r\n"
    );

    strcpy(&buffer, ok_response);
    delete[] ok_response;

    if(jobj != nullptr) {
        const char* tmp = jsonHandler.handleJsonData(jobj);
        strcat(&buffer, tmp);
    }
    // todo else create json error and remove the calling non null on json
}

void TcpServer::checkandSetKeepAlive(){
    /* Check the status for the keepalive option */
    int optval;
    socklen_t optlen = sizeof(optval);
    optval = 1;
    if(getsockopt(_Socket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
        perror("getsockopt()");
        close(_Socket);
        free(_IP);
        exit(EXIT_FAILURE);
    }
    printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

    /* Set the option active */
    optval = 1;
    optlen = sizeof(optval);
    if(setsockopt(_Socket, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
        perror("setsockopt()");
        close(_Socket);
        exit(EXIT_FAILURE);
    }
    printf("SO_KEEPALIVE set on socket\n");

    /* Check the status again */
    if(getsockopt(_Socket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
        perror("getsockopt()");
        close(_Socket);
        exit(EXIT_FAILURE);
    }
    printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
}

void TcpServer::ext(char *s) {
    perror(s);
    exit(1);
}

char* TcpServer::getIpAddress() {
    char* addressBuffer = (char*) malloc(INET_ADDRSTRLEN);
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) {
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            if(strcmp(ifa->ifa_name, "lo") != 0)
                return addressBuffer;
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return nullptr;
}

char* TcpServer::cleanBuffer(char* buffer){
    char *array = new char[BUFFLEN];
    int i = 0;
    while(buffer[i] != '{') {
        i++;
    }
    int c = 0;
    while(i < BUFFLEN) {
        array[c] = buffer[i];
        i++;
        c++;
    }
    array[c] = '\0';
    return array;
}

int TcpServer::Stop() {
    jsonHandler.StopThreads();
    exitRecvLoop = true;
    return 0;
}

void TcpServer::SetStartAppCallback(int (*StartAppCallback)(int)) {
    callBacks.StartAppCallback = StartAppCallback;
}

void TcpServer::SetStopAppCallback(int (*StopAppCallback)(int)) {
    callBacks.StopAppCallback = StopAppCallback;
}

void TcpServer::SetgetAppListCallback(char *(*getAppList)()) {
    callBacks.getAppList = getAppList;
}

void TcpServer::SetupdateAppListCallback(char *(*updateAppList)(char *)) {
    callBacks.updateAppList = updateAppList;
}

void TcpServer::SetgetAppThumbCallback(char *(*getAppThumb)()) {
    callBacks.getAppThumb = getAppThumb;
}
