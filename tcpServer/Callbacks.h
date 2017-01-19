#ifndef VTW_SERVER_LINUX_CALLBACKS_H
#define VTW_SERVER_LINUX_CALLBACKS_H


class Callbacks {
public:
    typedef int (*f_int_int_t) (int);
    typedef char* (*f_char_void_t) ();
    typedef char* (*f_char_char_t) (char*);
    struct CallBacks {
        f_int_int_t StartAppCallback;
        f_int_int_t StopAppCallback;
        f_char_void_t getAppList;
        f_char_char_t updateAppList;
        f_char_void_t getAppThumb;
    };
};


#endif //VTW_SERVER_LINUX_CALLBACKS_H
