echo off
cls

rem DJGPP Build Script for Blaze OS v0.1.1
set CFILECOUNT=10

echo 1 of 6 Build bootloader

mkdir bin
nasm -f bin -o bin\boot.bin boot.asm

echo 2 of 6 Build kernel sources

mkdir obj
echo   1 of %CFILECOUNT% idt.asm
nasm -f aout -o obj\idt.o idt.asm

echo   2 of %CFILECOUNT% kernel.c
gcc -c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore -o obj\kernel.o kernel.c
echo   3 of %CFILECOUNT% irq.c
gcc -c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore -o obj\irq.o irq.c
echo   4 of %CFILECOUNT% isr.c
gcc -c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore -o obj\isr.o isr.c
echo   5 of %CFILECOUNT% itext.c
gcc -c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore -o obj\itext.o itext.c
echo   6 of %CFILECOUNT% memmgr.c
gcc -c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore -o obj\memmgr.o memmgr.c
echo   7 of %CFILECOUNT% pic.c
gcc -c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore -o obj\pic.o pic.c
echo   8 of %CFILECOUNT% ports.c
gcc -c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore -o obj\ports.o ports.c
echo   9 of %CFILECOUNT% ps2.c
gcc -c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore -o obj\ps2.o ps2.c
echo   10 of %CFILECOUNT% power.c
gcc -c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore -o obj\power.o power.c

echo 3 of 6 Create library file

ar rcs obj\libk.a obj\kernel.o
ar rs obj\libk.a obj\irq.o
ar rs obj\libk.a obj\isr.o
ar rs obj\libk.a obj\itext.o
ar rs obj\libk.a obj\memmgr.o
ar rs obj\libk.a obj\pic.o
ar rs obj\libk.a obj\ports.o
ar rs obj\libk.a obj\ps2.o
ar rs obj\libk.a obj\power.o

echo 4 of 6 Create kernel binary

ld obj\idt.o obj\libk.a -T linker.ld -o obj\ldkern.o
objcopy -R .note -R .comment -S -g -O binary obj\ldkern.o bin\kernel.bin

echo 5 of 6 Create boot disk image

copy /B bin\boot.bin+bin\kernel.bin boot.img > nul

echo 6 of 6 Clean up

echo Y | del obj > nul
rmdir obj

echo Y | del bin > nul
rmdir bin