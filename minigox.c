#include "minigox.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_LEN(_a)   (sizeof(_a) / sizeof(_a[0]))

#include <Windows.h>

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

#if defined(_WIN32)

#include <Windows.h>

static HHOOK keyboard_hook, mouse_hook;
static INPUT input[6] = {
    {
        .type = INPUT_KEYBOARD,
        .ki = { .wVk = VK_BACK, .dwFlags = 0 },
    },
    {
        .type = INPUT_KEYBOARD,
        .ki = { .wVk = VK_BACK, .dwFlags = KEYEVENTF_KEYUP },
    },
};


static int process_key(char key) {
    enum ApplyResult result = minigox_apply_method(&method, &curr, key);
    if (result == APPLY_UNCHANGED)
        goto skip;

    wchar_t ch = curr.base;
    char unicode[4] = {0};
    if (minigox_write_char(curr, unicode) == 0) {
        MultiByteToWideChar(CP_UTF8, 0, unicode, -1, &ch, 1);
    } else {
        goto skip;
    }

    int count = 2;

    input[count++] = (INPUT){
        .type = INPUT_KEYBOARD,
        .ki = { .wVk = 0, .wScan = ch, .dwFlags = KEYEVENTF_UNICODE },
    };
    input[count++] = (INPUT){
        .type = INPUT_KEYBOARD,
        .ki = {
            .wVk = 0,
            .wScan = ch,
            .dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP,
        },
    };

    if (result == APPLY_REVERTED) {
        input[count++] = (INPUT){
            .type = INPUT_KEYBOARD,
            .ki = { .wVk = 0, .wScan = key, .dwFlags = KEYEVENTF_UNICODE },
        };
        input[count++] = (INPUT){
            .type = INPUT_KEYBOARD,
            .ki = {
                .wVk = 0,
                .wScan = key,
                .dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP,
            },
        };
        curr = minigox_unpack_char(key);
    }

    SendInput(count, input, sizeof(INPUT));
    return 1;

skip:
    curr = minigox_unpack_char(key);
    return 0;
}

static void update_modifiers(int key_down, int vkCode) {
    switch (vkCode) {
    case VK_LSHIFT:
    case VK_RSHIFT:
        modifiers.shift = key_down;
        break;
    case VK_LCONTROL:
    case VK_RCONTROL:
        modifiers.ctrl = key_down;
        break;
    case VK_LMENU:
    case VK_RMENU:
        modifiers.alt = key_down;
        break;
    case VK_CAPITAL:
        if (key_down)
            modifiers.caps = !modifiers.caps;
        break;
    case VK_NUMLOCK:
        if (key_down)
            modifiers.num = !modifiers.num;
        break;
    case VK_SCROLL:
        if (key_down)
            modifiers.scroll = !modifiers.scroll;
        break;
    }
}

LRESULT CALLBACK keyboard_proc(int ncode, WPARAM wparam, LPARAM lparam) {
    if (ncode == HC_ACTION) {
        PKBDLLHOOKSTRUCT kbd = (PKBDLLHOOKSTRUCT)lparam;
        DWORD vkCode = kbd->vkCode;
        int key_down = (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN);

        update_modifiers(key_down, vkCode);

        if (!key_down || kbd->flags & LLKHF_INJECTED)
            goto skip;

        if (vkCode == VK_DELETE || vkCode == VK_RETURN
            || vkCode == VK_HOME || vkCode == VK_END
            || vkCode == VK_PRIOR || vkCode == VK_NEXT
            || vkCode == VK_LEFT || vkCode == VK_RIGHT
            || vkCode == VK_UP || vkCode == VK_DOWN
            || modifiers.ctrl || modifiers.alt) {
            curr = minigox_unpack_char(0);
            goto skip;
        }

        BYTE keyboard_state[256] = {0};
        if (modifiers.shift)
            keyboard_state[VK_SHIFT] |= 0x80;
        if (modifiers.caps)
            keyboard_state[VK_CAPITAL] |= 0x01;
        if (modifiers.num)
            keyboard_state[VK_NUMLOCK] |= 0x01;
        if (modifiers.scroll)
            keyboard_state[VK_SCROLL] |= 0x01;

        WCHAR buffer[16] = {0};
        if (ToUnicode(
            vkCode,
            kbd->scanCode,
            keyboard_state,
            buffer,
            ARRAYSIZE(buffer) - 1,
            0
        ) == 1 && process_key(buffer[0]))
            return 1;
    }

skip:
    return CallNextHookEx(NULL, ncode, wparam, lparam);
}

static LRESULT CALLBACK mouse_proc(int ncode, WPARAM wparam, LPARAM lparam) {
    if (ncode == HC_ACTION) {
        PMSLLHOOKSTRUCT _mouse = (PMSLLHOOKSTRUCT)lparam;

        switch (wparam) {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
            if (_mouse->pt.x != mouse.x && _mouse->pt.y != mouse.y)
                curr = minigox_unpack_char(0);

            break;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
            mouse.x = _mouse->pt.x;
            mouse.y = _mouse->pt.y;
            break;
        }
    }

    return CallNextHookEx(NULL, ncode, wparam, lparam);
}

static bool minigox_setup(void) {
    keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_proc, NULL, 0);
    mouse_hook = SetWindowsHookEx(WH_MOUSE_LL, mouse_proc, NULL, 0);

    return keyboard_hook != NULL && mouse_hook != NULL;
}

static bool minigox_run(void) {
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

static void minigox_destroy(void) {
    UnhookWindowsHookEx(keyboard_hook);
    UnhookWindowsHookEx(mouse_hook);
}

#else // _WIN32
#error "No implementation found"
#endif
