#include <termios.h>
#include <unistd.h>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "rkeylogger.h"

bool get_capsclock_status() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    return (term.c_lflag & ECHO) != 0;
}

std::string current_datetime(){
    auto currentTime = std::chrono::system_clock::now();
    
    std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
    std::tm localTime = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d_%H:%M:%S");

    return oss.str();
}