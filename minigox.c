#ifndef _WIN32
#error "this program is Windows-only"
#else
	
#include "minigox.h"

#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

char buf = 0;
struct Method method = {0};

void send_unicode(char *unicode) {
	wchar_t ch = 0;
	MultiByteToWideChar(CP_UTF8, 0, unicode, -1, &ch, 1);

	INPUT input[4] = {
		/* send backspace */
		{
			.type = INPUT_KEYBOARD,
			.ki = { .wVk = VK_BACK, .dwFlags = 0 },
		},
		{
			.type = INPUT_KEYBOARD,
			.ki = { .wVk = VK_BACK, .dwFlags = KEYEVENTF_KEYUP },
		},
		/* send unicode */
		{
			.type = INPUT_KEYBOARD,
			.ki = { .wVk = 0, .wScan = ch, .dwFlags = KEYEVENTF_UNICODE },
		},
		{
			.type = INPUT_KEYBOARD,
			.ki = { .wVk = 0, .wScan = ch, .dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP },
		},
	};

	SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
}

bool process_key(char key) {
	for (int i = 0; i < method.len; ++i) {
		struct Keystroke keystroke = method.keystrokes[i];

		if (key == keystroke.trigger) {
			int *combination = keystroke.combinations;

			while (*combination > 0) {
				char ch = *combination;
				if (buf == ch) {
					char *unicode = compose_char(*combination);
					send_unicode(unicode);
					return true;
				}

				++combination;
			}

			break;
		}
	}

	buf = key;
	return false;
}

LRESULT CALLBACK keyboard_proc(int ncode, WPARAM wparam, LPARAM lparam) {
	if (ncode == HC_ACTION && (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)) {
		PKBDLLHOOKSTRUCT kbd = (PKBDLLHOOKSTRUCT)lparam;
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
				kbd->vkCode,
				kbd->scanCode,
				keyboard_state,
				buffer,
				ARRAYSIZE(buffer) - 1,
				0
			) == 1) {
				if (process_key(buffer[0]))
					return 1;
			}
		}
	}

	return CallNextHookEx(NULL, ncode, wparam, lparam);
}

int main(int argc, char *argv[]) {
	// TODO: CLI
	method.len = ARRAYSIZE(TELEX);
	method.keystrokes = TELEX;

	HHOOK keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_proc, NULL, 0);
	if (keyboard_hook == NULL) {
		fprintf(stderr, "failed to install hook!\n");
		return 1;
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(keyboard_hook);
	return 0;
}

#endif // _WIN32
