#include <iostream>
#include <libudev.h>
#include <xkbcommon/xkbcommon.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/input.h>

void monitorKeyboard(const char *devnode) {
    int fd = open(devnode, O_RDONLY);
    if (fd == -1) {
        std::cerr << "Impossible d'ouvrir le périphérique clavier.\n";
        return;
    }

    struct input_event ev;

    // Create an xkb context and keymap
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
                // Get the symbol for the key
                xkb_keycode_t keycode = ev.code + 8; // Offset for EV_KEY
                xkb_keysym_t sym = xkb_state_key_get_one_sym(state, keycode);

                // Get the Unicode code point for the symbol
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

int main() {
    struct udev *udev = udev_new();
    if (!udev) {
        std::cerr << "Erreur lors de l'initialisation de libudev.\n";
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
            std::cout << "Périphérique clavier détecté : " << devnode << std::endl;

            monitorKeyboard(devnode);
            break;
        }

        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);
    return 0;
}