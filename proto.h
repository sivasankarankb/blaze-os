// Inspiration function prototypes
  void memsetskp(unsigned char *dest, unsigned char what, int count, int skpb);
  void int46();
  void videomodetst();
  void irq1();
  void irq0();
  void isr17_31();
  void isr_16();
  void isr_15();
  void isr_14();
  void isr_13();
  void isr_12();
  void isr_11();
  void isr_10();
  void isr_9();
  void isr_8();
  void isr_7();
  void isr_6();
  void isr_5();
  void isr_4();
  void isr_3();
  void isr_2();
  void isr_1();
  void isr_0();
  void clrscr();
  void disable_ints();
  void enable_ints();
  void io_wait_ps2_r();  
  void io_wait_ps2_w();
  void setLEDs(int scrolllock,int numlock,int capslock);
  void set_scancode_1();
  void IRQ_clear_mask(unsigned char IRQline);
  void remap_pics(int pic1, int pic2);
  void prASM();
  void checka20();
  void scroll();
  void ani4ever();
  
  static inline void io_wait( void );
  
  static inline
  void io_wait( void )
  {
    __asm__ __volatile__( "jmp 1f\n\t"
                    "1:jmp 2f\n\t"
                    "2:" );
  }

  void enablea20();
  void memsetani(unsigned char *dest, unsigned char what, int count);
  void memset(unsigned char *dest, unsigned char what, int count);
  void memcopy(unsigned char *loc, unsigned char *dest, int count);
  int obit(unsigned char ibyte, int bitnum);
  void setccol(unsigned char col);
  void kputs(unsigned char *cha);
  void settptr(int tptr);
  void setbgfg(unsigned char col);
  void kput(unsigned char ch);
  void kputf(unsigned char ch);
  unsigned char in(unsigned short _port);
  void out(unsigned short _port, unsigned char _data);
  void enablemouse();