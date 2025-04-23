// This file is the Inspiration C kernel

  # include "proto.h"      // Function prototypes libary
                           // Some strings used in the basic kernel :
                           
  char pmode1[]        = "\
Protected mode active" ;
  char welcome[]       = "\
Welcome to Inspiration" ;
  char rep[]           = "\
Reporting:\n\n" ;
  char a201[]          = "\
1. A20 Line : " ;
  char ps2m1[]         = "\
2. PS/2 Mouse Port : Enabled\n\
3. PS/2 Mouse : Enabled\n\
4. Mouse Data Reporting : Enabled\n" ;
  char remap_pic1[]    = "\
5. PICs remapped to interrupts 33 to 47\n" ;
  char kbdsc1_LED_011[]= "\
6. Keyboard Scan Code set to Set 1\n\
7. Capslock and Numlock turned on\n";
  char irqs_1[]="\
8. Enabled IRQs Exceptions and All Interrupts\n";
  char paging_1[]="\
9. Enabled Paging\n";
  
  void kmain();            // Prototype for kmain()
  void enable_hardware();
  
  void enable_hardware()
  {
    IRQ_clear_mask(0);     // Make IRQs available
    IRQ_clear_mask(1);
    IRQ_clear_mask(2);
    IRQ_clear_mask(3);
    IRQ_clear_mask(4);
    IRQ_clear_mask(5);
    IRQ_clear_mask(6);
    IRQ_clear_mask(7);
    IRQ_clear_mask(8);
    IRQ_clear_mask(9);
    IRQ_clear_mask(10);
    IRQ_clear_mask(11);
    IRQ_clear_mask(12);
    IRQ_clear_mask(13);
    IRQ_clear_mask(14);
    IRQ_clear_mask(15);
    enable_ints();         // Enable Interrupts
  }  
  
  void main()              // Kernel entry point
  {             
    clrscr();              // Clear the screen
    disable_ints();        // Disable interrupts    
    kmain();               // Call kmain()
    for(;;);               // Go into an infinite loop                          
  }
  
  void kmain()             // Kernel-main()
  {
                           // Graphics and Text mode memory pointers :

    unsigned char *gvidmem = (unsigned char *)0xA0000;  
    unsigned char *tvidmem = (unsigned char *)0xB8000;

    clrscr();
    setbgfg(0x0E);
    setccol(0x0A);         // Set screen color attribute to Green on Black
    settptr(188);          // Change the text position pointer to position
                           // '188' for better alignment
    kputs(pmode1);         // Print 'Protected mode active'
    setccol(0x0F);         // Set attribute to White on Black
    settptr(27+240+80);    // Change the text pointer
    kputs(welcome);        // Print 'Welcome to Inspiration' 
    setccol(0x0C);         // Set attribute to Red on Black  
    settptr(33+400+80);    // Change the text pointer
    kputs(rep);            // Print 'Reporting :'
    setccol(0x0E);         // Set attribute to Yellow on Black
    enablea20();           // Enable the A20 line
    kputs(a201);           // Print status message
    checka20();            // Check if a20 is enabled or not 
    enablemouse();         // Enable mouse and 2nd PS/2 port
    kputs(ps2m1);          // Print status message
    remap_pics(0x20,0x28); // Remap the PICs
    kputs(remap_pic1);     // Print status message
    set_scancode_1();      // Set the keyboard scancode to set 1
    setLEDs(0,1,0);        // Sets the capslock and numloack LEDs to on position LEDs to on
    kputs(kbdsc1_LED_011); // Print status message
    videomodetst();        // Test if We Are In Mode 0x03 : 80x25 text mode
    enable_hardware();     // Enable Interrupts and IRQs
    kputs(irqs_1);         // Print status message
    //setup_paging();        // Enable Paging
    //kputs(paging_1);       // Print status message
    kputs("9. Testing Number Printer : ");
    putnum(1000);
    kputf('\n');
    
    __asm__("int $46");
    
    __asm__("mov $0,%bh");
    __asm__("mov $'A',%ax");
    __asm__("mov $1,%cx");
    __asm__("mov $0x0510,%edx");
    __asm__("int $47");
    
    __asm__("mov $0,%ah\n\
             mov $0x13,%al\n\
             int $48");
    
    for(;;);               // Another infinite loop for extra safety
  }