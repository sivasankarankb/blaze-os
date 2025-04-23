[BITS 32]
jmp 08h:start

; Kernel Main
extern _main

; ISRs code in C
extern _isr0
extern _isr1
extern _isr2
extern _isr3
extern _isr4
extern _isr5
extern _isr6
extern _isr7
extern _isr8
extern _isr9
extern _isr10
extern _isr11
extern _isr12
extern _isr13
extern _isr14
extern _isr15
extern _isr16
extern _isr17_31

; IRQ Handlers Coded in C 
extern _irq0
extern _irq1
extern _irq2
extern _irq3
extern _irq4
extern _irq5
extern _irq6
extern _irq7
extern _irq8
extern _irq9
extern _irq10
extern _irq11
extern _irq12
extern _irq13
extern _irq14
extern _irq15
extern _int46
extern _int47
 
start:
mov byte [ds:0x0b8002],'L'
mov byte [ds:0x0b8003],0x0F
mov byte [ds:0x0b8004],'o'
mov byte [ds:0x0b8005],0x0F
mov byte [ds:0x0b8006],'a'
mov byte [ds:0x0b8007],0x0F
mov byte [ds:0x0b8008],'d'
mov byte [ds:0x0b8009],0x0F
mov byte [ds:0x0b800a],'i'
mov byte [ds:0x0b800b],0x0F
mov byte [ds:0x0b800c],'n'
mov byte [ds:0x0b800d],0x0F
mov byte [ds:0x0b800e],'g'
mov byte [ds:0x0b800f],0x0F
mov byte [ds:0x0b8012],'I'
mov byte [ds:0x0b8013],0x0F
mov byte [ds:0x0b8014],'D'
mov byte [ds:0x0b8015],0x0F
mov byte [ds:0x0b8016],'T'
mov byte [ds:0x0b8017],0x0F

cli
lidt [idt_pointer]

mov byte [ds:0x0b801A],':'
mov byte [ds:0x0b801B],0x0F
mov byte [ds:0x0b801E],'1'
mov byte [ds:0x0b801F],0x0A

jmp 08h : _main
jmp $ 

start_of_idt:
;interrupt 0
dw isr_0 ; Offset LO
dw 0x08  ; GDT code Segment
dw 0x8E00; Flags
dw 0x00  ; Offset HI

;interrupt 1
dw isr_1
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 2, intel reserved, we set the 'present' bit to 0 on this one
dw isr_2
dw 0x08
dw 0x0E00
dw 0x00
;interrupt 3
dw isr_3
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 4
dw isr_4
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 5
dw isr_5
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 6
dw isr_6
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 7
dw isr_7
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 8
dw isr_8
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 9
dw isr_9
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 10
dw isr_10
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 11
dw isr_11
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 12
dw isr_12
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 13
dw isr_13
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 14
dw isr_14
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 15, intel reserved, we set the 'present' bit to 0 on this one
dw isr_15
dw 0x08
dw 0x0E00
dw 0x00

;interrupt 16
dw isr_16
dw 0x08
dw 0x8E00
dw 0x00

;interrupts 17-31
%rep 0x0E
  dw isr_17_31
  dw 0x08
  dw 0x0E00
  dw 0x00
%endrep


;interrupt 32 - PIT int
dw irq_0
dw 0x08
dw 0x8E00
dw 0x00

;interrupt 33 - Keyboard int
dw irq_1
dw 0x08
dw 0x8E00
dw 0x00
;interrput 34 onwards : just a stub
  dw irq_2
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_3
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_4
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_5
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_6
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_7
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_8
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_9
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_10
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_11
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_12
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_13
  dw 0x08
  dw 0x8E00
  dw 0x00
  
  dw irq_15
  dw 0x08
  dw 0x8E00
  dw 0x00
  
; 46th interrupt - Displays Inspiration Version
  dw int_46
  dw 0x08
  dw 0xEE00
  dw 0x00

; 47th interrupt - Memory Access  
  dw int_47
  dw 0x08
  dw 0xEE00
  dw 0x00
  
; 48th interrupt - Video Int  
  dw 0x40
  dw 0x08
  dw 0xEE00
  dw 0x42
    
end_of_idt:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; now for the IDT pointer
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
idt_pointer:
  dw (end_of_idt - start_of_idt) - 1
  dd start_of_idt
  
isr_0:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr0

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
isr_1:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr1

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_2:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr2

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_3:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr3

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_4:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr4

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_5:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr5

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_6:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr6

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_7:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr7

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_8:
 pop eax
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr8

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_9:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr9

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_10:
 pop eax
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr10

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_11:
 pop eax
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr11

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_12:
 pop eax
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr12

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_13:
 pop eax
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr13

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_14:
 pop eax
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr14

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_15:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr15

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_16:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr16

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
 isr_17_31:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _isr17_31

 pop ds
 pop es
 pop fs
 pop gs
 popa

 iret
 
  irq_0:
 pusha
 push gs
 push fs
 push es
 push ds
 
 call _irq0

 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_1:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq1
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_2:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq2
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_3:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq3
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_4:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq4
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_5:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq5
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_6:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq6
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_7:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq7
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_8:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq8
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_9:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq9
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_10:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq10
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_11:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq11
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_12:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq12
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_13:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq13
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_14:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq14
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  irq_15:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _irq15
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 mov al,20h
 out 20h,al
 iret
 
  int_46:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _int46
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 iret
 
  int_47:
 pusha
 push gs
 push fs
 push es
 push ds
  
 call _int47
 
 pop ds
 pop es
 pop fs
 pop gs
 popa
 iret
  
 jmp $  
times 1536-($-$$) db 0