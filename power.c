  #include "proto.h"
  void reboot()
  {
    __asm__ __volatile__(" .code16gcc\n\
                           mov $0xFE,%al;\
                           out %al,$0x64; ");    
  }