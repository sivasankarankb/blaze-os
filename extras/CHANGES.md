**Version 0.1.0**
13/11/2013, 06:52:16 pm

- It's a 32bit O.S.
- The O.S. binary is a raw floppy image.

- An in-house, 16+32bit bootloader is used.
- Bootloader waits for Enter press to launch O.S.
- GDT is setup by bootloader.
- Stack is setup by bootloader at address 0x90000.
- OS load address is 0x1000.

- Display is in 80x25 color text mode. Many colors used.
- Very basic string printing with hardware cursor update, screen scroll
  on overflow, newline, fake tab, backspace and screen clearing.
- Line, rectangle and circle drawing for 320x200 VGA mode
  were written and tested but never used in the O.S.

- PS/2 Keyboard Numlock LED is turned ON.
- PS/2 Keyboard keypresses are printed out.
- PS/2 Mouse movement data is erroneously printed out as keyboard presses.

- Very basic functions that work with memory.

- CPU Exceptions halt the machine.
- Two software interrupts - O.S. version display and memory
  access (set and copy).

- Unused and commented out code is present.