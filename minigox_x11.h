#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XInput2.h>

static Display *display;
static Window root;
static int opcode;

static bool minigox_setup(void) {
    display = XOpenDisplay(NULL);
    if (!display)
        return false;

    root = DefaultRootWindow(display);

    int event, error;
    if (!XQueryExtension(display, "XInputExtension", &opcode, &event, &error)) {
        return false;
    }

	unsigned char mask[XIMaskLen(XI_LASTEVENT)] = {0};

	XISetMask(mask, XI_ButtonPress);
	XISetMask(mask, XI_ButtonRelease);
    XISetMask(mask, XI_RawKeyPress);
    XISetMask(mask, XI_RawKeyRelease);

	XIEventMask evmask = {
		.deviceid = XIAllMasterDevices,
		.mask_len = sizeof(mask),
		.mask = mask,
	};

	XISelectEvents(display, root, &evmask, 1);
	XFlush(display);

    return true;
}

static void update_modifiers(bool keydown, KeySym keysym) {
    switch (keysym) {
    case XK_Shift_L:
    case XK_Shift_R:
        modifiers.shift = keydown;
        break;
    case XK_Control_L:
    case XK_Control_R:
        modifiers.ctrl = keydown;
        break;
    case XK_Alt_L:
    case XK_Alt_R:
        modifiers.alt = keydown;
        break;
    case XK_Caps_Lock:
        if (keydown) modifiers.caps = !modifiers.caps;
        break;
    case XK_Num_Lock:
        if (keydown) modifiers.num = !modifiers.num;
        break;
    case XK_Scroll_Lock:
        if (keydown) modifiers.scroll = !modifiers.scroll;
        break;
    }
}

static bool minigox_run(void) {
    XEvent ev;

    for (;;) {
        XNextEvent(display, &ev);
        XGenericEventCookie *xc = &ev.xcookie;

        if (
            xc->type != GenericEvent
            || xc->extension != opcode
            || !XGetEventData(display, xc)
        )
            continue;

        XIDeviceEvent *dev = xc->data;

        if (xc->evtype == XI_ButtonPress) {
            if (dev->root_x != mouse.x || dev->root_y != mouse.y)
                curr = minigox_unpack_char(0);
        } else if (xc->evtype == XI_ButtonRelease) {
            mouse.x = dev->root_x;
            mouse.y = dev->root_y;
        } else {
            bool keydown = xc->evtype == XI_RawKeyPress;
            KeySym keysym = XkbKeycodeToKeysym(
                display, dev->detail,
                0,
                modifiers.shift
            );

            update_modifiers(keydown, keysym);

            if (!keydown)
                continue;

            if (
                keysym == XK_Delete || keysym == XK_Return
                || keysym == XK_Home   || keysym == XK_End
                || keysym == XK_Page_Up || keysym == XK_Page_Down
                || keysym == XK_Left || keysym == XK_Right
                || keysym == XK_Up || keysym == XK_Down
                || modifiers.ctrl || modifiers.alt
            ) {
                curr = minigox_unpack_char(0);
                continue;
            }

            XKeyEvent kev = {
                .display = display,
                .keycode = dev->detail,
                .state = 0,
            };

            if (modifiers.shift)
                kev.state |= ShiftMask;
            if (modifiers.ctrl)
                kev.state |= ControlMask;
            if (modifiers.alt)
                kev.state |= Mod1Mask;
            if (modifiers.caps)
                kev.state |= LockMask;

            char buffer[16];
            if (
                XLookupString(
                    &kev,
                    buffer,
                    sizeof(buffer) - 1,
                    &keysym,
                    NULL
                ) == 1
                && minigox_process_char(buffer[0])
            ) {
            }
        }

        XFreeEventData(display, xc);
    }

    return true;
}

static void minigox_destroy(void) {
    XCloseDisplay(display);
}

static void minigox_enqueue_char(char *) {
    // TODO
}

static void minigox_flush(void) {
    // TODO
}
