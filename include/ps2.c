//-- Inspiration PS2-related functions Module --// 
# include <ps2.h>
# include <interrupts.h>
# include <ports.h>
  
  // Enable the a20 line if necessary
  void enable_a20()
   {
     char a20b;                          // The byte from PS/2 config byte
     
     ps2_wait_w();
     outb(PS2_COMMAND,PS2_1_DIS);        // Disable first PS/2 Device
     
     ps2_wait_w();
     outb(PS2_COMMAND,0xD0);             // Commmand : Read config byte
     a20b=inb(PS2_RW);                   // Get status byte
     
     if((a20b&0x02)!=0x02)               // If a20 wasn't enabled
      {
        outb(PS2_COMMAND,0xD1);          // Command : Write config byte
        outb(PS2_COMMAND,a20b|0x02);     // Set the modified byte
        //puts("\n\tA20 Line enabled");
      }
      
     else                                // If a20 was enabled
      {
        //puts("\n\tA20 Line is already enabled");
      }
     
     ps2_wait_w();
     outb(PS2_COMMAND,PS2_1_EN);         // Enable first PS/2 Device
   }
   
  // Initialize the Keyboard
  void init_keyboard()
   {
       ps2_wait_w();
       outb(PS2_RW,KYB_SCAN_NO);         // Desable keyboard scanning
       ps2_wait_r();
       
       ps2_wait_w();
       outb(PS2_RW,KYB_RESET_ST);        // Do a self test
       ps2_wait_r();
         
       ps2_wait_w();
       outb(PS2_RW,KYB_SCANCODE);        // Change scancode set to set 1
       ps2_wait_w();
       outb(PS2_RW,0x00);
       ps2_wait_r();
                
       ps2_wait_w();
       outb(PS2_RW,KYB_TYPEDELAY);       // Set typematic info
       ps2_wait_w();
       outb(PS2_RW,0x23);
       ps2_wait_r();
                
       ps2_wait_w();
       outb(PS2_RW,KYB_SCAN_YES);        // Enable scanning
       ps2_wait_r();
       
       kyb_LED(1,0,0);       
         
       //puts("\n\tKeyboard configured");
   }
   
  // Wait for PS/2 output buffer to be empty
  void ps2_wait_w()
   {
     char ch;
     for(;;)
     {
       ch=inb(PS2_STATUS);           // Read status byte
       
       if(!(ch&0x02))                // If output buffer full flag is clear
        {
          break;                     // Finish
        }
     }     
   }
  
  // Wait for PS/2 input buffer to be full
  void ps2_wait_r()
   {
     char ch;
     for(;;)
     {
       ch=inb(PS2_STATUS);          // Read status byte
       
       if((ch&0x01))                // If input buffer full flag is set
        {
          break;                    // Finish
        }
     }     
   }