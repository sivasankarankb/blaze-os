//--- Inspiration Kernel Screen Handling Header ---//
# include <common.h>

# ifndef SCREEN_H
# define SCREEN_H
  
  void putch(u8int ch);
  void puts(u8int *ch);
  void putint(u32int number);
  void puthexb(u8int byte);
  void puthexw(u16int word);
  void puthexdw(u32int dword);
  
  void clrscr();
  void scroll();
  void update_cursor();
  void reset_cursor();
  void dec_cur_x();
  void inc_cur_x();
  
  void textcolor(u8int attrib);
  void set_put_delay(u32int delay_num);

# endif