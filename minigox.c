#include "minigox.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_LEN(_a)   (sizeof(_a) / sizeof(_a[0]))

static struct CharInfo curr;
static struct Method method;
static struct {
    long x, y;
} mouse;
static struct {
    int ctrl, alt, shift, caps, num, scroll;
} modifiers;

static bool minigox_setup(void);
static bool minigox_run(void);
static void minigox_destroy(void);

static void minigox_enqueue_char(char *);
static void minigox_flush(void);

static bool minigox_process_char(char key) {
    enum ApplyResult result = minigox_apply_method(&method, &curr, key);
    char unicode[4] = {0};

    if (result == APPLY_UNCHANGED || minigox_write_char(curr, unicode) != 0) {
        curr = minigox_unpack_char(key);
        return false;
    }

    minigox_enqueue_char(unicode);

    if (result == APPLY_REVERTED) {
        unicode[0] = key;
        unicode[1] = '\0';
        minigox_enqueue_char(unicode);
        curr = minigox_unpack_char(key);
    }

    minigox_flush();
    return true;
}

#if defined(MINIGOX_WIN32)
#include "minigox_win32.h"
#else
#error "No implementation found"
#endif

int main(int argc, char *argv[]) {
    method.keystroke_num = ARRAY_LEN(TELEX);
    method.keystrokes = TELEX;

    if (argc > 1) {
        char *name = argv[1];

        if (strcmp(name, "vni") == 0) {
            method.keystroke_num = ARRAY_LEN(VNI);
            method.keystrokes = VNI;
        } else if (strcmp(name, "telex") != 0) {
            fprintf(stderr, "Unknown method name\n");
            return 1;
        }
    }

    if (!minigox_setup()) {
        fprintf(stderr, "Failed to setup minigox\n");
        return 1;
    }

    printf("minigox is ready\n");
    if (!minigox_run()) {
        fprintf(stderr, "Unexpected error while running\n");
        return 1;
    }

    minigox_destroy();
    return 0;
}
