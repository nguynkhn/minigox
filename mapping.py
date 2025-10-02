import unicodedata
from enum import Enum, auto

class ToneMark(Enum):
    UNMARKED   = 0
    GRAVE      = "\u0300"
    ACUTE      = "\u0301"
    HOOK_ABOVE = "\u0309"
    TILDE      = "\u0303"
    UNDERDOT   = "\u0323"
    RESET      = -1

    def enum_name(self):
        return f"TONE_{self.name}"

class LetterModification(Enum):
    NONE       = 0
    BREVE      = "\u0306"
    CIRCUMFLEX = "\u0302"
    HORN       = "\u031b"
    STROKE     = "\uffff"
    RESET      = -1

    def enum_name(self):
        return f"MOD_{self.name}"

MAX_TONE_LEN = max(len(tone.enum_name()) for tone in ToneMark)
MAX_MOD_LEN = max(len(mod.enum_name()) for mod in LetterModification)

class CharInfo:
    def __init__(self, base, tone, mod):
        self.base = base
        self.tone = tone
        self.mod = mod

def extract_mappings(charsets):
    mappings = {}

    for char in charsets:
        base = char
        tone = ToneMark.UNMARKED
        mod = LetterModification.NONE

        if char == "đ" or char == "Đ":
            base = "d" if char.islower() else "D"
            mod = LetterModification.STROKE
        else:
            decomposed = unicodedata.normalize("NFD", char)
            base = decomposed[0]

            for mark in decomposed[1:]:
                if mark in ToneMark:
                    tone = ToneMark(mark)
                elif mark in LetterModification:
                    mod = LetterModification(mark)

        mappings[char] = CharInfo(base, tone, mod)

    return mappings

def generate_switch_cases(mappings, var_name="", indent=""):
    for letter, mapping in mappings.items():
        print(
            f"{indent}case '{mapping.base}' | "
            f"{mapping.tone.enum_name().ljust(MAX_TONE_LEN)} | "
            f"{(mapping.mod.enum_name() + ":").ljust(MAX_MOD_LEN + 1)} "
            f"{var_name} = \"{letter}\"; break;"
        )

def generate_keystroke_defines(method, define_func="", indent=""):
    for trigger, conversion in method.items():
        if not isinstance(conversion, dict):
            conversion = { "": conversion }

        conversion_str = [
            (f"'{base}' | " if base else "") + mark.enum_name()
            for base, mark in conversion.items()
        ]

        define_str = f"{indent}{define_func}('{trigger}', "
        joined_str = f",\n{' ' * len(define_str)}".join(conversion_str)
        print(f"{define_str}{joined_str}),")

VAR_NAME = "unicode"
DEFINE_FUNC = "KEYSTROKE_DEFINE"
INDENT = " " * 4

CHARSETS = (
    "ÀÁẢÃẠĂẰẮẲẴẶÂẦẤẨẪẬĐEÈÉẺẼẸÊỀẾỂỄỆÌÍỈĨỊÒÓỎÕỌÔỒỐỔỖỘƠỜỚỞỠỢÙÚỦŨỤƯỪỨỬỮỰỲÝỶỸỴ"
    "àáảãạăằắẳẵặâầấẩẫậđeèéẻẽẹêềếểễệìíỉĩịòóỏõọôồốổỗộơờớởỡợùúủũụưừứửữựỳýỷỹỵ"
)

METHODS = {
    "telex": {
        "f": ToneMark.GRAVE,
        "s": ToneMark.ACUTE,
        "r": ToneMark.HOOK_ABOVE,
        "x": ToneMark.TILDE,
        "j": ToneMark.UNDERDOT,
        "a": { "a": LetterModification.CIRCUMFLEX },
        "d": { "d": LetterModification.STROKE },
        "e": { "e": LetterModification.CIRCUMFLEX },
        "o": { "o": LetterModification.CIRCUMFLEX },
        "w": {
            "a": LetterModification.BREVE,
            "o": LetterModification.HORN,
            "u": LetterModification.HORN,
        },
        "z": ToneMark.RESET,
    },
    "vni": {
        "1": ToneMark.ACUTE,
        "2": ToneMark.GRAVE,
        "3": ToneMark.HOOK_ABOVE,
        "4": ToneMark.TILDE,
        "5": ToneMark.UNDERDOT,
        "6": LetterModification.CIRCUMFLEX,
        "7": LetterModification.HORN,
        "8": LetterModification.BREVE,
        "9": LetterModification.STROKE,
        "0": ToneMark.RESET,
    },
}

if __name__ == "__main__":
    from sys import argv, exit

    if len(argv) < 2:
        print("Usage: python mapping.py <compose|method>")
        exit(1)

    match argv[1]:
        case "compose":
            mappings = extract_mappings(CHARSETS)
            generate_switch_cases(mappings, VAR_NAME, INDENT)
        case "method":
            if len(argv) < 3:
                print(f"Available methods: {", ".join(METHODS.keys())}")
                exit(1)

            name = argv[2]
            if name not in METHODS:
                print("Unknown method")
                exit(1)

            method = METHODS[name]
            define_func = argv[3] if len(argv) > 3 else DEFINE_FUNC
            generate_keystroke_defines(method, define_func, INDENT)
        case _:
            print("Unknown command")
            exit(1)
