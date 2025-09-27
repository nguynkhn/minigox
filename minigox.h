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

#define BASE_LETTER(_c) (_c & 0xFF)
#define LETTER_MODIFICATION(_c) ((_c >> 8) & 0xF)
#define TONE_MARK(_c) ((_c >> 12) & 0xF)

struct Keystroke {
	char trigger;
	int *conversions;
};

struct Method {
	size_t len;
	struct Keystroke *keystrokes;
};

#define KEYSTROKE_DEFINE(_t, ...) { _t, (int []){ __VA_ARGS__, 0 } }
static struct Keystroke TELEX[] = {
	/* generated with mapping.py */
	KEYSTROKE_DEFINE('f', TONE_GRAVE),
    KEYSTROKE_DEFINE('s', TONE_ACUTE),
    KEYSTROKE_DEFINE('r', TONE_HOOK_ABOVE),
    KEYSTROKE_DEFINE('x', TONE_TILDE),
    KEYSTROKE_DEFINE('j', TONE_UNDERDOT),
    KEYSTROKE_DEFINE('a', 'a' | MOD_CIRCUMFLEX),
    KEYSTROKE_DEFINE('d', 'd' | MOD_STROKE),
    KEYSTROKE_DEFINE('e', 'e' | MOD_CIRCUMFLEX),
    KEYSTROKE_DEFINE('o', 'o' | MOD_CIRCUMFLEX),
    KEYSTROKE_DEFINE('w', 'a' | MOD_BREVE,
                          'o' | MOD_HORN,
                          'u' | MOD_HORN),
};

char *compose_char(int combination) {
	switch (combination) {
	/* generated with mapping.py  */
	case 'a' | MOD_NONE       | TONE_GRAVE:      return "à";
    case 'a' | MOD_NONE       | TONE_ACUTE:      return "á";
    case 'a' | MOD_NONE       | TONE_HOOK_ABOVE: return "ả";
    case 'a' | MOD_NONE       | TONE_TILDE:      return "ã";
    case 'a' | MOD_NONE       | TONE_UNDERDOT:   return "ạ";
    case 'a' | MOD_BREVE      | TONE_UNMARKED:   return "ă";
    case 'a' | MOD_BREVE      | TONE_GRAVE:      return "ằ";
    case 'a' | MOD_BREVE      | TONE_ACUTE:      return "ắ";
    case 'a' | MOD_BREVE      | TONE_HOOK_ABOVE: return "ẳ";
    case 'a' | MOD_BREVE      | TONE_TILDE:      return "ẵ";
    case 'a' | MOD_BREVE      | TONE_UNDERDOT:   return "ặ";
    case 'a' | MOD_CIRCUMFLEX | TONE_UNMARKED:   return "â";
    case 'a' | MOD_CIRCUMFLEX | TONE_GRAVE:      return "ầ";
    case 'a' | MOD_CIRCUMFLEX | TONE_ACUTE:      return "ấ";
    case 'a' | MOD_CIRCUMFLEX | TONE_HOOK_ABOVE: return "ẩ";
    case 'a' | MOD_CIRCUMFLEX | TONE_TILDE:      return "ẫ";
    case 'a' | MOD_CIRCUMFLEX | TONE_UNDERDOT:   return "ậ";
    case 'd' | MOD_STROKE     | TONE_UNMARKED:   return "đ";
    case 'e' | MOD_NONE       | TONE_GRAVE:      return "è";
    case 'e' | MOD_NONE       | TONE_ACUTE:      return "é";
    case 'e' | MOD_NONE       | TONE_HOOK_ABOVE: return "ẻ";
    case 'e' | MOD_NONE       | TONE_TILDE:      return "ẽ";
    case 'e' | MOD_NONE       | TONE_UNDERDOT:   return "ẹ";
    case 'e' | MOD_CIRCUMFLEX | TONE_UNMARKED:   return "ê";
    case 'e' | MOD_CIRCUMFLEX | TONE_GRAVE:      return "ề";
    case 'e' | MOD_CIRCUMFLEX | TONE_ACUTE:      return "ế";
    case 'e' | MOD_CIRCUMFLEX | TONE_HOOK_ABOVE: return "ể";
    case 'e' | MOD_CIRCUMFLEX | TONE_TILDE:      return "ễ";
    case 'e' | MOD_CIRCUMFLEX | TONE_UNDERDOT:   return "ệ";
    case 'i' | MOD_NONE       | TONE_GRAVE:      return "ì";
    case 'i' | MOD_NONE       | TONE_ACUTE:      return "í";
    case 'i' | MOD_NONE       | TONE_HOOK_ABOVE: return "ỉ";
    case 'i' | MOD_NONE       | TONE_TILDE:      return "ĩ";
    case 'i' | MOD_NONE       | TONE_UNDERDOT:   return "ị";
    case 'o' | MOD_NONE       | TONE_GRAVE:      return "ò";
    case 'o' | MOD_NONE       | TONE_ACUTE:      return "ó";
    case 'o' | MOD_NONE       | TONE_HOOK_ABOVE: return "ỏ";
    case 'o' | MOD_NONE       | TONE_TILDE:      return "õ";
    case 'o' | MOD_NONE       | TONE_UNDERDOT:   return "ọ";
    case 'o' | MOD_CIRCUMFLEX | TONE_UNMARKED:   return "ô";
    case 'o' | MOD_CIRCUMFLEX | TONE_GRAVE:      return "ồ";
    case 'o' | MOD_CIRCUMFLEX | TONE_ACUTE:      return "ố";
    case 'o' | MOD_CIRCUMFLEX | TONE_HOOK_ABOVE: return "ổ";
    case 'o' | MOD_CIRCUMFLEX | TONE_TILDE:      return "ỗ";
    case 'o' | MOD_CIRCUMFLEX | TONE_UNDERDOT:   return "ộ";
    case 'o' | MOD_HORN       | TONE_UNMARKED:   return "ơ";
    case 'o' | MOD_HORN       | TONE_GRAVE:      return "ờ";
    case 'o' | MOD_HORN       | TONE_ACUTE:      return "ớ";
    case 'o' | MOD_HORN       | TONE_HOOK_ABOVE: return "ở";
    case 'o' | MOD_HORN       | TONE_TILDE:      return "ỡ";
    case 'o' | MOD_HORN       | TONE_UNDERDOT:   return "ợ";
    case 'u' | MOD_NONE       | TONE_GRAVE:      return "ù";
    case 'u' | MOD_NONE       | TONE_ACUTE:      return "ú";
    case 'u' | MOD_NONE       | TONE_HOOK_ABOVE: return "ủ";
    case 'u' | MOD_NONE       | TONE_TILDE:      return "ũ";
    case 'u' | MOD_NONE       | TONE_UNDERDOT:   return "ụ";
    case 'u' | MOD_HORN       | TONE_UNMARKED:   return "ư";
    case 'u' | MOD_HORN       | TONE_GRAVE:      return "ừ";
    case 'u' | MOD_HORN       | TONE_ACUTE:      return "ứ";
    case 'u' | MOD_HORN       | TONE_HOOK_ABOVE: return "ử";
    case 'u' | MOD_HORN       | TONE_TILDE:      return "ữ";
    case 'u' | MOD_HORN       | TONE_UNDERDOT:   return "ự";
    case 'y' | MOD_NONE       | TONE_GRAVE:      return "ỳ";
    case 'y' | MOD_NONE       | TONE_ACUTE:      return "ý";
    case 'y' | MOD_NONE       | TONE_HOOK_ABOVE: return "ỷ";
    case 'y' | MOD_NONE       | TONE_TILDE:      return "ỹ";
    case 'y' | MOD_NONE       | TONE_UNDERDOT:   return "ỵ";
	default:                                     return NULL;
	}
}
