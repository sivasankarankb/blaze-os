//-- Inspiration Interrupt Module Header --//
#ifndef INTERRUPTS_H
#define INTERRUPTS_H

# include <common.h>

  // Prototypes for interrupt.c
  
  void setup_ints();
  void init_idt();
  void remap_pics();
  void setup_irqs();
  void set_idt_entry(u32int base, u16int selector, u8int flags, u8int entry_no);
  void isr_handler(u32int intno);
  void int_14(u32int cr2);
  void IRQ_set_mask(u8int IRQline);
  void IRQ_clear_mask(u8int IRQline);
  void pit_handler();
  void init_pit(u32int freq);
  void kyb_LED(u8int numl, u8int caps,u8int scrl);
  int strcmp( u8int *cha, u8int *chb, u32int len);
  
//~~~~~~~~~~~~~~~~~~~~~ Some PIC-related '#define's ~~~~~~~~~~~~~~~~~~~~~//
  
# define ICW1_ICW4	       0x01	  /* ICW4 (not) needed */
# define ICW1_SINGLE	     0x02	  /* Single (cascade) mode */
# define ICW1_INTERVAL4	   0x04		/* Call address interval 4 (8) */
# define ICW1_LEVEL	       0x08   /* Level triggered (edge) mode */
# define ICW1_INIT	       0x10  	/* Initialization - required! */
  
# define ICW4_8086	       0x01   /* 8086/88 (MCS-80/85) mode */
# define ICW4_AUTO	       0x02   /* Auto (normal) EOI */
# define ICW4_BUF_SLAVE	   0x08		/* Buffered mode/slave */
# define ICW4_BUF_MASTER	 0x0C		/* Buffered mode/master */
# define ICW4_SFNM	       0x10   /* Special fully nested (not) */

# define PIC1		           0x20   /* IO base address for master PIC */
# define PIC2		           0xA0   /* IO base address for slave PIC */
# define PIC1_COMMAND	     PIC1
# define PIC1_DATA	       (PIC1+1)
# define PIC2_COMMAND	     PIC2
# define PIC2_DATA	       (PIC2+1)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//<--------------------- ISRs, ASM functions etc... -------------------->//

  extern void install_idt();
  extern void c_idt_start();
  
  extern void  isr0();
  extern void  isr1();
  extern void  isr2();
  extern void  isr3();
  extern void  isr4();
  extern void  isr5();
  extern void  isr6();
  extern void  isr7();
  extern void  isr8();
  extern void  isr9();
  extern void isr10();
  extern void isr11();
  extern void isr12();
  extern void isr13();
  extern void isr14();
  extern void isr15();
  extern void isr16();
  extern void isr17();
  extern void isr18();
  extern void isr19();
  extern void isr20();
  extern void isr21();
  extern void isr22();
  extern void isr23();
  extern void isr24();
  extern void isr25();
  extern void isr26();
  extern void isr27();
  extern void isr28();
  extern void isr29();
  extern void isr30();
  extern void isr31();
  extern void isr32();
  extern void isr33();
  
//<--------------------------------------------------------------------->//

#endif