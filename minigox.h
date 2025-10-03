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
const char *minigox_compose_char(struct CharInfo);
#include "minigox_compose.h"

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
#include "minigox_method.h"

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
