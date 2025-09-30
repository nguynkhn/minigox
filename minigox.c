#ifndef _WIN32
#error "This program is Windows-only"
#else

#include "minigox.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <windows.h>

#define ARRAY_LEN(_a) (sizeof(_a) / sizeof(_a[0]))

static struct CharInfo curr = {0};
static struct Method method = {0};

static bool ignore_sent = false;
static LONG mouse_x, mouse_y;
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

static bool process_key(char key) {
	if (ignore_sent) {
		ignore_sent = false;
		return false;
	}

	enum ApplyResult result = minigox_apply_method(method, &curr, key);
	if (result == APPLY_UNCHANGED)
		goto skip;

	wchar_t ch = curr.base;
	char *unicode = minigox_compose_char(curr);
	if (unicode != NULL) {
		MultiByteToWideChar(CP_UTF8, 0, unicode, -1, &ch, 1);
	} else {
		goto skip;
	}

	int count = 2;

	ignore_sent = true;
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
	return true;

skip:
	curr = minigox_unpack_char(key);
    return false;
}

static void reset_current(void) {}

LRESULT CALLBACK keyboard_proc(int ncode, WPARAM wparam, LPARAM lparam) {
	if (
        ncode == HC_ACTION
        && (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
    ) {
		PKBDLLHOOKSTRUCT kbd = (PKBDLLHOOKSTRUCT)lparam;
		int vkCode = kbd->vkCode;

		if (
			vkCode != VK_DELETE && vkCode != VK_RETURN
			&& vkCode != VK_HOME && vkCode != VK_END
			&& vkCode != VK_PRIOR && vkCode != VK_NEXT
			&& vkCode != VK_LEFT && vkCode != VK_RIGHT
			&& vkCode != VK_UP && vkCode != VK_RIGHT
		) {
			BYTE keyboard_state[256];
			WCHAR buffer[16] = {0};

			if (GetKeyboardState(keyboard_state)) {
				if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					keyboard_state[VK_SHIFT] |= 0x80;
				if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
					keyboard_state[VK_CONTROL] |= 0x80;
				if (GetAsyncKeyState(VK_MENU) & 0x8000)
					keyboard_state[VK_MENU] |= 0x80;
				if (GetKeyState(VK_CAPITAL) & 0x0001)
					keyboard_state[VK_CAPITAL] |= 0x01;
				if (GetKeyState(VK_NUMLOCK) & 0x0001)
					keyboard_state[VK_NUMLOCK] |= 0x01;
				if (GetKeyState(VK_SCROLL) & 0x0001)
					keyboard_state[VK_SCROLL] |= 0x01;

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
		} else {
            curr = minigox_unpack_char(0);
		}
	}

	return CallNextHookEx(NULL, ncode, wparam, lparam);
}

LRESULT CALLBACK mouse_proc(int ncode, WPARAM wparam, LPARAM lparam) {
    if (ncode == HC_ACTION) {
        PMSLLHOOKSTRUCT mouse = (PMSLLHOOKSTRUCT)lparam;

        switch (wparam) {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
            if (mouse->pt.x != mouse_x && mouse->pt.y != mouse_y)
                curr = minigox_unpack_char(0);

            break;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
            mouse_x = mouse->pt.x;
            mouse_y = mouse->pt.y;
            break;
        }
    }
	return CallNextHookEx(NULL, ncode, wparam, lparam);
}

int main(int argc, char *argv[]) {
    method.keystroke_num = ARRAY_LEN(TELEX);
    method.keystrokes = TELEX;

    if (argc > 1) {
        char *name = argv[1];

        if (strcmp(name, "vni") == 0) {
            method.keystroke_num = ARRAY_LEN(VNI);
            method.keystrokes == VNI;
        } else if (strcmp(name, "telex") != 0) {
            fprintf(stderr, "Unknown method name\n");
            return 1;
        }
    }

    HHOOK kbd_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_proc, NULL, 0);
    HHOOK mouse_hook = SetWindowsHookEx(WH_MOUSE_LL, mouse_proc, NULL, 0);
	if (kbd_hook == NULL || mouse_proc == NULL) {
		fprintf(stderr, "Failed to install hook\n");
		return 1;
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(kbd_hook);
	UnhookWindowsHookEx(mouse_hook);
    return 0;
}

#endif // _WIN32
