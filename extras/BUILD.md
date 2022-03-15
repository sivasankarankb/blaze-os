
Compiling older versions of Blaze O.S.
======================================

Older versions used a build script and a linker script instead of a Makefile.
These were removed from the old sources as they no longer require to be built.
Those sources were kept only for historic reasons.

These files were re-created. There were no build scripts for Linux distros
back then. A simple translation to linux commands has been done.
Copy the scripts to the outermost directory before running.


v0.1.0
------

- \[01\] In `boot.asm` the number of floppy sectors to load is hard-coded
  as 19. The latest DJGPP image (as of 10 March 2022) requires 29 sectors.
  Find the number of sectors by dividing the size of the kernel image by 512
  and rounding up. Edit the number in `boot.asm` and reassemble it.

- \[02\] All C source files excluding `kernel.c` include no header files.
  An 'implicit declaration' warning is thrown for each function external
  to the source file. Just add `#include "proto.h"` to the top of all C source.

- \[03\] (Fix included in build scripts)

  Newer builds of the GNU Linker (ld) for DJGPP sadly no longer support ELF
  format. Both COFF and AOUT formats are supported though. Using COFF produces
  a warning when assembling `idt.asm`. The AOUT format does the trick for now.

  MinGW and Linux GCCs still support ELF. Their build scripts will continue to
  utilise ELF for NASM output.

- \[04\] (Fix included in build scripts)

  The `idt.asm` file contains C symbols with an underscore in front. GCC on
  a linux distro usually produces symbols without a leading underscore.
  The flag `-fleading-underscore` has been added to the build scripts for
  all GCC invocations to add the underscore. It is unlikely that this flag
  will ever be needed by DJGPP. There is no real harm in adding it though.

- \[05\] The symbol `main` has a special meaning in C and it maybe renamed
  by compilers. MinGW was observed doing this. To build on such compilers
  the `main()` function in `kernel.c` should be renamed to something like
  `fakemain` or `mymain` for example. All references to `main` in `idt.asm`
  should also be renamed.

- \[06\] In `ports.c` `io_wait()` is defined `static inline` which does not
  include the function's instructions in the built object file. Move
  the definition from `ports.c` to `proto.h`. Place it below the `io_wait()`
  declaration there.

