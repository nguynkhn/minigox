#include <fcntl.h>
#include <linux/input.h>
#include <poll.h>
#include <unistd.h>
#include <xkbcommon/xkbcommon.h>

static int fd;
static struct xkb_context *ctx;
static struct xkb_keymap *keymap;
static struct xkb_state *state;

static bool minigox_setup(void) {
    fd = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);

    ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    keymap = xkb_keymap_new_from_names(ctx, NULL, XKB_KEYMAP_COMPILE_NO_FLAGS);
    state = xkb_state_new(keymap);
    return fd != -1;
}

static void update_modifiers(bool keydown, int vkcode) {
    switch (vkcode) {
    case KEY_LEFTSHIFT:
    case KEY_RIGHTSHIFT:
        modifiers.shift = keydown;
        break;
    case KEY_LEFTCTRL:
    case KEY_RIGHTCTRL:
        modifiers.ctrl = keydown;
        break;
    case KEY_LEFTALT:
    case KEY_RIGHTALT:
        modifiers.alt = keydown;
        break;
    case KEY_CAPSLOCK:
        if (keydown)
            modifiers.caps = !modifiers.caps;
        break;
    case KEY_NUMLOCK:
        if (keydown)
            modifiers.num = !modifiers.num;
        break;
    case KEY_SCROLLLOCK:
        if (keydown)
            modifiers.scroll = !modifiers.scroll;
        break;
    }
}

static bool minigox_run(void) {
    struct pollfd pfd = { fd, POLLIN, 0 };
    struct input_event event;

	for (;;) {
        if (poll(&pfd, 1, -1) > 0) {
            if (read(fd, &event, sizeof event) == sizeof event) {
                if (event.type != EV_KEY)
                    continue;

                int vkcode = event.code;
                bool keydown = event.value == 1 || event.value == 2;
                update_modifiers(keydown, vkcode);

                xkb_keycode_t keycode = vkcode + 8;
                xkb_state_update_key(
                    state,
                    keycode,
                    keydown ? XKB_KEY_DOWN : XKB_KEY_UP
                );
                if (keydown) {
                    char buf[64];
                    int len = xkb_state_key_get_utf8(
                        state,
                        keycode,
                        buf,
                        sizeof(buf)
                    );

                    if (len > 0) {
                        // DEBUG
                        // WILL REMOVE LATER
                        fwrite(buf, 1, len, stdout);
                        fflush(stdout);
                    }
                }
            }
        }
    }
    return true;
}

static void minigox_destroy(void) {
    xkb_state_unref(state);
    xkb_keymap_unref(keymap);
    xkb_context_unref(ctx);

    close(fd);
}
