//---- Inspiration  C Kernel ----//
# include <common.h>
# include <screen.h>
# include <ports.h>
# include <ps2.h>
# include <interrupts.h>

// Kernel Main
 void kmain()
 {
   u32int *bsect=(u32int *) 0x07DFC;
   
   asm("cli");
   
   ps2_wait_w();
   outb(PS2_COMMAND,KYB_SCAN_NO);
   
   // Write some stuff on the screen
   textcolor(0x0F);
   
   clrscr();
   
   set_put_delay(0);
   
   textcolor(0x0A);
   puts("\n\t\t\t\b\b");
   
   set_put_delay(500000);
   
   textcolor(0x0B);
   puts("Inspiration");
   
   textcolor(0x0A);
   puts(" v0.21 Alpha 'Twin-Leaf'");
   set_put_delay(0);
   
   textcolor(0x0F);  
   
   // Start initial services
   
   enable_a20();                    // Enable the A20 line if not enabled yet
   //init_keyboard();                 // Initialize the keyboard
   setup_ints();                    // Set Up Interrupts and IRQs
   
   textcolor(0x0F);
   
   puts("\n\n A:\\>");
   
   for(;;);                         // Put the CPU in a loop so that it doesn't
                                    // do anything stupid or execute any junk.
 }