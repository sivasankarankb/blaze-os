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
  
  // Copies a particular no. of bytes from one memory location to another

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
  
  // void setup_paging()
  // {
  //   int end=0x100000;
  //   unsigned int page_aligned_end = (((unsigned int)end) & 0xFFFFF000) + 0x1000;
  //   unsigned int *page_directory = (unsigned int*)page_aligned_end;
  //   //set each entry to not present
  //   unsigned int i = 0;
  //   for(i = 0; i < 1024; i++)
  //   {
  //      //attribute: supervisor level, read/write, not present.
  //      page_directory[i] = 0 | 2; 
  //   }
  //   //our first page table comes right after the page directory
  //   unsigned int *first_page_table = page_directory + 0x1000;
    
  //   // holds the physical address where we want to start mapping these pages to.
  //   // in this case, we want to map these pages to the very beginning of memory.
  //   unsigned int address = 0; 
 
  //   //we will fill all 1024 entries, mapping 4 megabytes
  //   for(i = 0; i < 1024; i++)
  //   {
  //     first_page_table[i] = address | 3; // attributes: supervisor level, read/write, present.
  //     address = address + 4096; //advance the address to the next page boundary
  //   }
    
  //   //put the newly created page table into our blank page directory
  //   page_directory[0] = first_page_table; 
  //   page_directory[0] |= 3;// attributes: supervisor level, read/write, present
    
  //   //moves page_directory (which is a pointer) into the cr3 register.
  //   __asm__ __volatile__("mov %0, %%cr3":: "b"(page_directory));
    
  //   //Finally we switch the paging bit on the cr0 register. This operation also requires inline assembly code.
  //   //reads cr0, switches the "paging enable" bit, and writes it back.
  //   unsigned int cr0;
  //   __asm__ __volatile__("mov %%cr0, %0": "=b"(cr0));
  //   cr0 |= 0x80000000;
  //   __asm__ __volatile__("mov %0, %%cr0":: "b"(cr0));
  // }