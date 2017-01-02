#include "JsonHandler.h"

json_object* JsonHandler::create2BroadcastResponseOk(char* ip, char* port) {
    json_object *jcode = json_object_new_string("OK");
    json_object *jip= json_object_new_string(ip);
    json_object *jport = json_object_new_string(port);

    json_object *jobjcode = json_object_new_object();
    json_object *jobjip = json_object_new_object();
    json_object *jobjport = json_object_new_object();

    json_object_object_add(jobjcode, J_RESPONSE, jcode);
    json_object_object_add(jobjip,J_IP, jip);
    json_object_object_add(jobjport,J_PORT, jport);

    json_object *jarray = json_object_new_array();
    json_object_array_add(jarray, jobjcode);
    json_object_array_add(jarray, jobjip);
    json_object_array_add(jarray, jobjport);

    json_object *resjobj = json_object_new_object();
    json_object_object_add(resjobj,J_VTWCONTROL,jarray);
    return resjobj;
}

json_object *JsonHandler::create7Error(char* code, json_object *obj) {
    json_object *jobj = json_object_new_object();
    json_object *jcode = json_object_new_string(code);
    json_object_object_add(jobj,J_ERROR, jcode);
    json_object_object_add(jobj,J_MESSAGE, obj);
    return jobj;
}

const char* JsonHandler::handleJsonData(json_object * jsonObject) {
    struct json_object *array, *object;
    int i, arraylen = json_object_array_length(jsonObject);

    array = json_object_array_get_idx(jsonObject, 0);
    json_object_object_get_ex(array, J_REQUEST, &object);
    static const char* eval = json_object_get_string(object);

    if(strcmp(eval,J_CODE_DISCOVERY) == 0) {
        return json_object_get_string(create2BroadcastResponseOk((char*)"0.0.0.0", (char*)"21211"));
    } else if (strcmp(eval,J_CODE_REQUESTAPP) == 0) {

    } else if (strcmp(eval,J_CODE_UPDATEAPP) == 0) {
        for (i = 1; i < arraylen; i++) {

        }

    } else if (strcmp(eval,J_CODE_START) == 0) {

    } else if (strcmp(eval,J_CODE_STOP) == 0) {

    } else
        return nullptr;
}
