#include "JsonHandler.h"

const char* JsonHandler::handleJsonData(json_object * jsonObject) {
    struct json_object *array, *object;
    int i, arraylen = json_object_array_length(jsonObject);

    array = json_object_array_get_idx(jsonObject, 0);
    json_object_object_get_ex(array, J_REQUEST, &object);
    static const char* eval = json_object_get_string(object);

    if(strcmp(eval,J_CODE_DISCOVERY) == 0) {
        return json_object_get_string(create2BroadcastResponseOk((char*)"0.0.0.0", (char*)"21211"));
    } else if (strcmp(eval,J_CODE_REQUESTAPP) == 0) {
        return json_object_get_string(create4AppResponse(1, nullptr));
    } else if (strcmp(eval,J_CODE_UPDATEAPP) == 0) {
        char str[10]; //10 max app update lenght
        for (i = 1; i < arraylen && i < 50; i++) {
            str[i] = *json_object_get_string(json_object_array_get_idx(jsonObject, i));
        }
        return json_object_get_string(create4AppResponse(0,str));
    } else if (strcmp(eval,J_CODE_START) == 0) {
        int app;
        //todo get app
        app = 0;
        return json_object_get_string(create6StartStopResponse(1,app));
    } else if (strcmp(eval,J_CODE_STOP) == 0) {
        int app;
        //todo get app
        app = 0;
        return json_object_get_string(create6StartStopResponse(0,app));
    } else
        return nullptr;
}

json_object* JsonHandler::create2BroadcastResponseOk(char* ip, char* port) {

    json_object *jcode = json_object_new_string("OK");
    json_object *jobjcode = json_object_new_object();
    json_object_object_add(jobjcode, J_RESPONSE, jcode);

    json_object *jip= json_object_new_string(ip);
    json_object *jobjip = json_object_new_object();
    json_object_object_add(jobjip,J_IP, jip);

    json_object *jport = json_object_new_string(port);
    json_object *jobjport = json_object_new_object();
    json_object_object_add(jobjport,J_PORT, jport);

    json_object *jarray = json_object_new_array();
    json_object_array_add(jarray, jobjcode);
    json_object_array_add(jarray, jobjip);
    json_object_array_add(jarray, jobjport);

    json_object *resjobj = json_object_new_object();
    json_object_object_add(resjobj,J_VTWCONTROL,jarray);
    return resjobj;
}

json_object *JsonHandler::create4AppResponse(int code, char str[]) {
    char app[100];

    if(code){
        //todo get all the apps
        //app[] = ...
    } else {
        //todo update the apps
        //str[] == app[] ...
    }

    json_object *jarray = json_object_new_array();
    if(str != nullptr) {
        int i = 0;
        while (i < sizeof(str) && str[i] != NULL) {
            json_object *jstr = json_object_new_string(&str[i]);
            json_object *jtumb = json_object_new_string((char *) 'c');

            json_object *jobjstr = json_object_new_object();
            json_object *jobjtumb = json_object_new_object();

            json_object_object_add(jobjstr, J_ID, jstr);
            json_object_object_add(jobjtumb, J_THUMBNAIL, jtumb);

            json_object_array_add(jarray, jobjstr);
            json_object_array_add(jarray, jobjtumb);

            i++;
        }
    }

    json_object *jcode = json_object_new_string(J_APP_LIST);
    json_object *jobjcode = json_object_new_object();
    json_object_object_add(jobjcode, J_RESPONSE, jcode);

    json_object *jarray_f = json_object_new_array();
    json_object_array_add(jarray_f, jobjcode);

    json_object *resjobjt = json_object_new_object();
    json_object_object_add(resjobjt, J_APP_LIST, jarray);

    json_object_array_add(jarray_f, resjobjt);

    json_object *resjobj = json_object_new_object();
    json_object_object_add(resjobj, J_VTWCONTROL, jarray_f);
    return resjobj;
}

json_object *JsonHandler::create6StartStopResponse(int code, int app) {

    if(!code){
        //todo stop the app
        return nullptr;
    }
    //todo start app with code app and get:
    //todo get the data ip
    //todo get the port
    //todo get the data uri
    char app_id[20], *app_ip, *app_port, *app_uri;

    snprintf(app_id, 20, "%d", app);
    app_ip = (char*) "0.0.0.0";
    app_port = (char*) "00000";
    app_uri = (char*) "uri";

    json_object *jcode = json_object_new_string(J_CODE_START);
    json_object *jobjcode = json_object_new_object();
    json_object_object_add(jobjcode, J_RESPONSE, jcode);


    json_object *jid = json_object_new_string(app_id);
    json_object *jobjid = json_object_new_object();
    json_object_object_add(jobjid, J_ID, jid);

    json_object *jip = json_object_new_string(app_ip);
    json_object *jobjip = json_object_new_object();
    json_object_object_add(jobjip, J_IP, jip);

    json_object *jport = json_object_new_string(app_port);
    json_object *jobjport = json_object_new_object();
    json_object_object_add(jobjport, J_PORT, jport);

    json_object *juri = json_object_new_string(app_uri);
    json_object *jobjuri = json_object_new_object();
    json_object_object_add(jobjuri, J_URI, juri);

    json_object *jarray = json_object_new_array();
    json_object_array_add(jarray, jobjcode);
    json_object_array_add(jarray, jobjip);
    json_object_array_add(jarray, jobjid);
    json_object_array_add(jarray, jobjport);
    json_object_array_add(jarray, jobjuri);

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
