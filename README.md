Blaze O.S.
==========

A fast, hobby operating system for x86 PCs.

This `README` file and the `extras` folder are not part of the original source
code. They have been added for the convenience of the reader.

**NOTE**: This version of the O.S. is kept for historical reasons only.

Development began in late September or early October of 2013. Verson 0.1.0
was last modified on 13 November 2013 at 06:52:16 pm. Some edits were made
to `kernel.c`, `idt.asm` and `irq.c` later on, the purpose of which are
unclear now.

For a full list of features see `extras/CHANGES.md`.

Features in v0.1.0
------------------

- Prints out what is typed on PS/2 Keyboard. Handles newline, space, tab
  and backspace. Scrolls the screen when output reaches the last line.

- Prints out PS/2 Mouse movement data (wrongly) as Keyboard presses.

Building
--------

These tools are required for building the O.S.:

- **Compiler**: GCC (`gcc`, `ar`, `ld` and `objcopy`) with i386 binary target.
  - GCC on a GNU/Linux distro.
  - MinGW on Windows.
  - DJGPP on DOS (or 32bit Windows).

- **Assembler**: NASM.

Read `extras/BUILD.md` for more information.
