//-- Inspiration Memory Module Header --//
#ifndef MEMORY_H
#define MEMORY_H

# include <common.h>

  // Prototypes for memory.c
  
  void memcpy(u8int *source,u8int *dest,u32int count);
  void memset(u8int *dest,u8int val,u32int count);

#endif