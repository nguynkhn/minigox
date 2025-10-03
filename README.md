# minigox

***A tiny Vietnamese input method editor written in C***

Currently only Windows is supported, but plans for Linux (and possibly MacOS)
are in the works.

## Usage

```console
make PLATFORM=<win32>
```

`minigox` supports Telex and VNI typing. The only difference from other IMEs is
that `minigox` only processes one character at a time.
