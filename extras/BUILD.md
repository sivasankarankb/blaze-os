
Compiling older versions of Blaze O.S.
======================================

Older versions used a build script and a linker script instead of a Makefile.
These were removed from the old sources as they no longer require to be built.
Those sources were kept only for historic reasons.

These files were re-created. There were no build scripts for Linux distros
back then. The included Linux script has been tested on very modern build
tools. Copy the scripts to the outermost directory before running.


Fixes required to OS v0.2.1 sources
-----------------------------------

**Note**: The points below are numbered discontinuously to not reuse issue
numbers. The missing numbers pointed to issues in past O.S. versions.

To compile the sources on todays tools, a bunch of changes are required.

- \[01\] In `boot.asm` the number of floppy sectors to load is hard-coded
  as 1. The latest DJGPP image (as of 02 May 2025) requires 36 sectors.
  Find the number of sectors by dividing the size of the kernel image by 512
  and rounding up. Edit the number in `boot.asm` and reassemble it.

- \[03\] (Fix included in build scripts)

  Newer builds of the GNU Linker (ld) for DJGPP sadly no longer support ELF
  format. Both COFF and AOUT formats are supported though. Using COFF produces
  a warning when assembling `kern32.asm`. The AOUT format does the trick for now.

  MinGW and Linux GCCs still support ELF. Their build scripts will continue to
  utilise ELF for NASM output.

- \[04\] (Fix included in build scripts)

  The `kern32.asm` file contains C symbols with an underscore in front. GCC on
  a linux distro usually produces symbols without a leading underscore.
  The flag `-fleading-underscore` has been added to the build scripts for
  all GCC invocations to add the underscore. It is unlikely that this flag
  will ever be needed by DJGPP. There is no real harm in adding it though.

- \[05\] The symbol `main` has a special meaning in C and it maybe renamed
  by compilers. MinGW was observed doing this. To build on such compilers
  the `main()` function in `kernel.c` should be renamed to something like
  `fakemain` or `mymain` for example. All references to `main` in `kern32.asm`
  should also be renamed.

- \[07\] (Fix included in Linux build script)

  Modern x86-64 tools have to be instructed to produce 32bit code explicitly.
  The `-m32` GCC flag and i386 ELF emulation in LD with `-melf_i386` seems
  to do the trick as of now.

- \[08\] (Fix included in Linux build script)

  Modern Linux builds of GCC produce position independent executables (PIEs) by
  default. The kernel is always loaded to a fixed address. PIE generation is
  disabled with the `-fno-pie` switch.

- \[09\] (Fix included in Linux build script)

  A stack smash protector added by GCC requires handling from within the kernel.
  This was never implemented in the original kernel code. This feature is
  disabled with the `-fno-stack-protector` flag.

- \[13\] The bootsector loaded the original kernel binary to hex `7E00`. Since
  our linker script aligns sections to 4K, the address must be changed to hex
  `8000` in `boot.asm` and `linker.ld`.

- \[14\] (Fix included in build scripts)

  There are multiple header files in the `include` dir that are required by
  the source code. The `-I include/` option to `gcc` invocations sets this up.

- \[15\] The function `outb` in `ports.c` is declared `inline`. To make this
  work as required, it must be moved to `ports.h` and both the declaration and
  definition must be marked `static inline`.

- \[16\] Port I/O is used by `ps2.c` and `screen.c` but `ports.h` was not
  included by them. Add the include statement to these.

- \[17\] The `init_keyboard` function leaves the keyboard configured in a buggy
  state. Comment out the call to this function in `kernel.c` to make keyboard
  input work.
