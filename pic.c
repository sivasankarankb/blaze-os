#include "proto.h"
// Inspiration PIC functions Library

  /* remap the PIC controller interrupts to our vectors
   rather than the 8 + 70 as mapped by default */

  #define	PIC1		        0x20
  #define	PIC2		        0xA0
  #define	PIC1_COMMAND	  PIC1
  #define	PIC1_DATA	     (PIC1+1)
  #define	PIC2_COMMAND  	PIC2
  #define	PIC2_DATA	     (PIC2+1)
  #define	PIC_EOI		      0x20

  #define	ICW1_ICW4	      0x01		/* ICW4 (not) needed */
  #define	ICW1_SINGLE	    0x02		/* Single (cascade) mode */
  #define	ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
  #define	ICW1_LEVEL	    0x08		/* Level triggered (edge) mode */
  #define	ICW1_INIT	      0x10		/* Initialization - required! */
 
  #define	ICW4_8086	      0x01		/* 8086/88 (MCS-80/85) mode */
  #define	ICW4_AUTO	      0x02		/* Auto (normal) EOI */
  #define	ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
  #define	ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
  #define	ICW4_SFNM	      0x10		/* Special fully nested (not) */

  void remap_pics(int pic1, int pic2)
  {
	  unsigned char	a1, a2;

	  a1=in(PIC1_DATA);
  	a2=in(PIC2_DATA);

  	out(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);
  	io_wait();
  	out(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
  	io_wait();
  	out(PIC1_DATA, pic1);
  	io_wait();
  	out(PIC2_DATA, pic2);
  	io_wait();
  	out(PIC1_DATA, 4);
  	io_wait();
  	out(PIC2_DATA, 2);
  	io_wait();

  	out(PIC1_DATA, ICW4_8086);
  	io_wait();
  	out(PIC2_DATA, ICW4_8086);
  	io_wait();

  	out(PIC1_DATA, a1);
  	out(PIC2_DATA, a2);
  }

  void IRQ_clear_mask(unsigned char IRQline)
  {
    unsigned short port;
    unsigned char value;
 
    if(IRQline < 8)
    {
      port = PIC1_DATA;
    }
    
    else
    {
      port = PIC2_DATA;
      IRQline -= 8;
    }
    
    value = in(port) & ~(1 << IRQline);
    out(port, value);        
 }