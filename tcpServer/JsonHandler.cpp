#include "JsonHandler.h"

const char* JsonHandler::handleJsonData(json_object * jsonObject) {
    struct json_object *array, *object, *jobj;
    int i, arraylen = json_object_array_length(jsonObject);

    array = json_object_array_get_idx(jsonObject, 0);
    json_object_object_get_ex(array, J_REQUEST, &object);
    const char* eval = json_object_get_string(object);

    if(strcmp(eval,J_CODE_DISCOVERY) == 0) {
        return json_object_get_string(create2BroadcastResponseOk(_IP, (char*)"21211"));
    }
    else if (strcmp(eval,J_CODE_REQUESTAPP) == 0) {
        return json_object_get_string(create4AppResponse(1, nullptr));
    }
    else if (strcmp(eval,J_CODE_UPDATEAPP) == 0) {
        char str[10]; //10 max app update lenght
        for (i = 1; i < arraylen && i < 50; i++) {
            array = json_object_array_get_idx(jsonObject, i);
            json_object_object_get_ex(array, J_APP, &jobj);
            str[i] = *json_object_get_string(jobj);
        }
        return json_object_get_string(create4AppResponse(0,str));
    }
    else if (strcmp(eval,J_CODE_START) == 0) {
        array = json_object_array_get_idx(jsonObject, 1);
        json_object_object_get_ex(array, J_ID, &jobj);
        int app = json_object_get_int(jobj);
        return json_object_get_string(create6StartStopResponse(1,app));
    }
    else if (strcmp(eval,J_CODE_STOP) == 0) {
        array = json_object_array_get_idx(jsonObject, 1);
        json_object_object_get_ex(array, J_ID, &jobj);
        int app = json_object_get_int(jobj);
        return json_object_get_string(create6StartStopResponse(0,app));
    }
    else
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
    int max_size = 5;
//    #####Hardcoded apps
    char *app_list[] = {
            (char *)"1",
            (char *)"2",
            (char *)"3",
            (char *)"4",
            (char *)"5"
    };

    const char *app_thumb[] = {
            (char *)"NULL",
            (char *)"NULL",
            (char *)"NULL",
            (char *)"NULL",
            (char *)"NULL"
    };
//    #####

//    if(code){
//        app_list = callBacks.getAppList();
//    } else {
//        app_list = callBacks.updateAppList(str);
//    }
//    app_thumb = callBacks.getAppThumb();

    json_object *jarray = json_object_new_array();
    if(jarray != nullptr) {
        int i = 0;
        while (i < max_size && app_list[i] != '\0') {
            json_object *jstr = json_object_new_string(&*app_list[i]);
            json_object *jtumb = json_object_new_string(&*app_thumb[i]);

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

json_object *JsonHandler::create6StartStopResponse(int code, int app_id) {

    char app_id_c[20], *app_ip, *app_port, *app_uri;
    snprintf(app_id_c, 20, "%d", app_id);

    if(!code){
        if(app.stop(app_id) == 1)
            return create7Error((char*)ERROR_NOAPPRUNNING,NULL);
        else{
//            callBacks.StopAppCallback(app_id);

            json_object *jcode = json_object_new_string(J_CODE_STOP);
            json_object *jobjcode = json_object_new_object();
            json_object_object_add(jobjcode, J_RESPONSE, jcode);

            json_object *jid = json_object_new_string(app_id_c);
            json_object *jobjid = json_object_new_object();
            json_object_object_add(jobjid, J_ID, jid);

            json_object *jarray = json_object_new_array();
            json_object_array_add(jarray, jobjcode);
            json_object_array_add(jarray, jobjid);

            json_object *resjobj = json_object_new_object();
            json_object_object_add(resjobj,J_VTWCONTROL,jarray);
            return resjobj;
        }

    }
    if(app.start(app_id) == 1)
        return create7Error((char*)ERROR_APPRUNNING,NULL);

//    callBacks.StartAppCallback(app_id);
    //todo get the port '_PORT' def is 8090
    //todo get the data uri '_URI' def is test1.webm

    app_ip = _IP;
    app_port = _PORT;
    app_uri = _URI;

    json_object *jcode = json_object_new_string(J_CODE_START);
    json_object *jobjcode = json_object_new_object();
    json_object_object_add(jobjcode, J_RESPONSE, jcode);


    json_object *jid = json_object_new_string(app_id_c);
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
    json_object_array_add(jarray, jobjid);
    json_object_array_add(jarray, jobjip);
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

    json_object *jarray = json_object_new_array();
    json_object_array_add(jarray, jobj);

    json_object *resjobj = json_object_new_object();
    json_object_object_add(resjobj,J_VTWCONTROL,jarray);
    return resjobj;
}

void JsonHandler::setIP(char *ip) {
    _IP = ip;
}

void JsonHandler::setCallbacks(Callbacks::CallBacks callBacks) {
    this->callBacks = callBacks;
}

void JsonHandler::StopThreads() {
    app.stop(0);
}
