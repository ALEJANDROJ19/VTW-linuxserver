#ifndef VTW_SERVER_LINUX_JSONHANDLER_H
#define VTW_SERVER_LINUX_JSONHANDLER_H

#include "../Portocol/HeaderDef.h"
#include <json/json_object.h>
#include <json/json.h>
#include <cstring>
#include "../Portocol/HeaderDef.h"
#include <stdio.h>
#include <stdlib.h>

class JsonHandler {

public:
    const char* handleJsonData(json_object*);
    json_object* create2BroadcastResponseOk(char* ip, char* port);
    json_object* create4AppResponse(int code, char[]);
    json_object* create6StartStopResponse(int code, int app);
    json_object* create7Error(char* code, json_object* obj);
};

#endif //VTW_SERVER_LINUX_JSONHANDLER_H
