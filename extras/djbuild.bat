@echo off

rem DJGPP Build Script for Blaze OS v0.2.1
set CFILECOUNT=7
set CFLAGS=-c -I include/ -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore

echo 1 of 6 Build bootloader

mkdir bin
nasm -f bin -o bin\boot.bin boot.asm

echo 2 of 6 Build kernel sources

mkdir obj
mkdir obj\include
echo   1 of %CFILECOUNT% kern32.asm
nasm -f aout -o obj\kern32.o kern32.asm

echo   2 of %CFILECOUNT% kernel.c
gcc %CFLAGS% -o obj\kernel.o kernel.c
echo   3 of %CFILECOUNT% include\interrupts.c
gcc %CFLAGS% -o obj\include\interrupts.o include\interrupts.c
echo   4 of %CFILECOUNT% include\screen.c
gcc %CFLAGS% -o obj\include\screen.o include\screen.c
echo   5 of %CFILECOUNT% include\memory.c
gcc %CFLAGS% -o obj\include\memory.o include\memory.c
echo   6 of %CFILECOUNT% include\ports.c
gcc %CFLAGS% -o obj\include\ports.o include\ports.c
echo   7 of %CFILECOUNT% include\ps2.c
gcc %CFLAGS% -o obj\include\ps2.o include\ps2.c

echo 3 of 6 Create library file

ar rcs obj\libk.a obj\kernel.o
ar rs obj\libk.a obj\include\interrupts.o
ar rs obj\libk.a obj\include\screen.o
ar rs obj\libk.a obj\include\memory.o
ar rs obj\libk.a obj\include\ports.o
ar rs obj\libk.a obj\include\ps2.o

echo 4 of 6 Create kernel binary

ld obj\kern32.o obj\libk.a -T linker.ld -o obj\ldkern.o
objcopy -R .note -R .comment -S -g -O binary obj\ldkern.o bin\kernel.bin

echo 5 of 6 Create boot disk image

copy /B bin\boot.bin+bin\kernel.bin boot.img > nul

echo 6 of 6 Clean up

echo Y | del obj\include > nul
rmdir obj\include

echo Y | del obj > nul
rmdir obj

echo Y | del bin > nul
rmdir bin
