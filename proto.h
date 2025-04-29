// Inspiration function prototypes

// IRQ.H
  void irq0();
  void irq1();

// ISR.H
  void disable_ints();
  void enable_ints();
  void int46();
  void isr0();
  void isr1();
  void isr2();
  void isr3();
  void isr4();
  void isr5();
  void isr6();
  void isr7();
  void isr8();
  void isr9();
  void isr10();
  void isr11();
  void isr12();
  void isr13();
  void isr14();
  void isr15();
  void isr16();
  void isr17_31();

// ITEXT.H
  void clrscr();
  void kput(unsigned char ch);
  void kputf(unsigned char ch);
  void kputs(unsigned char *cha);
  void prASM();
  void putnum(int num);
  void scroll();
  void setbgfg(unsigned char col);
  void setccol(unsigned char col);
  void settptr(int tptr);
  void videomodetst();

// MEMMGR.H
  void checka20();
  void enablea20();
  void memcopy(unsigned char *loc, unsigned char *dest, int count);
  void memset(unsigned char *dest, unsigned char what, int count);
  void setup_paging();

// PIC.H  
  void IRQ_clear_mask(unsigned char IRQline);
  void remap_pics(int pic1, int pic2);

// PORTS.H
  unsigned char in(unsigned short _port);
  static inline void io_wait( void );
  void out(unsigned short _port, unsigned char _data);

  static inline
  void io_wait( void )
  {
    __asm__ __volatile__( "jmp 1f\n\t"
                    "1:jmp 2f\n\t"
                    "2:" );
  }

// POWER.H  
  void reboot();

// PS2.H
  void enablemouse();
  void io_wait_ps2_r();  
  void io_wait_ps2_w();
  void setLEDs(int scrolllock,int numlock,int capslock);
  void set_scancode_1();