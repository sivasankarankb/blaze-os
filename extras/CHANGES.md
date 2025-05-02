**Version 0.2.1**
05/06/2014, 02:46:50 pm

- Bootloader no longer waits for Enter press to boot the O.S.
- O.S. load address changed to 0x7E00 so that a large kernel does not overwrite
  the bootloader while loading from disk.

- Left and right arrow keys on the keyboard move the cursor for basic line
  editing.
- Added hex screen print functions.
- Added a basic command-line interpreter with `help`,`cls`,`dir` and `reboot`
  commands.
- Replaced detailed startup messages with an animated O.S. version display.

- Setup the Programmable Interval Timer (PIT).
- PIT interrupts drive a little rotating animation on top right of console.

- Unused software interrupts (version print, memory access) removed.
- Unused screen printing functions removed.
- Modules cleaned up, documented through comments and merged where sensible.
- Single header file split into many (module-wise).


**Version 0.1.1**
07/12/2013, 08:12:02 am

- Switch characters output on Shift and CapsLock usage on keyboard.
- Toggle CapsLock, NumLock, ScrollLock LEDs on keyboard when these keys are
  pressed.
- Hitting Escape reboots the system.

- Added a number output function in the screen driver.
- Unused and commented out code is present.


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