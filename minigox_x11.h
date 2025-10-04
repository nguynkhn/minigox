#include <X11/Xlib.h>
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

	XIEventMask evmask = {
		.deviceid = XIAllMasterDevices,
		.mask_len = sizeof(mask),
		.mask = mask,
	};

	XISelectEvents(display, root, &evmask, 1);
	XFlush(display);

    return true;
}

static bool minigox_run(void) {
    XEvent ev;

    for (;;) {
        XNextEvent(display, &ev);
        XGenericEventCookie *xc = &ev.xcookie;

        if (
            xc->type == GenericEvent
            && xc->extension == opcode
            && XGetEventData(display, xc)
        ) {
            XIDeviceEvent *dev = xc->data;

            switch (xc->evtype) {
            case XI_ButtonPress:
                if (dev->root_x != mouse.x || dev->root_y != mouse.y)
                    curr = minigox_unpack_char(0);
                break;
            case XI_ButtonRelease:
                mouse.x = dev->root_x;
                mouse.y = dev->root_y;
                break;
            }

            XFreeEventData(display, xc);
        }
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
