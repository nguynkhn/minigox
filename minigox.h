#include <stddef.h>

enum LetterModification {
	MOD_NONE       = 0 << 12,
	MOD_BREVE      = 1 << 12,
	MOD_CIRCUMFLEX = 2 << 12,
	MOD_HORN       = 3 << 12,
	MOD_STROKE     = 4 << 12,
};

enum ToneMark {
	TONE_UNMARKED   = 0 << 8,
	TONE_GRAVE      = 1 << 8,
	TONE_ACUTE      = 2 << 8,
	TONE_HOOK_ABOVE = 3 << 8,
	TONE_TILDE      = 4 << 8,
	TONE_UNDERDOT   = 5 << 8,
};

struct Keystroke {
	char trigger;
	int *combinations;
};

struct Method {
	size_t len;
	struct Keystroke *keystrokes;
};

#define KEYSTROKE_DEFINE(_t, ...) { _t, (int []){ __VA_ARGS__, 0 } }
static struct Keystroke TELEX[] = {
	/* generated with mapping.py */
    KEYSTROKE_DEFINE('a', 'A' | TONE_UNMARKED   | MOD_CIRCUMFLEX,
                          'a' | TONE_UNMARKED   | MOD_CIRCUMFLEX,
                          'A' | TONE_GRAVE      | MOD_CIRCUMFLEX,
                          'a' | TONE_GRAVE      | MOD_CIRCUMFLEX,
                          'A' | TONE_ACUTE      | MOD_CIRCUMFLEX,
                          'a' | TONE_ACUTE      | MOD_CIRCUMFLEX,
                          'A' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'a' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'A' | TONE_TILDE      | MOD_CIRCUMFLEX,
                          'a' | TONE_TILDE      | MOD_CIRCUMFLEX,
                          'A' | TONE_UNDERDOT   | MOD_CIRCUMFLEX,
                          'a' | TONE_UNDERDOT   | MOD_CIRCUMFLEX),
    KEYSTROKE_DEFINE('d', 'D' | TONE_UNMARKED | MOD_STROKE,
                          'd' | TONE_UNMARKED | MOD_STROKE),
    KEYSTROKE_DEFINE('e', 'E' | TONE_UNMARKED   | MOD_CIRCUMFLEX,
                          'e' | TONE_UNMARKED   | MOD_CIRCUMFLEX,
                          'E' | TONE_GRAVE      | MOD_CIRCUMFLEX,
                          'e' | TONE_GRAVE      | MOD_CIRCUMFLEX,
                          'E' | TONE_ACUTE      | MOD_CIRCUMFLEX,
                          'e' | TONE_ACUTE      | MOD_CIRCUMFLEX,
                          'E' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'e' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'E' | TONE_TILDE      | MOD_CIRCUMFLEX,
                          'e' | TONE_TILDE      | MOD_CIRCUMFLEX,
                          'E' | TONE_UNDERDOT   | MOD_CIRCUMFLEX,
                          'e' | TONE_UNDERDOT   | MOD_CIRCUMFLEX),
    KEYSTROKE_DEFINE('f', 'A' | TONE_GRAVE | MOD_NONE,
                          'E' | TONE_GRAVE | MOD_NONE,
                          'I' | TONE_GRAVE | MOD_NONE,
                          'O' | TONE_GRAVE | MOD_NONE,
                          'U' | TONE_GRAVE | MOD_NONE,
                          'Y' | TONE_GRAVE | MOD_NONE,
                          'a' | TONE_GRAVE | MOD_NONE,
                          'e' | TONE_GRAVE | MOD_NONE,
                          'i' | TONE_GRAVE | MOD_NONE,
                          'o' | TONE_GRAVE | MOD_NONE,
                          'u' | TONE_GRAVE | MOD_NONE,
                          'y' | TONE_GRAVE | MOD_NONE,
                          'A' | TONE_GRAVE | MOD_BREVE,
                          'a' | TONE_GRAVE | MOD_BREVE,
                          'A' | TONE_GRAVE | MOD_CIRCUMFLEX,
                          'E' | TONE_GRAVE | MOD_CIRCUMFLEX,
                          'O' | TONE_GRAVE | MOD_CIRCUMFLEX,
                          'a' | TONE_GRAVE | MOD_CIRCUMFLEX,
                          'e' | TONE_GRAVE | MOD_CIRCUMFLEX,
                          'o' | TONE_GRAVE | MOD_CIRCUMFLEX,
                          'O' | TONE_GRAVE | MOD_HORN,
                          'U' | TONE_GRAVE | MOD_HORN,
                          'o' | TONE_GRAVE | MOD_HORN,
                          'u' | TONE_GRAVE | MOD_HORN),
    KEYSTROKE_DEFINE('j', 'A' | TONE_UNDERDOT | MOD_NONE,
                          'E' | TONE_UNDERDOT | MOD_NONE,
                          'I' | TONE_UNDERDOT | MOD_NONE,
                          'O' | TONE_UNDERDOT | MOD_NONE,
                          'U' | TONE_UNDERDOT | MOD_NONE,
                          'Y' | TONE_UNDERDOT | MOD_NONE,
                          'a' | TONE_UNDERDOT | MOD_NONE,
                          'e' | TONE_UNDERDOT | MOD_NONE,
                          'i' | TONE_UNDERDOT | MOD_NONE,
                          'o' | TONE_UNDERDOT | MOD_NONE,
                          'u' | TONE_UNDERDOT | MOD_NONE,
                          'y' | TONE_UNDERDOT | MOD_NONE,
                          'A' | TONE_UNDERDOT | MOD_BREVE,
                          'a' | TONE_UNDERDOT | MOD_BREVE,
                          'A' | TONE_UNDERDOT | MOD_CIRCUMFLEX,
                          'E' | TONE_UNDERDOT | MOD_CIRCUMFLEX,
                          'O' | TONE_UNDERDOT | MOD_CIRCUMFLEX,
                          'a' | TONE_UNDERDOT | MOD_CIRCUMFLEX,
                          'e' | TONE_UNDERDOT | MOD_CIRCUMFLEX,
                          'o' | TONE_UNDERDOT | MOD_CIRCUMFLEX,
                          'O' | TONE_UNDERDOT | MOD_HORN,
                          'U' | TONE_UNDERDOT | MOD_HORN,
                          'o' | TONE_UNDERDOT | MOD_HORN,
                          'u' | TONE_UNDERDOT | MOD_HORN),
    KEYSTROKE_DEFINE('o', 'O' | TONE_UNMARKED   | MOD_CIRCUMFLEX,
                          'o' | TONE_UNMARKED   | MOD_CIRCUMFLEX,
                          'O' | TONE_GRAVE      | MOD_CIRCUMFLEX,
                          'o' | TONE_GRAVE      | MOD_CIRCUMFLEX,
                          'O' | TONE_ACUTE      | MOD_CIRCUMFLEX,
                          'o' | TONE_ACUTE      | MOD_CIRCUMFLEX,
                          'O' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'o' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'O' | TONE_TILDE      | MOD_CIRCUMFLEX,
                          'o' | TONE_TILDE      | MOD_CIRCUMFLEX,
                          'O' | TONE_UNDERDOT   | MOD_CIRCUMFLEX,
                          'o' | TONE_UNDERDOT   | MOD_CIRCUMFLEX),
    KEYSTROKE_DEFINE('r', 'A' | TONE_HOOK_ABOVE | MOD_NONE,
                          'E' | TONE_HOOK_ABOVE | MOD_NONE,
                          'I' | TONE_HOOK_ABOVE | MOD_NONE,
                          'O' | TONE_HOOK_ABOVE | MOD_NONE,
                          'U' | TONE_HOOK_ABOVE | MOD_NONE,
                          'Y' | TONE_HOOK_ABOVE | MOD_NONE,
                          'a' | TONE_HOOK_ABOVE | MOD_NONE,
                          'e' | TONE_HOOK_ABOVE | MOD_NONE,
                          'i' | TONE_HOOK_ABOVE | MOD_NONE,
                          'o' | TONE_HOOK_ABOVE | MOD_NONE,
                          'u' | TONE_HOOK_ABOVE | MOD_NONE,
                          'y' | TONE_HOOK_ABOVE | MOD_NONE,
                          'A' | TONE_HOOK_ABOVE | MOD_BREVE,
                          'a' | TONE_HOOK_ABOVE | MOD_BREVE,
                          'A' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'E' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'O' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'a' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'e' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'o' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX,
                          'O' | TONE_HOOK_ABOVE | MOD_HORN,
                          'U' | TONE_HOOK_ABOVE | MOD_HORN,
                          'o' | TONE_HOOK_ABOVE | MOD_HORN,
                          'u' | TONE_HOOK_ABOVE | MOD_HORN),
    KEYSTROKE_DEFINE('s', 'A' | TONE_ACUTE | MOD_NONE,
                          'E' | TONE_ACUTE | MOD_NONE,
                          'I' | TONE_ACUTE | MOD_NONE,
                          'O' | TONE_ACUTE | MOD_NONE,
                          'U' | TONE_ACUTE | MOD_NONE,
                          'Y' | TONE_ACUTE | MOD_NONE,
                          'a' | TONE_ACUTE | MOD_NONE,
                          'e' | TONE_ACUTE | MOD_NONE,
                          'i' | TONE_ACUTE | MOD_NONE,
                          'o' | TONE_ACUTE | MOD_NONE,
                          'u' | TONE_ACUTE | MOD_NONE,
                          'y' | TONE_ACUTE | MOD_NONE,
                          'A' | TONE_ACUTE | MOD_BREVE,
                          'a' | TONE_ACUTE | MOD_BREVE,
                          'A' | TONE_ACUTE | MOD_CIRCUMFLEX,
                          'E' | TONE_ACUTE | MOD_CIRCUMFLEX,
                          'O' | TONE_ACUTE | MOD_CIRCUMFLEX,
                          'a' | TONE_ACUTE | MOD_CIRCUMFLEX,
                          'e' | TONE_ACUTE | MOD_CIRCUMFLEX,
                          'o' | TONE_ACUTE | MOD_CIRCUMFLEX,
                          'O' | TONE_ACUTE | MOD_HORN,
                          'U' | TONE_ACUTE | MOD_HORN,
                          'o' | TONE_ACUTE | MOD_HORN,
                          'u' | TONE_ACUTE | MOD_HORN),
    KEYSTROKE_DEFINE('w', 'A' | TONE_UNMARKED   | MOD_BREVE,
                          'a' | TONE_UNMARKED   | MOD_BREVE,
                          'A' | TONE_GRAVE      | MOD_BREVE,
                          'a' | TONE_GRAVE      | MOD_BREVE,
                          'A' | TONE_ACUTE      | MOD_BREVE,
                          'a' | TONE_ACUTE      | MOD_BREVE,
                          'A' | TONE_HOOK_ABOVE | MOD_BREVE,
                          'a' | TONE_HOOK_ABOVE | MOD_BREVE,
                          'A' | TONE_TILDE      | MOD_BREVE,
                          'a' | TONE_TILDE      | MOD_BREVE,
                          'A' | TONE_UNDERDOT   | MOD_BREVE,
                          'a' | TONE_UNDERDOT   | MOD_BREVE,
                          'O' | TONE_UNMARKED   | MOD_HORN,
                          'U' | TONE_UNMARKED   | MOD_HORN,
                          'o' | TONE_UNMARKED   | MOD_HORN,
                          'u' | TONE_UNMARKED   | MOD_HORN,
                          'O' | TONE_GRAVE      | MOD_HORN,
                          'U' | TONE_GRAVE      | MOD_HORN,
                          'o' | TONE_GRAVE      | MOD_HORN,
                          'u' | TONE_GRAVE      | MOD_HORN,
                          'O' | TONE_ACUTE      | MOD_HORN,
                          'U' | TONE_ACUTE      | MOD_HORN,
                          'o' | TONE_ACUTE      | MOD_HORN,
                          'u' | TONE_ACUTE      | MOD_HORN,
                          'O' | TONE_HOOK_ABOVE | MOD_HORN,
                          'U' | TONE_HOOK_ABOVE | MOD_HORN,
                          'o' | TONE_HOOK_ABOVE | MOD_HORN,
                          'u' | TONE_HOOK_ABOVE | MOD_HORN,
                          'O' | TONE_TILDE      | MOD_HORN,
                          'U' | TONE_TILDE      | MOD_HORN,
                          'o' | TONE_TILDE      | MOD_HORN,
                          'u' | TONE_TILDE      | MOD_HORN,
                          'O' | TONE_UNDERDOT   | MOD_HORN,
                          'U' | TONE_UNDERDOT   | MOD_HORN,
                          'o' | TONE_UNDERDOT   | MOD_HORN,
                          'u' | TONE_UNDERDOT   | MOD_HORN),
    KEYSTROKE_DEFINE('x', 'A' | TONE_TILDE | MOD_NONE,
                          'E' | TONE_TILDE | MOD_NONE,
                          'I' | TONE_TILDE | MOD_NONE,
                          'O' | TONE_TILDE | MOD_NONE,
                          'U' | TONE_TILDE | MOD_NONE,
                          'Y' | TONE_TILDE | MOD_NONE,
                          'a' | TONE_TILDE | MOD_NONE,
                          'e' | TONE_TILDE | MOD_NONE,
                          'i' | TONE_TILDE | MOD_NONE,
                          'o' | TONE_TILDE | MOD_NONE,
                          'u' | TONE_TILDE | MOD_NONE,
                          'y' | TONE_TILDE | MOD_NONE,
                          'A' | TONE_TILDE | MOD_BREVE,
                          'a' | TONE_TILDE | MOD_BREVE,
                          'A' | TONE_TILDE | MOD_CIRCUMFLEX,
                          'E' | TONE_TILDE | MOD_CIRCUMFLEX,
                          'O' | TONE_TILDE | MOD_CIRCUMFLEX,
                          'a' | TONE_TILDE | MOD_CIRCUMFLEX,
                          'e' | TONE_TILDE | MOD_CIRCUMFLEX,
                          'o' | TONE_TILDE | MOD_CIRCUMFLEX,
                          'O' | TONE_TILDE | MOD_HORN,
                          'U' | TONE_TILDE | MOD_HORN,
                          'o' | TONE_TILDE | MOD_HORN,
                          'u' | TONE_TILDE | MOD_HORN),
};

char *compose_char(int combination) {
	switch (combination) {
	/* generated with mapping.py */
    case 'A' | TONE_GRAVE      | MOD_NONE:       return "À";
    case 'E' | TONE_GRAVE      | MOD_NONE:       return "È";
    case 'I' | TONE_GRAVE      | MOD_NONE:       return "Ì";
    case 'O' | TONE_GRAVE      | MOD_NONE:       return "Ò";
    case 'U' | TONE_GRAVE      | MOD_NONE:       return "Ù";
    case 'Y' | TONE_GRAVE      | MOD_NONE:       return "Ỳ";
    case 'a' | TONE_GRAVE      | MOD_NONE:       return "à";
    case 'e' | TONE_GRAVE      | MOD_NONE:       return "è";
    case 'i' | TONE_GRAVE      | MOD_NONE:       return "ì";
    case 'o' | TONE_GRAVE      | MOD_NONE:       return "ò";
    case 'u' | TONE_GRAVE      | MOD_NONE:       return "ù";
    case 'y' | TONE_GRAVE      | MOD_NONE:       return "ỳ";
    case 'A' | TONE_ACUTE      | MOD_NONE:       return "Á";
    case 'E' | TONE_ACUTE      | MOD_NONE:       return "É";
    case 'I' | TONE_ACUTE      | MOD_NONE:       return "Í";
    case 'O' | TONE_ACUTE      | MOD_NONE:       return "Ó";
    case 'U' | TONE_ACUTE      | MOD_NONE:       return "Ú";
    case 'Y' | TONE_ACUTE      | MOD_NONE:       return "Ý";
    case 'a' | TONE_ACUTE      | MOD_NONE:       return "á";
    case 'e' | TONE_ACUTE      | MOD_NONE:       return "é";
    case 'i' | TONE_ACUTE      | MOD_NONE:       return "í";
    case 'o' | TONE_ACUTE      | MOD_NONE:       return "ó";
    case 'u' | TONE_ACUTE      | MOD_NONE:       return "ú";
    case 'y' | TONE_ACUTE      | MOD_NONE:       return "ý";
    case 'A' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ả";
    case 'E' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ẻ";
    case 'I' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ỉ";
    case 'O' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ỏ";
    case 'U' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ủ";
    case 'Y' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ỷ";
    case 'a' | TONE_HOOK_ABOVE | MOD_NONE:       return "ả";
    case 'e' | TONE_HOOK_ABOVE | MOD_NONE:       return "ẻ";
    case 'i' | TONE_HOOK_ABOVE | MOD_NONE:       return "ỉ";
    case 'o' | TONE_HOOK_ABOVE | MOD_NONE:       return "ỏ";
    case 'u' | TONE_HOOK_ABOVE | MOD_NONE:       return "ủ";
    case 'y' | TONE_HOOK_ABOVE | MOD_NONE:       return "ỷ";
    case 'A' | TONE_TILDE      | MOD_NONE:       return "Ã";
    case 'E' | TONE_TILDE      | MOD_NONE:       return "Ẽ";
    case 'I' | TONE_TILDE      | MOD_NONE:       return "Ĩ";
    case 'O' | TONE_TILDE      | MOD_NONE:       return "Õ";
    case 'U' | TONE_TILDE      | MOD_NONE:       return "Ũ";
    case 'Y' | TONE_TILDE      | MOD_NONE:       return "Ỹ";
    case 'a' | TONE_TILDE      | MOD_NONE:       return "ã";
    case 'e' | TONE_TILDE      | MOD_NONE:       return "ẽ";
    case 'i' | TONE_TILDE      | MOD_NONE:       return "ĩ";
    case 'o' | TONE_TILDE      | MOD_NONE:       return "õ";
    case 'u' | TONE_TILDE      | MOD_NONE:       return "ũ";
    case 'y' | TONE_TILDE      | MOD_NONE:       return "ỹ";
    case 'A' | TONE_UNDERDOT   | MOD_NONE:       return "Ạ";
    case 'E' | TONE_UNDERDOT   | MOD_NONE:       return "Ẹ";
    case 'I' | TONE_UNDERDOT   | MOD_NONE:       return "Ị";
    case 'O' | TONE_UNDERDOT   | MOD_NONE:       return "Ọ";
    case 'U' | TONE_UNDERDOT   | MOD_NONE:       return "Ụ";
    case 'Y' | TONE_UNDERDOT   | MOD_NONE:       return "Ỵ";
    case 'a' | TONE_UNDERDOT   | MOD_NONE:       return "ạ";
    case 'e' | TONE_UNDERDOT   | MOD_NONE:       return "ẹ";
    case 'i' | TONE_UNDERDOT   | MOD_NONE:       return "ị";
    case 'o' | TONE_UNDERDOT   | MOD_NONE:       return "ọ";
    case 'u' | TONE_UNDERDOT   | MOD_NONE:       return "ụ";
    case 'y' | TONE_UNDERDOT   | MOD_NONE:       return "ỵ";
    case 'A' | TONE_UNMARKED   | MOD_BREVE:      return "Ă";
    case 'a' | TONE_UNMARKED   | MOD_BREVE:      return "ă";
    case 'A' | TONE_GRAVE      | MOD_BREVE:      return "Ằ";
    case 'a' | TONE_GRAVE      | MOD_BREVE:      return "ằ";
    case 'A' | TONE_ACUTE      | MOD_BREVE:      return "Ắ";
    case 'a' | TONE_ACUTE      | MOD_BREVE:      return "ắ";
    case 'A' | TONE_HOOK_ABOVE | MOD_BREVE:      return "Ẳ";
    case 'a' | TONE_HOOK_ABOVE | MOD_BREVE:      return "ẳ";
    case 'A' | TONE_TILDE      | MOD_BREVE:      return "Ẵ";
    case 'a' | TONE_TILDE      | MOD_BREVE:      return "ẵ";
    case 'A' | TONE_UNDERDOT   | MOD_BREVE:      return "Ặ";
    case 'a' | TONE_UNDERDOT   | MOD_BREVE:      return "ặ";
    case 'A' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "Â";
    case 'E' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "Ê";
    case 'O' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "Ô";
    case 'a' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "â";
    case 'e' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "ê";
    case 'o' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "ô";
    case 'A' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "Ầ";
    case 'E' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "Ề";
    case 'O' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "Ồ";
    case 'a' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "ầ";
    case 'e' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "ề";
    case 'o' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "ồ";
    case 'A' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "Ấ";
    case 'E' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "Ế";
    case 'O' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "Ố";
    case 'a' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "ấ";
    case 'e' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "ế";
    case 'o' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "ố";
    case 'A' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "Ẩ";
    case 'E' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "Ể";
    case 'O' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "Ổ";
    case 'a' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "ẩ";
    case 'e' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "ể";
    case 'o' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "ổ";
    case 'A' | TONE_TILDE      | MOD_CIRCUMFLEX: return "Ẫ";
    case 'E' | TONE_TILDE      | MOD_CIRCUMFLEX: return "Ễ";
    case 'O' | TONE_TILDE      | MOD_CIRCUMFLEX: return "Ỗ";
    case 'a' | TONE_TILDE      | MOD_CIRCUMFLEX: return "ẫ";
    case 'e' | TONE_TILDE      | MOD_CIRCUMFLEX: return "ễ";
    case 'o' | TONE_TILDE      | MOD_CIRCUMFLEX: return "ỗ";
    case 'A' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "Ậ";
    case 'E' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "Ệ";
    case 'O' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "Ộ";
    case 'a' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "ậ";
    case 'e' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "ệ";
    case 'o' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "ộ";
    case 'O' | TONE_UNMARKED   | MOD_HORN:       return "Ơ";
    case 'U' | TONE_UNMARKED   | MOD_HORN:       return "Ư";
    case 'o' | TONE_UNMARKED   | MOD_HORN:       return "ơ";
    case 'u' | TONE_UNMARKED   | MOD_HORN:       return "ư";
    case 'O' | TONE_GRAVE      | MOD_HORN:       return "Ờ";
    case 'U' | TONE_GRAVE      | MOD_HORN:       return "Ừ";
    case 'o' | TONE_GRAVE      | MOD_HORN:       return "ờ";
    case 'u' | TONE_GRAVE      | MOD_HORN:       return "ừ";
    case 'O' | TONE_ACUTE      | MOD_HORN:       return "Ớ";
    case 'U' | TONE_ACUTE      | MOD_HORN:       return "Ứ";
    case 'o' | TONE_ACUTE      | MOD_HORN:       return "ớ";
    case 'u' | TONE_ACUTE      | MOD_HORN:       return "ứ";
    case 'O' | TONE_HOOK_ABOVE | MOD_HORN:       return "Ở";
    case 'U' | TONE_HOOK_ABOVE | MOD_HORN:       return "Ử";
    case 'o' | TONE_HOOK_ABOVE | MOD_HORN:       return "ở";
    case 'u' | TONE_HOOK_ABOVE | MOD_HORN:       return "ử";
    case 'O' | TONE_TILDE      | MOD_HORN:       return "Ỡ";
    case 'U' | TONE_TILDE      | MOD_HORN:       return "Ữ";
    case 'o' | TONE_TILDE      | MOD_HORN:       return "ỡ";
    case 'u' | TONE_TILDE      | MOD_HORN:       return "ữ";
    case 'O' | TONE_UNDERDOT   | MOD_HORN:       return "Ợ";
    case 'U' | TONE_UNDERDOT   | MOD_HORN:       return "Ự";
    case 'o' | TONE_UNDERDOT   | MOD_HORN:       return "ợ";
    case 'u' | TONE_UNDERDOT   | MOD_HORN:       return "ự";
    case 'D' | TONE_UNMARKED   | MOD_STROKE:     return "Đ";
    case 'd' | TONE_UNMARKED   | MOD_STROKE:     return "đ";
	default:                                     return NULL;
	}
}
