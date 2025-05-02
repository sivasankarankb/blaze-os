//--- Inspiration Kernel Port Handling Module ---//
# include <ports.h>
  
  // in-port-byte
  u8int   inb ( u16int  port) 
  { 
      u8int  ret; 
      asm  volatile ( "inb %1, %0"  :  "=a"  (ret) :  "dN"  (port)); 
      return  ret; 
  } 

  // in-port-word
  u16int   inw ( u16int  port) 
  { 
      u16int  ret; 
      asm volatile ( "inw %1, %0"  :  "=a"  (ret) :  "dN"  (port)); 
      return  ret; 
  }
  
  // Wait for an I/O operation to complete 
  void io_wait( void )
  {
    asm volatile("jmp 1f;1:jmp 2f;2:");
  }