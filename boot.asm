;Inspiration Primary Bootloader

[BITS 16]       ; We need 16-bit intructions for Real mode
[ORG 0x7C00]    ; The BIOS loads the boot sector into memory location 0x7C00


jmp short begin
nop
times 0x3B db 0

; DOS Boot Record

;db "MSWIN4.1" ; OEM Identifier
;dw 0x200      ; No. of Bytes Per Sector
;db 0xFF       ; No. of sector per cluster
;dw 0x11       ; No. of Reserved Sectors
;db 0x01       ; No. of FATs on the Disc
;dw 0x02       ; No. of Directory Entries
;dw 0x27BF     ; No. of Logical Sectors on this Disc = 65535
;db 0x00       ; Media Descriptor Byte
;dw 0x00       ; No. of Sectors Per FAT


; Start the bootloader

begin:

;jmp enableA20

;enable a20 line

;enableA20:
;  in al, 0x92
;  test al, 2
;  jnz after
;  or al, 2
;  and al, 0xFE
;  out 0x92, al

after:

; Reads a few sectors from floppy
reset_drive:
        mov ah, 0               ; RESET-command
        int 13h                 ; Call interrupt 13h
        or ah, ah               ; Check for error code
        jnz reset_drive         ; Try again if ah != 0

        mov ax, 0               ; Offset of Destination address = 0000 
        mov es, ax              ; Move offset to es
                                ; The reset command uses es:bx
        mov bx, 01000h          ; Destination address = 0000:1000

        mov ah, 02h             ; READ SECTOR-command
        mov al, 012h            ; Number of sectors to read = 19
        mov ch, 00h             ; Cylinder = 0
        mov cl, 02h             ; Sector = 2 (starts from 1 not 0!)
        mov dh, 00h             ; Head = 0
        int 13h                 ; Call interrupt 13h
        or ah, ah               ; Check for error code
        jnz reset_drive         ; Try again if ah != 0
        
; Print 'Press Enter' onto the screen

; First clear the screen

mov ah,06h ; Scroll Up function
mov al,00h ; Nothing or 0x00 in AL means clear the whole screen
mov bh,0ah ; Character attribute 0x0A is green on black
mov ch,00h ; Top left row
mov cl,00h ; Top left column
mov dh,25  ; Bottom right row 
mov dl,80  ; Bottom right column
int 10h    ; Call video interrupt

; Then set cursor to position '0'

mov ah,02h ; Set hardware cursor function
mov bh,00h ; Page no. = 0
mov dh,00h ; Row or X
mov dl,00h ; Column or Y
int 10h    ; Call video interrupt

; Make the cursor invisible

mov ah,01h   ; Set textmode cursor shape function
mov ch,0010b ; Cursor config. bits 7-5
mov cl,0000b ; Cursor config. bits 0-4
int 10h      ; Call video interrupt
 
mov ah, 0Eh
mov bh, 0Fh
mov bl, 0

mov al,0x0A                     ; New Line Character - 11
int 10h

mov al,0x0D                     ; Carriage Return Character - 13
int 10h

mov al,' '                      ; <space> character
times 34 int 10h

mov al,'P'
int 10h

mov al,'r'
int 10h

mov al,'e'
int 10h

mov al,'s'
int 10h

mov al,'s'
int 10h

mov al,' '
int 10h

mov al,'E'
int 10h

mov al,'n'
int 10h

mov al,'t'
int 10h

mov al,'e'
int 10h

mov al,'r'
int 10h

mov al,' '
int 10h

; wait until enter is pressed

mloop:
   mov ah, 0
   int 0x16   ; wait for keypress
 
   cmp al, 0x08    ; backspace pressed?
   je mloop   ; back to square one
 
   cmp al, 0x0D  ; enter pressed?
   je next      ; yes, we're done
   
   jmp mloop  ; keep looping util Enter is Pressed
   
; Graphics setup 

next:
; Graphics Mode
;mov ah,00h  ; Set Graphics Mode Function
;mov al,13h  ; 256 K color Mode 13h
;int 10h     ; Video interrupt

;mov ax,4F02h
;mov bx,102h ;103h
;int 10h

;text mode
mov ah,00h
mov al,03h
int 10h


; Start the Procedure to go to 32-bit mode - setup GDT and Stack

        cli                     ; Disable interrupts, we want to be alone

        xor ax, ax
        mov ds, ax              ; Set DS-register to 0 - used by lgdt

        lgdt [gdt_desc]         ; Load the GDT descriptor

        mov eax, cr0            ; Copy the contents of CR0 into EAX
        or eax, 1               ; Set bit 0
        mov cr0, eax            ; Copy the contents of EAX into CR0
        jmp 08h:clear_pipe      ; Jump to code segment, offset clear_pipe

[BITS 32]                       ; We now need 32-bit instructions

clear_pipe:
        mov ax, 10h             ; Save data segment identifyer
        mov ds, ax              ; Move a valid data segment into the data segment register
        mov ss, ax              ; Move a valid data segment into the stack segment register
        mov esp, 090000h        ; Move the stack pointer to 090000h

; Let the 32bit kernel code take control of the PC

jmp 08h : 01000h                ; Go to C code
jmp $                           ; A loop for extra safety

; The data for the GDT                                

gdt:                    ; Address for the GDT

gdt_null:               ; Null Segment
        dd 0
        dd 0

gdt_code:               ; Code segment, read/execute, nonconforming
        dw 0FFFFh
        dw 0
        db 0
        db 10011010b    ;10011010b
        db 11001111b
        db 0

gdt_data:               ; Data segment, read/write, expand down
        dw 0FFFFh
        dw 0
        db 0
        db 10010010b
        db 11001111b
        db 0

gdt_end:                ; Used to calculate the size of the GDT



gdt_desc:                       ; The GDT descriptor
        dw gdt_end - gdt - 1    ; Limit (size)
        dd gdt                  ; Address of the GDT


; Make the bootsector perfect

times 510-($-$$) db 0           ; Fill up the file with zeros

        dw 0AA55h               ; Boot sector identifyer                    