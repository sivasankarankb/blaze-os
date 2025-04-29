[BITS 32]             ; 32-bit instructions since we are in protected mode

 ;---- Code Section ----;

 [GLOBAL asm_main]    ; The main function of this file
 [GLOBAL _c_idt_start]; Start of IDT pool
 [GLOBAL _install_idt]; Install IDT function
  
 [extern _kmain]      ; The kernel Main of the c kernel
 
 [extern _isr_handler]; The C Interrupt handler
 [extern _int_14]     ; The C int 14 handler
 [extern _kyb_handler]; The C keyboard Handler
 [extern _pit_handler]; The C PIT handler
 
; Prototype for the ISRs
 [GLOBAL _isr0]
 [GLOBAL _isr1]
 [GLOBAL _isr2]
 [GLOBAL _isr3]
 [GLOBAL _isr4]
 [GLOBAL _isr5]
 [GLOBAL _isr6]
 [GLOBAL _isr7]
 [GLOBAL _isr8]
 [GLOBAL _isr9]
 [GLOBAL _isr10]
 [GLOBAL _isr11]
 [GLOBAL _isr12]
 [GLOBAL _isr13]
 [GLOBAL _isr14]
 [GLOBAL _isr15]
 [GLOBAL _isr16]
 [GLOBAL _isr17]
 [GLOBAL _isr18]
 [GLOBAL _isr19]
 [GLOBAL _isr20]
 [GLOBAL _isr21]
 [GLOBAL _isr22]
 [GLOBAL _isr23]
 [GLOBAL _isr24]
 [GLOBAL _isr25]
 [GLOBAL _isr26]
 [GLOBAL _isr27]
 [GLOBAL _isr28]
 [GLOBAL _isr29]
 [GLOBAL _isr30]
 [GLOBAL _isr31]
 
; IRQ prototypes
 [GLOBAL _isr32]      ; IRQ 0 
 [GLOBAL _isr33]      ; IRQ 2

 asm_main:            ; main() or entry point of this file

 jmp 08h:_kmain       ; Far jump to C Kernel main()
 
 jmp $                ; A loop just to be safe
 
;---------- Data Section + functions ------------;

 db 'INSIDT'          ; Just an ID

 _c_idt_start:        ; Start of IDT
 times 256 dq 0x00    ; Buffer for IDT to be setup by the C kernel
 _c_idt_end:          ; End of IDT
 
 idt_ptr:             ; IDT descriptor to be used by lidt[idt_ptr]
 idt_limit dw _c_idt_end-_c_idt_start-1
 idt_base  dd _c_idt_start 
 
 _install_idt:        ; install_idt() called by C kernel
   cli                ; Clear IF
   lidt[idt_ptr]      ; Load IDTR with idt_ptr
   sti                ; Set IF
   ret                ; Return to the executing code
   
 _isr_common:         ; A common stub called by some ISRs
   pusha              ; Push general purpose regs
   push gs            ; Push segment regs
   push fs
   push ds
   push es

   mov eax,[ds:intno] ; Get the interrupt no.
   
   push eax           ; Pass it as a parameter to isr_handler(u32int intno);
   call _isr_handler  ; Call isr_handler();
   pop  eax           ; Balance the stack

   pop es             ; Pop the segment regs
   pop ds
   pop fs
   pop gs
   popa               ; Pop general purpose regs
   
; The actual ISRs
; Exception handlers (ints 0 to 31)
 _isr0:
   mov byte [ds:intno],0   ; Save the int no. so that _isr_common can get it
   call _isr_common        ; Call _isr_common
   iret                    ; Do an IRET
   
 _isr1:                    ; Same here as above
   mov byte [ds:intno],1
   call _isr_common
   iret
   
 _isr2:
   mov byte [ds:intno],2
   call _isr_common
   iret

 _isr3:
   mov byte [ds:intno],3
   call _isr_common
   iret
   
 _isr4:
   mov byte [ds:intno],4
   call _isr_common
   iret
   
 _isr5:
   mov byte [ds:intno],5
   call _isr_common
   iret

 _isr6:
   mov byte [ds:intno],6
   call _isr_common
   iret
   
 _isr7:
   mov byte [ds:intno],7
   call _isr_common
   iret
   
 _isr8:
   mov byte [ds:intno],8
   call _isr_common
   iret
   
 _isr9:
   mov byte [ds:intno],9
   call _isr_common
   iret
   
 _isr10:
   mov byte [ds:intno],10
   call _isr_common
   iret
   
 _isr11:
   mov byte [ds:intno],11
   call _isr_common
   iret
   
 _isr12:
   mov byte [ds:intno],12
   call _isr_common
   iret
   
 _isr13:
   mov byte [ds:intno],13
   call _isr_common
   iret
   
; This one's special because a page fault gives more info
 _isr14:
   pusha                    ; Same as the common stub
   push gs
   push fs
   push ds
   push es

   mov eax, cr2             ; Save cr2 as it contains the faulty address
   push eax                 ; Pass it onto int_14(u32int cr2);
   
   call _int_14             ; Call int_14();

   pop eax                  ; Even out the stack

   pop es                   ; Same as in the stub
   pop ds
   pop fs
   pop gs
   popa
   iret
   
; More exception handlers
 _isr15:
   mov byte [ds:intno],15
   call _isr_common
   iret
   
 _isr16:
   mov byte [ds:intno],16
   call _isr_common
   iret
   
 _isr17:
   mov byte [ds:intno],17
   call _isr_common
   iret
   
 _isr18:
   mov byte [ds:intno],18
   call _isr_common
   iret
   
 _isr19:
   mov byte [ds:intno],19
   call _isr_common
   iret
   
 _isr20:
   mov byte [ds:intno],20
   call _isr_common
   iret
   
 _isr21:
   mov byte [ds:intno],21
   call _isr_common
   iret
   
 _isr22:
   mov byte [ds:intno],22
   call _isr_common
   iret
   
 _isr23:
   mov byte [ds:intno],23
   call _isr_common
   iret
   
 _isr24:
   mov byte [ds:intno],24
   call _isr_common
   iret
   
 _isr25:
   mov byte [ds:intno],25
   call _isr_common
   iret
   
 _isr26:
   mov byte [ds:intno],26
   call _isr_common
   iret
   
 _isr27:
   mov byte [ds:intno],27
   call _isr_common
   iret
   
 _isr28:
   mov byte [ds:intno],28
   call _isr_common
   iret
   
 _isr29:
   mov byte [ds:intno],29
   call _isr_common
   iret
   
 _isr30:
   mov byte [ds:intno],30
   call _isr_common
   iret
   
 _isr31:
   mov byte [ds:intno],31
   call _isr_common
   iret
   
; IRQs
; IRQ 0 : Programmable Interval Timer (PIT)
   
 _isr32:
   pusha                ; Just like the stub
   push gs
   push fs
   push ds
   push es
   
   call _pit_handler    ; Call the C handler for IRQ0

   pop es               ; Even out the stack
   pop ds
   pop fs
   pop gs
   popa
   
   mov al,0x20          ; Send an EOI to the master PIC
   out 0x20,al
   
   iret                 ; Do an IRET
   
; IRQ 1 : PS2 Keyboard

 _isr33:                ; Same as above
   pusha
   push gs
   push fs
   push ds
   push es
      
   call _kyb_handler    ; Call the keyboard int handler

   pop es
   pop ds
   pop fs
   pop gs
   popa
   
   mov al,0x20          ; Send an EOI
   out 0x20,al
   
   iret                 ; Do an IRET
    
 intno db 0             ; Buffer to store the int no.

times 3072-($-$$) db 0  ; Pad the file with zeroes