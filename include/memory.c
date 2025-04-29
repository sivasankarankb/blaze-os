//-- Inspiration Memory Module --//
# include <common.h>
# include <memory.h>
  
  // Copy from one memory location to another, 1 byte at a time
  void memcpy(u8int *source,u8int *dest,u32int count)
  {
    int i;
    for(i=0;i<count;i++)
    {
      dest[i]=source[i];      
    }
  }
  
  // Set a no. of continous bytes in memory to a specific value
  void memset(u8int *dest,u8int val,u32int count)
  {
    int i;
    for(i=0;i<count;i++)
    {
      dest[i]=val;      
    }
  } 
