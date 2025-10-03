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
static int count = 2;

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
        ) == 1 && minigox_process_char(buffer[0]))
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

static void minigox_enqueue_char(char *ch) {
    wchar_t key = *ch;
    if (ch[1] != '\0')
        MultiByteToWideChar(CP_UTF8, 0, ch, -1, &key, 1);

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
}

static void minigox_flush(void) {
    SendInput(count, input, sizeof(INPUT));
    count = 2;
}
