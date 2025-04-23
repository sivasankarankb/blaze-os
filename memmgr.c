#include "proto.h"
// Inspiration Memory functions Library  

  // Enables the A20 line
  
  void enablea20()
  {
    unsigned char a,b,c;
   
    io_wait_ps2_w();
    out(0x64,0xAD);         // disable keyboard
   
    io_wait_ps2_w();
    out(0x64,0xA7);         // disable ps2 mouse
  
    io_wait_ps2_w();
    out(0x64,0xD0);         // Read from input command
 
    io_wait_ps2_r();
    a=in(0x60);             // Read byte from kbc
  
    io_wait_ps2_w();
    out(0x64,0xD1);         // Write to output command
    
    b=a<<6;
    c=b>>7;
  
    if(c!=1)
    {
      io_wait_ps2_w();
      out(0x60,a|2);          // Write byte to kbc
    }
    
    else
    {
      unsigned char *mx=(unsigned char *)0x501;
      *mx='Y';
    }
  
    io_wait_ps2_w();
    out(0x64,0xAE);         // Enable Keyboard
  }
  
  // Checks if the A20 line was enabled

  void checka20()
  {
    io_wait_ps2_w();
    out(0x64,0xD0);         // Read from input command
    
    io_wait_ps2_r();
    
    unsigned char enchk;
    enchk = in(0x60);       // Read byte from kbc
    
    unsigned short enable_chk = enchk<<6;
    enable_chk=enable_chk>>7;
    
    if(enable_chk==1)
    {
      unsigned char *mx=(unsigned char *) 0x501;
      
      if(*mx=='Y')
      {
        kputs("Already Enabled by BIOS");
      }
      
      else
        kputs("Enabled By Inspiration");
    }
    
    else
    {
      kputs("Disabled");
    }
    
    kputf('\n');
  }
  
  // Set a particulat rage in memory to a specific value at the byte level

  void memset(unsigned char *dest, unsigned char what, int count)
  {
    int i;
    
    for(i=0; i<count; i++)
    {
      *dest=what;
      dest++;
    }
  }
  
  void memsetskp(unsigned char *dest, unsigned char what, int count, int skpb)
  {
    int i;
    
    for(i=0; i<(count*(skpb+1));i+=(skpb+1))
    {
      *dest=what;
      dest+=(skpb+1);
    }
  }
  
  // Copies a particular no. of bytes from one meory location to another

  void memcopy(unsigned char *loc, unsigned char *dest, int count)
  {
    int i;
    for(i=0; i<count; i++)
    {
      *dest=*loc;
      dest++;
      loc++;
    }
  }