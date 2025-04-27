#!/bin/bash
clear

# GNU/Linux GCC Build Script for Blaze OS v0.1.1

CFLAGS="-c -nostdinc -nostdlib -ffreestanding -march=i386 -fleading-underscore \
-fno-pie -fno-stack-protector -m32"
CFILES="kernel irq isr itext memmgr pic ports ps2 power"
CFILECOUNT=$(echo "$CFILES" | wc -w)
SRCCOUNT=$(($CFILECOUNT + 1))

echo "1 of 6 Build bootloader"

mkdir bin
nasm -f bin -o bin/boot.bin boot.asm

echo "2 of 6 Build kernel sources"
SRCNUM=1

mkdir obj
echo "  $SRCNUM of $SRCCOUNT idt.asm"
nasm -f elf -o obj/idt.o idt.asm

for CSOURCE in ${CFILES}; do
  SRCNUM=$(($SRCNUM + 1))
  echo "  $SRCNUM of $SRCCOUNT ${CSOURCE}.c"
  gcc $CFLAGS -o obj/${CSOURCE}.o ${CSOURCE}.c; done

echo "3 of 6 Create library file"

for CSOURCE in ${CFILES}; do
  ar rcs obj/libk.a obj/${CSOURCE}.o; done

echo "4 of 6 Create kernel binary"

ld -melf_i386 obj/idt.o obj/libk.a -T linker.ld -o obj/ldkern.o
objcopy -R .note -R .comment -S -g -O binary obj/ldkern.o bin/kernel.bin

echo "5 of 6 Create boot disk image"

cat bin/boot.bin bin/kernel.bin > boot.img

echo "6 of 6 Clean up"

rm -rf obj
rm -rf bin
