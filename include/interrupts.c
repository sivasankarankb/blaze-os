//-- Inspiration Interrupt Module --//

# include <common.h>
# include <interrupts.h>
# include <screen.h>
# include <ports.h>
# include <ps2.h>

 // Definition for a pointer to text video memory
 u8int *itext_video= (u8int *) 0x0B8000;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Keymaps ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

  // General
  
  char US_QWERTY_1[128]=
  {
  // Key Presses

  0,//Escape
  '1','2','3','4','5','6','7','8','9','0',
  '-','=',
  '\b','\t',//Backspace and Tab
  'q','w','e','r','t','y','u','i','o','p',
  '[',']',
  '\n',//Enter
  0,//Left Control
  'a','s','d','f','g','h','j','k','l',
  ';','\'','`',
  127,//Left Shift
  '\\',
  'z','x','c','v','b','n','m',',','.',
  '/',
  127,//Right Shift
  '*',
  0,//Left Alt
  ' ',//Spacebar
  0,//Capslock
  0,0,0,0,0,0,0,0,0,0,//F1 to F10
  0,//Number Lock
  0,//Scroll Lock
  
  //Number Pad with Number Lock:
  
  '7',//Home
  '8',//Up Arrow
  '9',//Page Up
  '-',//Number Pad Minus
  '4',//Left Arrow
  '5',//Number Pad 5
  '6',//Right Arrow
  '+',//Number Pad Plus
  '1',//End
  '2',//Down Arrow
  '3',//Page Down
  '0',//Insert           
  '.',//Delete
  0,0,0,//Absolutely Nothing
  0,0,// F11 and F12
  
  // Key Presses End
  0     // That's all
  
  };
  
  // With shift pressed
  
  char US_QWERTY_sh[128]=
  {
  
  // Key Presses

  0,//Escape
  '!','@','#','$','%','^','&','*','(',')',
  '_','+',
  '\b','\t',//Backspace and Tab
  'Q','W','E','R','T','Y','U','I','O','P',
  '{','}',
  '\n',//Enter
  0,//Left Control
  'A','S','D','F','G','H','J','K','L',
  ':','\"','~',
  127,//Left Shift
  '|',
  'Z','X','C','V','B','N','M','<','>',
  '?',
  127,//Right Shift
  '*',
  0,//Left Alt
  ' ',//Spacebar
  0,//Capslock
  0,0,0,0,0,0,0,0,0,0,//F1 to F10
  0,//Number Lock
  0,//Scroll Lock
  
  //Number Pad with Number Lock:
  
  '7',//Home
  '8',//Up Arrow
  '9',//Page Up
  '-',//Number Pad Minus
  '4',//Left Arrow
  '5',//Number Pad 5
  '6',//Right Arrow
  '+',//Number Pad Plus
  '1',//End
  '2',//Down Arrow
  '3',//Page Down
  '0',//Insert           
  '.',//Delete
  0,0,0,//Absolutely Nothing
  0,0,// F11 and F12
  
  // Key Presses End
  0     // That's all
  
  };
  
  // Extended Character set
  char US_QWERTY_extended[]=
  {
  '\n',//Keypad Enter
  0,//Right Control
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,//Print Screen 1
  0,0,0,0,0,0,0,0,0,0,
  '/',0,
  0,//Print Screen 2
  0,//Right Alt
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//Home
  0,//Cursor Up
  0,//Page Up  
  0,0,//Left
  0,0,//Right
  0,0,//End
  0,//Down
  0,//Page Down
  0,//Insert
  0,//Delete
  0,0,0,0,0,0,0,
  0,//Left GUI
  0,//Right GUI
  0,//Apps
  
  };
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  
  u8int  shifton=0;            // Shift flag
  u8int  NumOn=0;              // Numberlock flag
  u8int  CapsOn=0;             // Capslock flag
  u8int  ScrlOn=0;             // Scroll lock flag
  u8int  firststroke=1;        // If the keystroke was the 1st since startup
  u8int  pitarray[5]="|/-\\";  // Animated cursor frames
  u8int  pitarrpos=0;          // Current Position in pitarray[];
  u32int pit_ticks=0;          // No. of PIT ticks

  // Stucture of an IDT entry
  typedef struct
  {
    u16int  base_low  __attribute__((packed)); 
    u16int  selector  __attribute__((packed)); 
    u8int   zero; 
    u8int   flags; 
    u16int  base_high __attribute__((packed));
  }idt_struct_t;
  
  // IDT entry that points to the ASM buffer
  idt_struct_t *idt_array=(idt_struct_t *)c_idt_start;
  
  u8int cmd_buff[76];
  
  // Set up interrupts
  void setup_ints()
  {
    init_idt();     // Fill IDT with initial values
    remap_pics();   // Reinitialize and Remap the PICs to IRQ 32 onwards
    setup_irqs();   // Clear required IRQ masks in the PIC's mask register
    install_idt();  // Call install IDT from the assembly module
    //puts("\n\tInterrupts setup successfully");
  }
  
  void init_idt()
  {
    // Fill up the IDT relevantly
    
    // Exeption handling ISRs
    set_idt_entry( (u32int)isr0,0x08,0x8E, 0);
    set_idt_entry( (u32int)isr1,0x08,0x8E, 1);
    set_idt_entry( (u32int)isr2,0x08,0x0E, 2);
    set_idt_entry( (u32int)isr3,0x08,0x8E, 3);
    set_idt_entry( (u32int)isr4,0x08,0x8E, 4);
    set_idt_entry( (u32int)isr5,0x08,0x8E, 5);
    set_idt_entry( (u32int)isr6,0x08,0x8E, 6);
    set_idt_entry( (u32int)isr7,0x08,0x8E, 7);
    set_idt_entry( (u32int)isr8,0x08,0x8E, 8);
    set_idt_entry( (u32int)isr9,0x08,0x8E, 9);
    set_idt_entry((u32int)isr10,0x08,0x8E,10);
    set_idt_entry((u32int)isr11,0x08,0x8E,11);
    set_idt_entry((u32int)isr12,0x08,0x8E,12);
    set_idt_entry((u32int)isr13,0x08,0x8E,13);
    set_idt_entry((u32int)isr14,0x08,0x8E,14);
    set_idt_entry((u32int)isr15,0x08,0x8E,15);
    set_idt_entry((u32int)isr16,0x08,0x8E,16);
    set_idt_entry((u32int)isr17,0x08,0x8E,17);
    set_idt_entry((u32int)isr18,0x08,0x8E,18);
    set_idt_entry((u32int)isr19,0x08,0x8E,19);
    set_idt_entry((u32int)isr20,0x08,0x8E,20);
    set_idt_entry((u32int)isr21,0x08,0x8E,21);
    set_idt_entry((u32int)isr22,0x08,0x8E,22);
    set_idt_entry((u32int)isr23,0x08,0x8E,23);
    set_idt_entry((u32int)isr24,0x08,0x8E,24);
    set_idt_entry((u32int)isr25,0x08,0x8E,25);
    set_idt_entry((u32int)isr26,0x08,0x8E,26);
    set_idt_entry((u32int)isr27,0x08,0x8E,27);
    set_idt_entry((u32int)isr28,0x08,0x8E,28);
    set_idt_entry((u32int)isr29,0x08,0x8E,29);
    set_idt_entry((u32int)isr30,0x08,0x8E,30);
    set_idt_entry((u32int)isr31,0x08,0x8E,31);
    
    // IRQs
    set_idt_entry((u32int)isr32,0x08,0x8E,32);
    set_idt_entry((u32int)isr33,0x08,0x8E,33);
  }
  
  // Reinitialise and Remap the PICs
  void remap_pics()
  {
    u8int a1, a2;                             // IRQ masks
    u32int offset1=32, offset2=40;            // Offset to IDT entries
 
	  a1 = inb(PIC1_DATA);                      // save masks
	  a2 = inb(PIC2_DATA);
 
	  outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization
	  io_wait();                                // sequence (in cascade mode)
    
	  outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	  io_wait();
    
	  outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	  io_wait();
    
	  outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	  io_wait();
    
	  outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that 
	  io_wait();                                // there is a slave PIC at
                                              // IRQ2 (0000 0100)
                                              
	  outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its
	  io_wait();                                // cascade identity (0000 0010)
 
	  outb(PIC1_DATA, ICW4_8086);
	  io_wait();
    
	  outb(PIC2_DATA, ICW4_8086);
	  io_wait();
 
	  outb(PIC1_DATA, a1);                      // restore saved masks.
	  outb(PIC2_DATA, a2);
  }
  
  // Cleara few IRQ masks
  void setup_irqs()
  {
    IRQ_clear_mask(0);  //IRQ 0
    IRQ_clear_mask(1);  //IRQ 1
  }
  
  // Set an IDT entry (very useful)
  void set_idt_entry(u32int base, u16int selector, u8int flags, u8int entry_no)
  {
    idt_array[entry_no].base_low=base;
    idt_array[entry_no].base_high=(base>>16)&0xFFFF;
    idt_array[entry_no].selector=selector;
    idt_array[entry_no].zero=0x00;
    idt_array[entry_no].flags=flags;                
  }
  
  // Exception Handler
  void isr_handler(u32int intno)
  {
    puts("\n\tException no.");
    putint(intno);
    asm("cli;hlt;");
  }
  
  // Handler for int 14
  void int_14(u32int cr2)
  {
    puts("Page fault at ");
    putint(cr2);
    asm("cli;hlt;");    // Clear IF and halt the CPU
  }
  
  // Handler for IRQ 1
  void kyb_handler()
  {
    u8int ch;           // Scancode for Keyboard buffer
    //ps2_wait_r();
    ch=inb(PS2_RW);     // Read scancode
    
    if(ch&0x80)         // If bit #7 is set, the key was just released
    {
      if(US_QWERTY_1[(ch^0x80)-1]==127)  // Handle a shift-release
      {
        shifton=0;                       // Clear shift-on flag
      }
      
      else if(ch==0xE0)                  // Handle a keypad key
      {
        ps2_wait_r();
        ch=inb(PS2_RW);
        
        if(!(ch&0x80))
        {
          if(US_QWERTY_1[ch-1]=='4')     // Left Arrow
          {
            dec_cur_x();
          }
        
          else if(US_QWERTY_1[ch-1]=='6')// Right Arrow
          {
            inc_cur_x();
          }
          else if(US_QWERTY_1[ch-1]=='.')// Delete
          {
            puts(" \b");
          }
        }
      }
      
      else if(ch==0xE1)                  // Handle a pause/break keypress
      {
        ps2_wait_r();
        ch=inb(PS2_RW);
        ps2_wait_r();
        ch=inb(PS2_RW);
        ps2_wait_r();
        ch=inb(PS2_RW);
        ps2_wait_r();
        ch=inb(PS2_RW);
        ps2_wait_r();
        ch=inb(PS2_RW);
      }
    }
    
    else if(firststroke)                 // Ignore if the keystroke is the 1st
    {
      firststroke=0;
    }
    
    else if(US_QWERTY_1[ch-1]==127)      // Handle a shift-press
    {
      shifton=1;                         // Set shift-on flag
    }
    
    else if(ch==0x3A)
    {
      if(CapsOn==1)
      {
        kyb_LED(NumOn,0,ScrlOn);
      }
      else
      {
        kyb_LED(NumOn,1,ScrlOn);
      }
    }
    
    else if(ch==0x45)
    {
      if(NumOn==1)
      {
        kyb_LED(0,CapsOn,ScrlOn);
      }
      else
      {
        kyb_LED(1,CapsOn,ScrlOn);
      }
    }
    
    else if(ch==0x46)
    {
      if(ScrlOn==1)
      {
        kyb_LED(NumOn,CapsOn,0);
      }
      else
      {
        kyb_LED(NumOn,CapsOn,1);
      }
    }
    
    else if((!NumOn)&&(ch>=0x47&&ch<=0x53||ch==0x37))
    {
      
    }
    
    else if(shifton&&!CapsOn)            // If shift is pressed and held
    {
      putch(US_QWERTY_sh[ch-1]);
    }
        
    else if(shifton&&CapsOn&&US_QWERTY_sh[ch-1]>='A'&&US_QWERTY_sh[ch-1]<='Z')
    {
      putch(US_QWERTY_1[ch-1]);
    }
    
    else if(shifton&&CapsOn&&(US_QWERTY_sh[ch-1]<'A'||US_QWERTY_sh[ch-1]>'Z'))
    {
      putch(US_QWERTY_1[ch-1]);
    }
    
    else if(US_QWERTY_1[ch-1]=='\n')
    {
      putch('\n');
      if(!strcmp("ver",cmd_buff,3))
      {
        textcolor(0x0E);
        puts("\tInspiration 1.21 alpha build 05-06-14\n");
        textcolor(0x0F);
      }
      else if(!strcmp("help",cmd_buff,4))
      {
        textcolor(0x0B);
        puts("\n Commands :\n\tver\tDisplays version information.\n\t");
        puts("help\tDisplays this help message.");
        puts("\n\tcls\tClears the screen content.");
        puts("\n\tdir\tDisplay the files in the current directory.");
        puts("\n\treboot\tReboots the computer.\n");        
        textcolor(0x0F);
      }
      else if(!strcmp("cls",cmd_buff,3))
      {
        clrscr();
      }
      else if(!strcmp("reboot",cmd_buff,6))
      {
        asm("cli");
        clrscr();
        textcolor(0x0A);
        puts("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t   Rebooting...");
        ps2_wait_w();
        outb(0x64,0xFE);
      }
      else if(!strcmp("dir",cmd_buff,3))
      {
        textcolor(0x0F);
        puts("\n\tFile System in A: is Unknown!\n\tDirectory of Floppy A:\\");
        puts("\n\n\tKERNEL.SYS\n");
        textcolor(0x0F);
      }
      else
      {
        textcolor(0x0C);
        puts("\tUnknown Command!\n\tType help for help\n");
        textcolor(0x0F);
      }
      puts(" A:\\>");
    }
    
    else
    {
      putch(US_QWERTY_1[ch-1]);
    }
  }
  
  // Set the mask bit of an IRQ line
  void IRQ_set_mask(u8int IRQline)
  {
    u16int port;
    u8int value;
 
    if(IRQline < 8)                     // If IRQ no. is less than 8
    {
        port = PIC1_DATA;               // send data to PIC master
    }
    
    else
    {
        port = PIC2_DATA;               // Otherwise to the slave PIC
        IRQline -= 8;
    }
    
    value = inb(port) | (1 << IRQline);
    outb(port, value);                  // Set the required mask
  }
 
  // Clear the mask bit of an IRQ line
  void IRQ_clear_mask(u8int IRQline)
  {
    u16int port;
    u8int value;
 
    if(IRQline < 8)
    {
        port = PIC1_DATA;
    }
    
    else
    {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
  }
  
  // Handler for IRQ 0
  void pit_handler()
  {
    if(pit_ticks%2==0)                // If no. of ticks is even
    {
      if(pitarrpos<4)                 // If position in pitarray[] < 4
      {
        itext_video[160+156]=pitarray[pitarrpos];
        itext_video[160+157]=0x0F;
        pitarrpos++;                  // Increment position
      }
     
      else                            // If position in pitarray[] >= 4
      {
        pitarrpos=0;
        itext_video[160+156]=pitarray[pitarrpos];
        itext_video[160+157]=0x0F;
        pitarrpos++;
      }
    }
    
    pit_ticks++;                      // Increment no. of ticks
  }
  
  // Initialize the PIT to a particular frequency
  void init_pit(u32int freq)
  {
    u32int divisor=freq/1193180L;

    outb(0x43,0x36); 
 
    u8int low= (u8int)(divisor&0xFF); 
    u8int hi = (u8int)((divisor>>8)&0xFF); 
 
    outb(0x40,low); 
    outb(0x40,hi);
  }
  
  //Set the keyboard LEDs
  void kyb_LED(u8int numl, u8int caps,u8int scrl)
  {
    u8int kyb_byte=0x00,kyb_tempb=0x00;
    
    if(numl==1)
    {
      NumOn=1;
      kyb_byte=kyb_tempb^0x02;
      kyb_tempb=kyb_byte;
    }
    
    else
    {
      NumOn=0;
    }
    
    if(caps==1)
    {
      CapsOn=1;
      kyb_byte=kyb_tempb^0x04;
      kyb_tempb=kyb_byte;
    }
    
    else
    {
      CapsOn=0;
    }
    
    if(scrl==1)
    {
      ScrlOn=1;
      kyb_byte=kyb_tempb^0x01;
      kyb_tempb=kyb_byte;
    }
    
    else
    {
      ScrlOn=0;
    }
    
    ps2_wait_w();
    outb(PS2_RW,KYB_LED);
    
    ps2_wait_w();
    outb(PS2_RW,kyb_byte);
    
    ps2_wait_r();
  }
  
  
  int strcmp( u8int *cha, u8int *chb, u32int len)
  {
    int i,j;
    
    for(j=0;chb[j]==' ';j++);
    
    for(i=0;i<len;i++,j++)
    {
      if(cha[i]!=chb[j])
      {
        return i+1;
      }
    }
    
    return 0;
  }