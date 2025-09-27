from unicodedata import normalize
from enum import Enum, auto

class LetterModification(Enum):
    MOD_NONE = auto()
    MOD_BREVE = auto()
    MOD_CIRCUMFLEX = auto()
    MOD_HORN = auto()
    MOD_STROKE = auto()

class ToneMark(Enum):
    TONE_UNMARKED = auto()
    TONE_GRAVE = auto()
    TONE_ACUTE = auto()
    TONE_HOOK_ABOVE = auto()
    TONE_TILDE = auto()
    TONE_UNDERDOT = auto()

class CharMapping:
    def __init__(self, unicode, base, tone: ToneMark, mod: LetterModification):
        self.unicode = unicode
        self.base = base
        self.tone = tone
        self.mod = mod

    def pack(self):
        return ord(self.base) | (self.tone.value << 8) | (self.mod.value << 12)

    def __repr__(self):
        return (
            f"CharMapping(unicode='{self.unicode}', base='{self.base}', "
            f"tone={self.tone.name}, mod={self.mod.name})"
        )

LETTER_MODIFICATION_MAP = {
    "\u0306": LetterModification.MOD_BREVE,
    "\u0302": LetterModification.MOD_CIRCUMFLEX,
    "\u031b": LetterModification.MOD_HORN,
}

TONE_MARK_MAP = {
    "\u0300": ToneMark.TONE_GRAVE,
    "\u0301": ToneMark.TONE_ACUTE,
    "\u0309": ToneMark.TONE_HOOK_ABOVE,
    "\u0303": ToneMark.TONE_TILDE,
    "\u0323": ToneMark.TONE_UNDERDOT,
}


VIETNAMESE_CHARS = (
    "ÀÁẢÃĂẰẮẲẴẶÂẦẤẨẪẬĐÈÉẺẼẸÊỀẾỂỄỆÌÍỈĨỊÒÓỎÕỌÔỒỐỔỖỘƠỜỚỞỠỢÙÚỦŨỤƯỪỨỬỮỰỲÝỶỸỴ"
    "àáảãăằắẳẵặâầấẩẫậđèéẻẽẹêềếểễệìíỉĩịòóỏõọôồốổỗộơờớởỡợùúủũụưừứửữựỳýỷỹỵ"
)

def extract_mappings():
    mappings = []

    for char in VIETNAMESE_CHARS:
        base = char
        tone = ToneMark.TONE_UNMARKED
        mod = LetterModification.MOD_NONE

        if char.lower() == 'đ':
            base = 'd' if char.islower() else 'D'
            mod = LetterModification.MOD_STROKE
        else:
            decomposed = normalize("NFD", char)
            base = decomposed[0]

            for mark in decomposed[1:]:
                if mark in TONE_MARK_MAP:
                    tone = TONE_MARK_MAP[mark]
                elif mark in LETTER_MODIFICATION_MAP:
                    mod = LETTER_MODIFICATION_MAP[mark]

        mappings.append(CharMapping(char, base, tone, mod))

    return mappings

def generate_switch_cases(mappings, indent=""):
    max_base_len = max(len(mapping.base) for mapping in mappings)
    max_tone_len = max(len(mapping.tone.name) for mapping in mappings)
    max_mod_len = max(len(mapping.mod.name + ":") for mapping in mappings)

    for mapping in mappings:
        base_padded = mapping.base.ljust(max_base_len)
        tone_padded = mapping.tone.name.ljust(max_tone_len)
        mod_padded = (mapping.mod.name + ":").ljust(max_mod_len)
        print(
            f"{indent}case '{base_padded}' | {tone_padded} | {mod_padded} "
            f"return \"{mapping.unicode}\";"
        )

if __name__ == "__main__":
    all_mappings = extract_mappings()
    all_mappings.sort(key=lambda x: x.pack())

    generate_switch_cases(all_mappings, " " * 4)
