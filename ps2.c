#include "proto.h"
// Inspiration PS/2 Functions Library

  void enablemouse()
  {
    io_wait_ps2_w();
    out(0x64,0xAD);      // Disable Keyboard
    
    io_wait_ps2_w();
    out(0x64,0xA8);      // Enable 2nd PS/2 Port
    
    io_wait_ps2_w();
    out(0x64,0xD4);      // Send next byte to 2nd PS/2 Device
    
    io_wait_ps2_w();
    out(0x60,0xF4);      // Tell Mouse to Enable Data Reporting
    
    io_wait_ps2_w();
    out(0x64,0xAE);      // Enable Keyboard  
  }

  void set_scancode_1()
  {
    io_wait_ps2_w();
    out(0x60,0xF0);
    io_wait_ps2_w();
    out(0x60,0x00);
  }

  void setLEDs(int scrolllock,int numlock,int capslock)
  {
    unsigned char data_byte=0;
   
    if(scrolllock==1)
    {
      data_byte=data_byte|1;
    }
   
    if(numlock==1)
    {
      data_byte=data_byte|2;
    }
   
    if(capslock==1)
    {
      data_byte=data_byte|4;
    }

    io_wait_ps2_w();
    out(0x60,0xED);
    
    io_wait_ps2_w();
    out(0x60,data_byte);
  }
  
  void io_wait_ps2_w()
  {
   unsigned char inv;
    for(;;)
    {
      inv=in(0x64);
      inv=inv<<6;
      inv=inv>>7;
      if(inv==0)
      {
        break;
      }
    }
  }
   
  void io_wait_ps2_r()
  {
   unsigned char inv;
    for(;;)
    {
      inv=in(0x64);
      inv=inv<<7;
      inv=inv>>7;
      if(inv==1)
      {
        break;
      }
    }
  }