// Inspiration Port-related functions library

  static inline
  void io_wait( void )
  {
    __asm__ __volatile__( "jmp 1f\n\t"
                    "1:jmp 2f\n\t"
                    "2:" );
  }

  unsigned char in(unsigned short _port)
  {
    // "=a" (result) means: put AL register in variable result when finished
    // "d" (_port) means: load EDX with _port
    unsigned char result;
    __asm__  ("in %%dx, %%al" : "=a" (result) : "d" (_port));
    return result;
  }

  void out(unsigned short _port, unsigned char _data)
  {
    // "a" (_data) means: load EAX with _data
    // "d" (_port) means: load EDX with _port
    __asm__ ("out %%al, %%dx" : :"a" (_data), "d" (_port));
  }