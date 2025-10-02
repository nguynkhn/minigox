#ifndef MINIGOX_H
#define MINIGOX_H

#include <ctype.h>
#include <stdint.h>

enum ToneMark {
    TONE_UNMARKED   = 0 << 8,
    TONE_GRAVE      = 1 << 8,
    TONE_ACUTE      = 2 << 8,
    TONE_HOOK_ABOVE = 3 << 8,
    TONE_TILDE      = 4 << 8,
    TONE_UNDERDOT   = 5 << 8,

    TONE_RESET      = 0xF << 8,
};

enum LetterModification {
    MOD_NONE        = 0 << 12,
    MOD_BREVE       = 1 << 12,
    MOD_CIRCUMFLEX  = 2 << 12,
    MOD_HORN        = 3 << 12,
    MOD_STROKE      = 4 << 12,

    MOD_RESET       = 0xF << 12,
};

typedef uint16_t pchar_t;

static inline int is_vowel(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y'
        || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

static inline int is_modifiable(char c) {
    return c == 'd' || c == 'D' || is_vowel(c);
}

#define BASE_MASK   0x00FF
#define TONE_MASK   0x0F00
#define MOD_MASK    0xF000

struct CharInfo {
    char                    base;
    enum ToneMark           tone;
    enum LetterModification mod;
};

static inline struct CharInfo minigox_unpack_char(pchar_t ch) {
    return (struct CharInfo){
        .base = ch & BASE_MASK,
        .tone = ch & TONE_MASK,
        .mod  = ch & MOD_MASK,
    };
}

/*
 * Compose to an UTF-8 character
 * - If `dest` is NULL, return the size of the character without
 *   the null terminator
 * - Otherwise, store the character in `dest` and return 0 or
 *   return -1 if no such combination is found
 */
int minigox_compose_char(struct CharInfo info, char *dest) {
    int len = (info.tone != TONE_UNMARKED) + (info.mod != MOD_NONE) + 1;

    if (!dest)
        return len;
    if (len == 1) {
        *dest++ = info.base;
        *dest++ = '\0';
        return 0;
    }

    pchar_t ch = info.base | info.tone | info.mod;
    char *unicode;

    switch (ch) {
    /* generated with mapping.py */
    case 'A' | TONE_GRAVE      | MOD_NONE:       unicode = "À"; break;
    case 'A' | TONE_ACUTE      | MOD_NONE:       unicode = "Á"; break;
    case 'A' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "Ả"; break;
    case 'A' | TONE_TILDE      | MOD_NONE:       unicode = "Ã"; break;
    case 'A' | TONE_UNDERDOT   | MOD_NONE:       unicode = "Ạ"; break;
    case 'A' | TONE_UNMARKED   | MOD_BREVE:      unicode = "Ă"; break;
    case 'A' | TONE_GRAVE      | MOD_BREVE:      unicode = "Ằ"; break;
    case 'A' | TONE_ACUTE      | MOD_BREVE:      unicode = "Ắ"; break;
    case 'A' | TONE_HOOK_ABOVE | MOD_BREVE:      unicode = "Ẳ"; break;
    case 'A' | TONE_TILDE      | MOD_BREVE:      unicode = "Ẵ"; break;
    case 'A' | TONE_UNDERDOT   | MOD_BREVE:      unicode = "Ặ"; break;
    case 'A' | TONE_UNMARKED   | MOD_CIRCUMFLEX: unicode = "Â"; break;
    case 'A' | TONE_GRAVE      | MOD_CIRCUMFLEX: unicode = "Ầ"; break;
    case 'A' | TONE_ACUTE      | MOD_CIRCUMFLEX: unicode = "Ấ"; break;
    case 'A' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: unicode = "Ẩ"; break;
    case 'A' | TONE_TILDE      | MOD_CIRCUMFLEX: unicode = "Ẫ"; break;
    case 'A' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: unicode = "Ậ"; break;
    case 'D' | TONE_UNMARKED   | MOD_STROKE:     unicode = "Đ"; break;
    case 'E' | TONE_UNMARKED   | MOD_NONE:       unicode = "E"; break;
    case 'E' | TONE_GRAVE      | MOD_NONE:       unicode = "È"; break;
    case 'E' | TONE_ACUTE      | MOD_NONE:       unicode = "É"; break;
    case 'E' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "Ẻ"; break;
    case 'E' | TONE_TILDE      | MOD_NONE:       unicode = "Ẽ"; break;
    case 'E' | TONE_UNDERDOT   | MOD_NONE:       unicode = "Ẹ"; break;
    case 'E' | TONE_UNMARKED   | MOD_CIRCUMFLEX: unicode = "Ê"; break;
    case 'E' | TONE_GRAVE      | MOD_CIRCUMFLEX: unicode = "Ề"; break;
    case 'E' | TONE_ACUTE      | MOD_CIRCUMFLEX: unicode = "Ế"; break;
    case 'E' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: unicode = "Ể"; break;
    case 'E' | TONE_TILDE      | MOD_CIRCUMFLEX: unicode = "Ễ"; break;
    case 'E' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: unicode = "Ệ"; break;
    case 'I' | TONE_GRAVE      | MOD_NONE:       unicode = "Ì"; break;
    case 'I' | TONE_ACUTE      | MOD_NONE:       unicode = "Í"; break;
    case 'I' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "Ỉ"; break;
    case 'I' | TONE_TILDE      | MOD_NONE:       unicode = "Ĩ"; break;
    case 'I' | TONE_UNDERDOT   | MOD_NONE:       unicode = "Ị"; break;
    case 'O' | TONE_GRAVE      | MOD_NONE:       unicode = "Ò"; break;
    case 'O' | TONE_ACUTE      | MOD_NONE:       unicode = "Ó"; break;
    case 'O' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "Ỏ"; break;
    case 'O' | TONE_TILDE      | MOD_NONE:       unicode = "Õ"; break;
    case 'O' | TONE_UNDERDOT   | MOD_NONE:       unicode = "Ọ"; break;
    case 'O' | TONE_UNMARKED   | MOD_CIRCUMFLEX: unicode = "Ô"; break;
    case 'O' | TONE_GRAVE      | MOD_CIRCUMFLEX: unicode = "Ồ"; break;
    case 'O' | TONE_ACUTE      | MOD_CIRCUMFLEX: unicode = "Ố"; break;
    case 'O' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: unicode = "Ổ"; break;
    case 'O' | TONE_TILDE      | MOD_CIRCUMFLEX: unicode = "Ỗ"; break;
    case 'O' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: unicode = "Ộ"; break;
    case 'O' | TONE_UNMARKED   | MOD_HORN:       unicode = "Ơ"; break;
    case 'O' | TONE_GRAVE      | MOD_HORN:       unicode = "Ờ"; break;
    case 'O' | TONE_ACUTE      | MOD_HORN:       unicode = "Ớ"; break;
    case 'O' | TONE_HOOK_ABOVE | MOD_HORN:       unicode = "Ở"; break;
    case 'O' | TONE_TILDE      | MOD_HORN:       unicode = "Ỡ"; break;
    case 'O' | TONE_UNDERDOT   | MOD_HORN:       unicode = "Ợ"; break;
    case 'U' | TONE_GRAVE      | MOD_NONE:       unicode = "Ù"; break;
    case 'U' | TONE_ACUTE      | MOD_NONE:       unicode = "Ú"; break;
    case 'U' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "Ủ"; break;
    case 'U' | TONE_TILDE      | MOD_NONE:       unicode = "Ũ"; break;
    case 'U' | TONE_UNDERDOT   | MOD_NONE:       unicode = "Ụ"; break;
    case 'U' | TONE_UNMARKED   | MOD_HORN:       unicode = "Ư"; break;
    case 'U' | TONE_GRAVE      | MOD_HORN:       unicode = "Ừ"; break;
    case 'U' | TONE_ACUTE      | MOD_HORN:       unicode = "Ứ"; break;
    case 'U' | TONE_HOOK_ABOVE | MOD_HORN:       unicode = "Ử"; break;
    case 'U' | TONE_TILDE      | MOD_HORN:       unicode = "Ữ"; break;
    case 'U' | TONE_UNDERDOT   | MOD_HORN:       unicode = "Ự"; break;
    case 'Y' | TONE_GRAVE      | MOD_NONE:       unicode = "Ỳ"; break;
    case 'Y' | TONE_ACUTE      | MOD_NONE:       unicode = "Ý"; break;
    case 'Y' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "Ỷ"; break;
    case 'Y' | TONE_TILDE      | MOD_NONE:       unicode = "Ỹ"; break;
    case 'Y' | TONE_UNDERDOT   | MOD_NONE:       unicode = "Ỵ"; break;
    case 'a' | TONE_GRAVE      | MOD_NONE:       unicode = "à"; break;
    case 'a' | TONE_ACUTE      | MOD_NONE:       unicode = "á"; break;
    case 'a' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "ả"; break;
    case 'a' | TONE_TILDE      | MOD_NONE:       unicode = "ã"; break;
    case 'a' | TONE_UNDERDOT   | MOD_NONE:       unicode = "ạ"; break;
    case 'a' | TONE_UNMARKED   | MOD_BREVE:      unicode = "ă"; break;
    case 'a' | TONE_GRAVE      | MOD_BREVE:      unicode = "ằ"; break;
    case 'a' | TONE_ACUTE      | MOD_BREVE:      unicode = "ắ"; break;
    case 'a' | TONE_HOOK_ABOVE | MOD_BREVE:      unicode = "ẳ"; break;
    case 'a' | TONE_TILDE      | MOD_BREVE:      unicode = "ẵ"; break;
    case 'a' | TONE_UNDERDOT   | MOD_BREVE:      unicode = "ặ"; break;
    case 'a' | TONE_UNMARKED   | MOD_CIRCUMFLEX: unicode = "â"; break;
    case 'a' | TONE_GRAVE      | MOD_CIRCUMFLEX: unicode = "ầ"; break;
    case 'a' | TONE_ACUTE      | MOD_CIRCUMFLEX: unicode = "ấ"; break;
    case 'a' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: unicode = "ẩ"; break;
    case 'a' | TONE_TILDE      | MOD_CIRCUMFLEX: unicode = "ẫ"; break;
    case 'a' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: unicode = "ậ"; break;
    case 'd' | TONE_UNMARKED   | MOD_STROKE:     unicode = "đ"; break;
    case 'e' | TONE_UNMARKED   | MOD_NONE:       unicode = "e"; break;
    case 'e' | TONE_GRAVE      | MOD_NONE:       unicode = "è"; break;
    case 'e' | TONE_ACUTE      | MOD_NONE:       unicode = "é"; break;
    case 'e' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "ẻ"; break;
    case 'e' | TONE_TILDE      | MOD_NONE:       unicode = "ẽ"; break;
    case 'e' | TONE_UNDERDOT   | MOD_NONE:       unicode = "ẹ"; break;
    case 'e' | TONE_UNMARKED   | MOD_CIRCUMFLEX: unicode = "ê"; break;
    case 'e' | TONE_GRAVE      | MOD_CIRCUMFLEX: unicode = "ề"; break;
    case 'e' | TONE_ACUTE      | MOD_CIRCUMFLEX: unicode = "ế"; break;
    case 'e' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: unicode = "ể"; break;
    case 'e' | TONE_TILDE      | MOD_CIRCUMFLEX: unicode = "ễ"; break;
    case 'e' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: unicode = "ệ"; break;
    case 'i' | TONE_GRAVE      | MOD_NONE:       unicode = "ì"; break;
    case 'i' | TONE_ACUTE      | MOD_NONE:       unicode = "í"; break;
    case 'i' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "ỉ"; break;
    case 'i' | TONE_TILDE      | MOD_NONE:       unicode = "ĩ"; break;
    case 'i' | TONE_UNDERDOT   | MOD_NONE:       unicode = "ị"; break;
    case 'o' | TONE_GRAVE      | MOD_NONE:       unicode = "ò"; break;
    case 'o' | TONE_ACUTE      | MOD_NONE:       unicode = "ó"; break;
    case 'o' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "ỏ"; break;
    case 'o' | TONE_TILDE      | MOD_NONE:       unicode = "õ"; break;
    case 'o' | TONE_UNDERDOT   | MOD_NONE:       unicode = "ọ"; break;
    case 'o' | TONE_UNMARKED   | MOD_CIRCUMFLEX: unicode = "ô"; break;
    case 'o' | TONE_GRAVE      | MOD_CIRCUMFLEX: unicode = "ồ"; break;
    case 'o' | TONE_ACUTE      | MOD_CIRCUMFLEX: unicode = "ố"; break;
    case 'o' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: unicode = "ổ"; break;
    case 'o' | TONE_TILDE      | MOD_CIRCUMFLEX: unicode = "ỗ"; break;
    case 'o' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: unicode = "ộ"; break;
    case 'o' | TONE_UNMARKED   | MOD_HORN:       unicode = "ơ"; break;
    case 'o' | TONE_GRAVE      | MOD_HORN:       unicode = "ờ"; break;
    case 'o' | TONE_ACUTE      | MOD_HORN:       unicode = "ớ"; break;
    case 'o' | TONE_HOOK_ABOVE | MOD_HORN:       unicode = "ở"; break;
    case 'o' | TONE_TILDE      | MOD_HORN:       unicode = "ỡ"; break;
    case 'o' | TONE_UNDERDOT   | MOD_HORN:       unicode = "ợ"; break;
    case 'u' | TONE_GRAVE      | MOD_NONE:       unicode = "ù"; break;
    case 'u' | TONE_ACUTE      | MOD_NONE:       unicode = "ú"; break;
    case 'u' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "ủ"; break;
    case 'u' | TONE_TILDE      | MOD_NONE:       unicode = "ũ"; break;
    case 'u' | TONE_UNDERDOT   | MOD_NONE:       unicode = "ụ"; break;
    case 'u' | TONE_UNMARKED   | MOD_HORN:       unicode = "ư"; break;
    case 'u' | TONE_GRAVE      | MOD_HORN:       unicode = "ừ"; break;
    case 'u' | TONE_ACUTE      | MOD_HORN:       unicode = "ứ"; break;
    case 'u' | TONE_HOOK_ABOVE | MOD_HORN:       unicode = "ử"; break;
    case 'u' | TONE_TILDE      | MOD_HORN:       unicode = "ữ"; break;
    case 'u' | TONE_UNDERDOT   | MOD_HORN:       unicode = "ự"; break;
    case 'y' | TONE_GRAVE      | MOD_NONE:       unicode = "ỳ"; break;
    case 'y' | TONE_ACUTE      | MOD_NONE:       unicode = "ý"; break;
    case 'y' | TONE_HOOK_ABOVE | MOD_NONE:       unicode = "ỷ"; break;
    case 'y' | TONE_TILDE      | MOD_NONE:       unicode = "ỹ"; break;
    case 'y' | TONE_UNDERDOT   | MOD_NONE:       unicode = "ỵ"; break;
    default:                                     return -1;
    }

    while (*unicode)
        *dest++ = *unicode++;

    return 0;
}

#define NO_CONV 0x0000

struct Keystroke {
    char     trigger;
    pchar_t *conversions;
};

#define KEYSTROKE_DEFINE(_t, ...)                           \
    (struct Keystroke){                                     \
        .trigger = _t,                                      \
        .conversions = (pchar_t []){ __VA_ARGS__, NO_CONV } \
    }

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
    KEYSTROKE_DEFINE('z', TONE_RESET),
};

static struct Keystroke VNI[] = {
    /* generated with mapping.py */
    KEYSTROKE_DEFINE('1', TONE_ACUTE),
    KEYSTROKE_DEFINE('2', TONE_GRAVE),
    KEYSTROKE_DEFINE('3', TONE_HOOK_ABOVE),
    KEYSTROKE_DEFINE('4', TONE_TILDE),
    KEYSTROKE_DEFINE('5', TONE_UNDERDOT),
    KEYSTROKE_DEFINE('6', MOD_CIRCUMFLEX),
    KEYSTROKE_DEFINE('7', MOD_HORN),
    KEYSTROKE_DEFINE('8', MOD_BREVE),
    KEYSTROKE_DEFINE('9', MOD_STROKE),
    KEYSTROKE_DEFINE('0', TONE_RESET),
};

struct Method {
    int               keystroke_num;
    struct Keystroke *keystrokes;
};

enum ApplyResult {
    APPLY_OK = 0,
    APPLY_REVERTED,
    APPLY_UNCHANGED,
};

enum ApplyResult minigox_apply_method(
    const struct Method *method,
    struct CharInfo *info,
    char ch
) {
    for (int i = 0; i < method->keystroke_num; ++i) {
        struct Keystroke *keystroke = &method->keystrokes[i];

        if (keystroke->trigger == tolower(ch)) {
            pchar_t *conv = keystroke->conversions;

            while (*conv != NO_CONV) {
                struct CharInfo conv_info = minigox_unpack_char(*conv);

                if (conv_info.base && conv_info.base != tolower(info->base)) {
                    ++conv;
                    continue;
                }

                if (conv_info.tone != TONE_UNMARKED) {
                    if (
                        (conv_info.tone == TONE_RESET
                        && info->tone != TONE_UNMARKED)
                        || conv_info.tone == info->tone
                    ) {
                        info->tone = TONE_UNMARKED;
                        return APPLY_REVERTED;
                    }

                    info->tone = conv_info.tone;
                } else if (conv_info.mod != MOD_NONE) {
                    if (
                        (conv_info.mod == MOD_RESET && info->mod != MOD_NONE)
                        || conv_info.mod == info->mod
                    ) {
                        info->mod = MOD_NONE;
                        return APPLY_REVERTED;
                    }

                    info->mod = conv_info.mod;
                }

                return APPLY_OK;
            }

            break;
        }
    }

    return APPLY_UNCHANGED;
}

#endif // MINIGOX_H
