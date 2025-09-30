# minigox

A tiny Vietnamese input method editor written in C

Currently only Windows is supported, but plans for Linux (and possibly MacOS)
are in the works

## Usage

Compile `minigox.c` using MSVC or MinGW.

`minigox` supports Telex and VNI typing. The only difference from other IMEs is
that `minigox` only processes one character at a time.
