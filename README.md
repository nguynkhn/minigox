# minigox

***A tiny Vietnamese input method editor written in C***

Currently only Windows is supported, but plans for Linux (and possibly MacOS)
are in the works.

## Usage

```console
make PLATFORM=<win32|x11>
```

`minigox` supports Telex and VNI typing. The only difference from other IMEs is
that `minigox` only processes one character at a time.

## Why?

[UniKey](https://www.unikey.org/), one of the most popular IMEs for Vietnamese
typing, isn't really open-source...\
<small>They claim it is, but the source code
is like... from 20 years ago...</small>

There are, of course, [some](https://github.com/tuyenvm/OpenKey/)
[alternatives](https://github.com/lamquangminh/EVKey/), but most of them are
either closed-source or... their codebases are messy as hell.

Implementing this for Linux window systems like X11 or Wayland is quite
challenging, as their security stuff and numerous standards which will never
converge into a single protocol.\
Currently the best you can do is to rely on an
existing input method framework like
[IBus](https://github.com/BambooEngine/ibus-bamboo) or
[Fcitx](https://github.com/fcitx/fcitx5-unikey).

Why C? Because it's simple. You don't have to worry about borrow checking or the
myriad of rules that give programmers headaches.\
*(Don't worry, once this is finished, I'll port it to a better and safer
language :P)*

Also this is kinda like a keylogger. Use at your own risk
(GitHub please don't ban me T.T.)

Deeply inspired by [goxkey](https://github.com/huytd/goxkey). [See how it works
under the hood](https://github.com/huytd/goxkey/blob/main/DEVELOPMENT.md).

