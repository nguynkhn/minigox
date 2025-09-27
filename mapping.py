import unicodedata
from enum import Enum, auto

class LetterModification(Enum):
    MOD_NONE       = 0
    MOD_BREVE      = "\u0306"
    MOD_CIRCUMFLEX = "\u0302"
    MOD_HORN       = "\u031b"
    MOD_STROKE     = "\uffff"

class ToneMark(Enum):
    TONE_UNMARKED   = 0
    TONE_GRAVE      = "\u0300"
    TONE_ACUTE      = "\u0301"
    TONE_HOOK_ABOVE = "\u0309"
    TONE_TILDE      = "\u0303"
    TONE_UNDERDOT   = "\u0323"

MAX_MOD_LEN = max(len(mod.name) for mod in LetterModification)
MAX_TONE_LEN = max(len(tone.name) for tone in ToneMark)

class CharMapping:
    def __init__(self, base, mod, tone):
        self.base = base
        self.mod = mod
        self.tone = tone

def extract_mappings(charsets):
    mappings = {}

    for char in charsets:
        base = char
        mod = LetterModification.MOD_NONE
        tone = ToneMark.TONE_UNMARKED

        if char == "đ":
            base = "d"
            mod = LetterModification.MOD_STROKE
        else:
            decomposed = unicodedata.normalize("NFD", char)
            base = decomposed[0]

            for mark in decomposed[1:]:
                if mark in LetterModification:
                    mod = LetterModification(mark)
                elif mark in ToneMark:
                    tone = ToneMark(mark)

        mappings[char] = CharMapping(base, mod, tone)

    return mappings

def generate_switch_cases(mappings, indent=""):
    for letter, mapping in mappings.items():
        print(
            f"{indent}case '{mapping.base}' | "
            f"{mapping.mod.name.ljust(MAX_MOD_LEN)} | "
            f"{(mapping.tone.name + ":").ljust(MAX_TONE_LEN + 1)} "
            f"return \"{letter}\";"
        )

def generate_keystroke_defines(method, define_func="", indent=""):
    for trigger, conversion in method.items():
        if not isinstance(conversion, dict):
            conversion = { "": conversion }

        conversion_str = [
            (f"'{base}' | " if base else "") + mark.name
            for base, mark in conversion.items()
        ]

        define_str = f"{indent}{define_func}('{trigger}', "
        joined_str = f",\n{' ' * len(define_str)}".join(conversion_str)
        print(f"{define_str}{joined_str}),")

CHARSETS = "àáảãạăằắẳẵặâầấẩẫậđèéẻẽẹêềếểễệìíỉĩịòóỏõọôồốổỗộơờớởỡợùúủũụưừứửữựỳýỷỹỵ"

TELEX = {
    "f": ToneMark.TONE_GRAVE,
    "s": ToneMark.TONE_ACUTE,
    "r": ToneMark.TONE_HOOK_ABOVE,
    "x": ToneMark.TONE_TILDE,
    "j": ToneMark.TONE_UNDERDOT,
    "a": { "a": LetterModification.MOD_CIRCUMFLEX },
    "d": { "d": LetterModification.MOD_STROKE },
    "e": { "e": LetterModification.MOD_CIRCUMFLEX },
    "o": { "o": LetterModification.MOD_CIRCUMFLEX },
    "w": {
        "a": LetterModification.MOD_BREVE,
        "o": LetterModification.MOD_HORN,
        "u": LetterModification.MOD_HORN,
    },
}

if __name__ == "__main__":
    from sys import argv, exit

    if len(argv) < 2:
        print("Usage: python mapping.py <compose|method>")
        exit(1)

    indent = " " * 4

    match argv[1]:
        case "compose":
            mappings = extract_mappings(CHARSETS)
            generate_switch_cases(mappings, indent)
        case "method":
            if len(argv) < 3:
                print("Please enter method name")
                exit(1)

            match argv[2]:
                case "telex": method = TELEX
                case _:
                    print("Unknown method")
                    exit(1)

            define_func = argv[3] if len(argv) > 3 else "KEYSTROKE_DEFINE"
            generate_keystroke_defines(method, define_func, indent)
        case _:
            print("Unknown command")
            exit(1)
