;-Code section-----------------------------------------------------------------;

[BITS 16]    ; 16 bit instructions for real mode
[ORG 0x7C00] ; The origin of this bootloader is 0x0000:0x07C0

; Skip the FAT boot record ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

jmp short start
nop

; A FAT12 BPB
 BS_OEMName      db      'MSWIN4.1'
 BPB_BytesPerSec dw      00200h
 BPB_SecPerClus  db      001h
 BPB_RsvdSecCnt  dw      00001h
 BPB_NumFATs     db      002h
 BPB_RootEntCnt  dw      000E0h
 BPB_TotSec16    dw      00B40h
 BPB_Media       db      0F0h
 BPB_FATSz16     dw      00009h
 BPB_SecPerTrk   dw      00012h
 BPB_NumHeads    dw      00002h
 BPB_HiddSec     dd      000000000h
 BPB_TotSec32    dd      000000000h
 BS_DrvNum       db      000h
 BS_Reserved1    db      000h
 BS_BootSig      db      029h
 BS_VolID        dd      0DEADBABAh
 BS_VolLab       db      'INSPIRATION'
 BS_FilSysType   db      'FAT12   '


;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Boot sector entry point
start:

  mov byte [ds:bootdrive],dl

; Set the correct video mode, Clear the screen and put a string on it ;

    mov ah,0x00                 ; SET VIDEO MODE command
    mov al,0x03                 ; 80x25 16-color TEXT mode
    int 10h                     ; Call video interrupt
  
    mov  dl,0x0F                ; Character attribute of white on black
    call clrscr                 ; Call custom clrscr(); function
    mov si,msg                  ; Move the address of string into si
    call printstring            ; Call custom printstring(); function
    
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Reset the Floppy Disk Drive ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

reset_drive:
        mov ah, 0               ; RESET-command
        int 13h                 ; Call interrupt 13h
        or ah, ah               ; Check for error code
        jnz reset_drive         ; Try again if ah != 0
        
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Set Parameters and call int 13h to read a few sectors ~~~~~~~~~~~~~~; 

        ; Load sectors from booted drive
        mov byte dl,[ds:bootdrive]
        mov ax, 0h              ; Offset of Destination address = 0000 
        mov es, ax              ; Move offset to es
                                ; The reset command uses es:bx
        mov bx, 7E00h           ; Destination address = 0000:7E00

        mov ah, 02h             ; READ SECTOR-command
        mov al, 1h             ; Number of sectors to read = 26
        mov ch, 00h             ; Cylinder = 0
        mov cl, 02h             ; Sector = 2 (starts from 1 not 0!)
        mov dh, 00h             ; Head = 0
        int 13h                 ; Call interrupt 13h
        or ah, ah               ; Check for error code
        jnz reset_drive         ; Try again if ah != 0

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
        
; Put another string on the screen~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

    mov  si,msga                ; Store the address of another string
    call printstring            ; Call printstring(); again

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Switch to protected mode~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

 cli                    ; Disable interrupts
 lgdt[gdt_ptr]          ; Load GDT 
 mov eax,cr0            ; Get the contents of cr0
 or al,1                ; OR the value with 1
 mov cr0,eax            ; Update the value of cr0
 jmp 08h:clear_pipe     ; Do a far jump to set cs

[BITS 32]
 clear_pipe:
   mov ax,010h          ; Move data segment into ax
   mov ds,ax            ; Move it into ds
   mov ss,ax            ; Move it into ss
   mov esp, 07000h      ; Set stack pointer to 0x7000

   jmp 08h:0x7E00       ; Call ASM Kernel Main

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Go into an infinite loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

jmp $                   ; A 'self-jump'

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; <--------------16-bit functions using BIOS interrupts--------------->

; Function PrintString to print a NULL-terminated string ~~~~~~~~~~~~~;
 
printstring:
  mov bh, 1Fh ; Character attribute
  mov bl, 0   ; Page number
  
  chloop:     ; The Character printing loop
  lodsb       ; Get a byte from si
  
  or al,al    ; If the byte is a null or 0 then break the loop
  jz finish   ; and return
  
  mov ah, 0Eh ; Function 14 of int 10h :: Print Character  
  int 10h     ; Call int 10h
  
  jmp chloop
  
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
  
; Function ClrScr to clear the screen ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

clrscr:
  
  mov ah,06h  ; Function 6 of int 10h :: Scroll Up Window 
  mov al,00h  ; No. of lines to Scroll :: Zero means all the lines
  mov bh,dl   ; Character attribute for all characters
  mov ch,00h  ; Top left row
  mov cl,00h  ; Top left column
  mov dh,25   ; Bottom right row 
  mov dl,80   ; Bottom right column
  int 10h     ; Call int 10h
              
  mov ah,02h  ; Funtion 2 of int 10h :: Set cutsor position
  mov bh,00h  ; Page number
  mov dh,00h  ; Row no.
  mov dl,00h  ; Column no.
  int 10h     ; Call int 10h
  
  jmp finish
  
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~; 
  
; Function Return to return to the executing code~~~~~~~~~~~~~~~~~~~~~;

finish:
  ret
  
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; <------------------------------------------------------------------->
  
jmp $

;-Data Section-----------------------------------------------------------------;

; GDT entries - Self explanatory ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; NULL secgment
gdt_start:
 gdt_null         dq 0
 
; Kernel Mode Code Segment 
 code_limit_low   dw 0FFFFh
 code_baselow     dw 0
 code_base_middle db 0
 code_access      db 10011010b
 code_granularity db 11001111b
 code_base_high   db 0
 
; Kernel Mode Data Segment 
 data_limit_low   dw 0FFFFh
 data_baselow     dw 0
 data_base_middle db 0
 data_access      db 10010010b
 data_granularity db 11001111b
 data_base_high   db 0

; User Mode Code Segment 
 u_code_limit_low   dw 0FFFFh
 u_code_baselow     dw 0
 u_code_base_middle db 0
 u_code_access      db 11111010b
 u_code_granularity db 11001111b
 u_code_base_high   db 0
 
; User Mode Data Segment
 u_data_limit_low   dw 0FFFFh
 u_data_baselow     dw 0
 u_data_base_middle db 00000000b
 u_data_access      db 11110010b
 u_data_granularity db 11001111b
 u_data_base_high   db 0 
gdt_end:

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; GDT pointer to load into GDTR - Self Explanatory ~~~~~~~~~~~~~~~~~~~;

gdt_ptr:
 limit dw gdt_end - gdt_start - 1
 base  dd gdt_start
 
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
 
; Strings to print ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

msg db 13, 10, 13, 10, '  [ Reading Kernel File ]', 13, 10, 0
msga db 13, 10, 13, 10, '  [ Booting Kernel ]', 13, 10, 13, 10, 0

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

 bootdrive db 0

; Pad the file with Zeroes
times 510-($-$$) db 0

; 'Bootable' Signature
dw 0xAA55

;times 512*18 db 0

;times 224*32 db 0