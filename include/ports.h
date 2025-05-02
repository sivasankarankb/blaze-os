//--- Inspiration Kernel Port Handling Header ---//
# include <common.h>

# ifndef PORTS_H
# define PORTS_H

  // Prototypes for ports.c
  
  static inline void outb(u16int port, u8int value);
  u8int inb(u16int port);
  u16int inw(u16int port);
  void io_wait();

  // out-port-byte
  static inline void outb(u16int port, u8int value)
  {
     asm volatile ( "outb %1, %0"  : :  "dN"  (port),  "a"  (value));
  }

# endif