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
 * Compose a Vietnamese character from CharInfo.
 *
 * Returns a pointer to a UTF-8 encoded string representing the
 * fully composed character (with tone and modifier applied).
 * Returns NULL if no valid composition exists.
 */
const char *minigox_compose_char(struct CharInfo info) {
    pchar_t ch = info.base | info.tone | info.mod;

    if (ch == info.base) {
        static char buf[2];
        buf[0] = info.base;
        return buf;
    }

    switch (ch) {
    /* generated with mapping.py */
    case 'A' | TONE_GRAVE      | MOD_NONE:       return "À";
    case 'A' | TONE_ACUTE      | MOD_NONE:       return "Á";
    case 'A' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ả";
    case 'A' | TONE_TILDE      | MOD_NONE:       return "Ã";
    case 'A' | TONE_UNDERDOT   | MOD_NONE:       return "Ạ";
    case 'A' | TONE_UNMARKED   | MOD_BREVE:      return "Ă";
    case 'A' | TONE_GRAVE      | MOD_BREVE:      return "Ằ";
    case 'A' | TONE_ACUTE      | MOD_BREVE:      return "Ắ";
    case 'A' | TONE_HOOK_ABOVE | MOD_BREVE:      return "Ẳ";
    case 'A' | TONE_TILDE      | MOD_BREVE:      return "Ẵ";
    case 'A' | TONE_UNDERDOT   | MOD_BREVE:      return "Ặ";
    case 'A' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "Â";
    case 'A' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "Ầ";
    case 'A' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "Ấ";
    case 'A' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "Ẩ";
    case 'A' | TONE_TILDE      | MOD_CIRCUMFLEX: return "Ẫ";
    case 'A' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "Ậ";
    case 'D' | TONE_UNMARKED   | MOD_STROKE:     return "Đ";
    case 'E' | TONE_GRAVE      | MOD_NONE:       return "È";
    case 'E' | TONE_ACUTE      | MOD_NONE:       return "É";
    case 'E' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ẻ";
    case 'E' | TONE_TILDE      | MOD_NONE:       return "Ẽ";
    case 'E' | TONE_UNDERDOT   | MOD_NONE:       return "Ẹ";
    case 'E' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "Ê";
    case 'E' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "Ề";
    case 'E' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "Ế";
    case 'E' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "Ể";
    case 'E' | TONE_TILDE      | MOD_CIRCUMFLEX: return "Ễ";
    case 'E' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "Ệ";
    case 'I' | TONE_GRAVE      | MOD_NONE:       return "Ì";
    case 'I' | TONE_ACUTE      | MOD_NONE:       return "Í";
    case 'I' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ỉ";
    case 'I' | TONE_TILDE      | MOD_NONE:       return "Ĩ";
    case 'I' | TONE_UNDERDOT   | MOD_NONE:       return "Ị";
    case 'O' | TONE_GRAVE      | MOD_NONE:       return "Ò";
    case 'O' | TONE_ACUTE      | MOD_NONE:       return "Ó";
    case 'O' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ỏ";
    case 'O' | TONE_TILDE      | MOD_NONE:       return "Õ";
    case 'O' | TONE_UNDERDOT   | MOD_NONE:       return "Ọ";
    case 'O' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "Ô";
    case 'O' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "Ồ";
    case 'O' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "Ố";
    case 'O' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "Ổ";
    case 'O' | TONE_TILDE      | MOD_CIRCUMFLEX: return "Ỗ";
    case 'O' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "Ộ";
    case 'O' | TONE_UNMARKED   | MOD_HORN:       return "Ơ";
    case 'O' | TONE_GRAVE      | MOD_HORN:       return "Ờ";
    case 'O' | TONE_ACUTE      | MOD_HORN:       return "Ớ";
    case 'O' | TONE_HOOK_ABOVE | MOD_HORN:       return "Ở";
    case 'O' | TONE_TILDE      | MOD_HORN:       return "Ỡ";
    case 'O' | TONE_UNDERDOT   | MOD_HORN:       return "Ợ";
    case 'U' | TONE_GRAVE      | MOD_NONE:       return "Ù";
    case 'U' | TONE_ACUTE      | MOD_NONE:       return "Ú";
    case 'U' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ủ";
    case 'U' | TONE_TILDE      | MOD_NONE:       return "Ũ";
    case 'U' | TONE_UNDERDOT   | MOD_NONE:       return "Ụ";
    case 'U' | TONE_UNMARKED   | MOD_HORN:       return "Ư";
    case 'U' | TONE_GRAVE      | MOD_HORN:       return "Ừ";
    case 'U' | TONE_ACUTE      | MOD_HORN:       return "Ứ";
    case 'U' | TONE_HOOK_ABOVE | MOD_HORN:       return "Ử";
    case 'U' | TONE_TILDE      | MOD_HORN:       return "Ữ";
    case 'U' | TONE_UNDERDOT   | MOD_HORN:       return "Ự";
    case 'Y' | TONE_GRAVE      | MOD_NONE:       return "Ỳ";
    case 'Y' | TONE_ACUTE      | MOD_NONE:       return "Ý";
    case 'Y' | TONE_HOOK_ABOVE | MOD_NONE:       return "Ỷ";
    case 'Y' | TONE_TILDE      | MOD_NONE:       return "Ỹ";
    case 'Y' | TONE_UNDERDOT   | MOD_NONE:       return "Ỵ";
    case 'a' | TONE_GRAVE      | MOD_NONE:       return "à";
    case 'a' | TONE_ACUTE      | MOD_NONE:       return "á";
    case 'a' | TONE_HOOK_ABOVE | MOD_NONE:       return "ả";
    case 'a' | TONE_TILDE      | MOD_NONE:       return "ã";
    case 'a' | TONE_UNDERDOT   | MOD_NONE:       return "ạ";
    case 'a' | TONE_UNMARKED   | MOD_BREVE:      return "ă";
    case 'a' | TONE_GRAVE      | MOD_BREVE:      return "ằ";
    case 'a' | TONE_ACUTE      | MOD_BREVE:      return "ắ";
    case 'a' | TONE_HOOK_ABOVE | MOD_BREVE:      return "ẳ";
    case 'a' | TONE_TILDE      | MOD_BREVE:      return "ẵ";
    case 'a' | TONE_UNDERDOT   | MOD_BREVE:      return "ặ";
    case 'a' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "â";
    case 'a' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "ầ";
    case 'a' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "ấ";
    case 'a' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "ẩ";
    case 'a' | TONE_TILDE      | MOD_CIRCUMFLEX: return "ẫ";
    case 'a' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "ậ";
    case 'd' | TONE_UNMARKED   | MOD_STROKE:     return "đ";
    case 'e' | TONE_UNMARKED   | MOD_NONE:       return "e";
    case 'e' | TONE_GRAVE      | MOD_NONE:       return "è";
    case 'e' | TONE_ACUTE      | MOD_NONE:       return "é";
    case 'e' | TONE_HOOK_ABOVE | MOD_NONE:       return "ẻ";
    case 'e' | TONE_TILDE      | MOD_NONE:       return "ẽ";
    case 'e' | TONE_UNDERDOT   | MOD_NONE:       return "ẹ";
    case 'e' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "ê";
    case 'e' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "ề";
    case 'e' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "ế";
    case 'e' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "ể";
    case 'e' | TONE_TILDE      | MOD_CIRCUMFLEX: return "ễ";
    case 'e' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "ệ";
    case 'i' | TONE_GRAVE      | MOD_NONE:       return "ì";
    case 'i' | TONE_ACUTE      | MOD_NONE:       return "í";
    case 'i' | TONE_HOOK_ABOVE | MOD_NONE:       return "ỉ";
    case 'i' | TONE_TILDE      | MOD_NONE:       return "ĩ";
    case 'i' | TONE_UNDERDOT   | MOD_NONE:       return "ị";
    case 'o' | TONE_GRAVE      | MOD_NONE:       return "ò";
    case 'o' | TONE_ACUTE      | MOD_NONE:       return "ó";
    case 'o' | TONE_HOOK_ABOVE | MOD_NONE:       return "ỏ";
    case 'o' | TONE_TILDE      | MOD_NONE:       return "õ";
    case 'o' | TONE_UNDERDOT   | MOD_NONE:       return "ọ";
    case 'o' | TONE_UNMARKED   | MOD_CIRCUMFLEX: return "ô";
    case 'o' | TONE_GRAVE      | MOD_CIRCUMFLEX: return "ồ";
    case 'o' | TONE_ACUTE      | MOD_CIRCUMFLEX: return "ố";
    case 'o' | TONE_HOOK_ABOVE | MOD_CIRCUMFLEX: return "ổ";
    case 'o' | TONE_TILDE      | MOD_CIRCUMFLEX: return "ỗ";
    case 'o' | TONE_UNDERDOT   | MOD_CIRCUMFLEX: return "ộ";
    case 'o' | TONE_UNMARKED   | MOD_HORN:       return "ơ";
    case 'o' | TONE_GRAVE      | MOD_HORN:       return "ờ";
    case 'o' | TONE_ACUTE      | MOD_HORN:       return "ớ";
    case 'o' | TONE_HOOK_ABOVE | MOD_HORN:       return "ở";
    case 'o' | TONE_TILDE      | MOD_HORN:       return "ỡ";
    case 'o' | TONE_UNDERDOT   | MOD_HORN:       return "ợ";
    case 'u' | TONE_GRAVE      | MOD_NONE:       return "ù";
    case 'u' | TONE_ACUTE      | MOD_NONE:       return "ú";
    case 'u' | TONE_HOOK_ABOVE | MOD_NONE:       return "ủ";
    case 'u' | TONE_TILDE      | MOD_NONE:       return "ũ";
    case 'u' | TONE_UNDERDOT   | MOD_NONE:       return "ụ";
    case 'u' | TONE_UNMARKED   | MOD_HORN:       return "ư";
    case 'u' | TONE_GRAVE      | MOD_HORN:       return "ừ";
    case 'u' | TONE_ACUTE      | MOD_HORN:       return "ứ";
    case 'u' | TONE_HOOK_ABOVE | MOD_HORN:       return "ử";
    case 'u' | TONE_TILDE      | MOD_HORN:       return "ữ";
    case 'u' | TONE_UNDERDOT   | MOD_HORN:       return "ự";
    case 'y' | TONE_GRAVE      | MOD_NONE:       return "ỳ";
    case 'y' | TONE_ACUTE      | MOD_NONE:       return "ý";
    case 'y' | TONE_HOOK_ABOVE | MOD_NONE:       return "ỷ";
    case 'y' | TONE_TILDE      | MOD_NONE:       return "ỹ";
    case 'y' | TONE_UNDERDOT   | MOD_NONE:       return "ỵ";
    default:                                     return 0;
    }
}

/*
 * Write a composed Vietnamese character into a buffer
 *
 * Returns 0 on success, -1 if composition failed.
 * If `dest` is NULL, returns the number of bytes required
 * (not including null terminator).
 */
int minigox_write_char(struct CharInfo info, char *dest) {
    int len = (info.tone != TONE_UNMARKED) + (info.mod != MOD_NONE) + 1;

    if (!dest)
        return len;
    if (len == 1) {
        *dest++ = info.base;
        *dest++ = '\0';
        return 0;
    }

    const char *unicode = minigox_compose_char(info);
    if (!unicode)
        return -1;

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

/*
 * Note: this function does not check whether the resulting
 * combination is a valid Vietnamese character.
 * Better use `minigox_compose_char` after applying.
 */
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
                        conv_info.tone == TONE_RESET
                        && info->tone != TONE_UNMARKED
                    ) {
                        info->tone = TONE_UNMARKED;
                        return APPLY_OK;
                    }

                    if (conv_info.tone == info->tone) {
                        info->tone = TONE_UNMARKED;
                        return APPLY_REVERTED;
                    }

                    info->tone = conv_info.tone;
                    return APPLY_OK;
                }
                if (conv_info.mod != MOD_NONE) {
                    if (conv_info.mod == MOD_RESET && info->mod != MOD_NONE) {
                        info->mod = MOD_NONE;
                        return APPLY_OK;
                    }

                    if (conv_info.mod == info->mod) {
                        info->mod = MOD_NONE;
                        return APPLY_REVERTED;
                    }

                    info->mod = conv_info.mod;
                    return APPLY_OK;
                }
            }

            break;
        }
    }

    return APPLY_UNCHANGED;
}

#endif // MINIGOX_H
