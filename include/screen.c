//--- Inspiration Kernel Screen Handling Module ---//

# include <screen.h>
# include <memory.h>
# include <common.h>
# include <ports.h>

  u8int cursor_x=0, cursor_y=0;            // Row and column of hardware cursor
  u8int *text_video= (u8int *) 0x0B8000;   // VGA text mode memory
  u8int text_col=0x0F;                     // Attribute for the characters
  u32int put_delay=0;                      // Delay befoe putting a character
  
  u8int *grx_video= (u8int *) 0x0A0000;    // VGA graphics mode memory
  extern u8int cmd_buff[76];
  
  u8int hexarray[]=
  {
    '0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F'
  };

// Put Character on screen
  void putch(u8int ch)
  {
    u32int delay_int;
    for(delay_int=0;delay_int<=put_delay;delay_int++);
    
    if(ch=='\n')                           // If character is a newline
    {
      int i;
      for(i=0;i<75;i++)
      {
        cmd_buff[i]=text_video[(2*(5+i+(cursor_y*80)))];
      }
      cmd_buff[75]='\0';
      cursor_x=0;                          // Set X to zero
      cursor_y++;                          // Increment Y
    }
    
    else if(ch=='\r')                      // If the char is a carriage return
    {
      cursor_x=0;                          // Set X to zero
    }
    
    else if(ch=='\b')                      // If the char is a backspace
    {
      if(cursor_x>5)                       // If the cursor isn't at a
      {                                    // line's beginning.
        cursor_x--;                        // Decrement X
        putch(' ');
        cursor_x--;
      }
      
  /*  else if(cursor_y>0)                  // Otherwise
      {
        cursor_x=79;                       // Set (X,Y) to the end of the
        cursor_y--;                        // previous line.
      }*/
    }
    
    else if(ch=='\t')
    {
      cursor_x+=8-(cursor_x%8);
    }
      
    else if(ch>='!'||ch==' ')
    {  
      text_video[(cursor_x+(cursor_y*80))*2]=ch;
      text_video[((cursor_x+(cursor_y*80))*2)+1]=text_col;
    
      cursor_x++;
    }
    
    if(cursor_x>79)
    {
      cursor_x=0;
      cursor_y++;
      if(cursor_y>24)
      {
        scroll();
        cursor_y=24;
      }
      else
      {
        cursor_y++;
      }

    }
    
    else
    {
      if(cursor_y>24)
      {
        scroll();
        cursor_y=24;
      }
      else
      {
      
      }
    }
    
    update_cursor();        
  }
  
// Put NULL-Terminated string on screen
  void puts(u8int *ch)
  {
    int i;
    for(i=0;ch[i]!='\0';i++)
    {
      putch(ch[i]);
    }
  }
  
// Update the Hardware Cursor
  void update_cursor()
  { 
    u16int cursorLocation = cursor_y*80 + cursor_x; 
    outb (0x3D4,14);
    outb (0x3D5,cursorLocation>>8); 
    outb (0x3D4,15); 
    outb (0x3D5,cursorLocation);
  }
  
// Clear the screen
  void clrscr()
  {
    int i;
    for(i=0;i<25*80;i++)
    {
    text_video[i*2]=' ';
    text_video[(i*2)+1]=text_col;
    }
    cursor_x=0;
    cursor_y=0;
    update_cursor();
  }
  
// Scroll the screen up one line
  void scroll()
  {
    int i;
    memcpy((u8int*)(0x0B8000+160),(u8int*)0x0B8000,24*80*2);
    
    for(i=0;i<160;i+=2)
    {
      text_video[i+(24*160)]=' ';
      text_video[(i+1)+(24*160)]=text_col;
    }
  }
  
// Set the Color attribute of characters displayed on the screen
  void textcolor(u8int attrib)
  {
    text_col=attrib;
  }
  
// Put a number on the screen
  void putint (u32int number) 
  { 
    u32int c,d,e,f;
    u8int chr[]="0123456789";
    e=number;
    
    for(d=1;e!=0;d=d*10)
    {
      c=e%10;
      e=e/10;
    }    
    
    for(d=d/10;d!=0;d=d/10)
    {
      putch(chr[((number/d)%10)]);
    }
    
    if(number==0)
    {
      putch('0');
    }
  }
  
// Set's the character input delay of putch for animating in text mode
  void set_put_delay(u32int delay_num)
  {
    put_delay=delay_num;
  }
  
  // Reset the cursor to the beginnning of the screen
  void reset_cursor()
   {
     cursor_x=0;
     cursor_y=0;
     
     update_cursor();
   }
   
  // Put a byte-sized integer on the screen in hexadecimal
  void puthexb(u8int byte)
  {
    putch(hexarray[byte/16]);
    putch(hexarray[byte%16]);
  }
  
  // Put a word-sized integer on the screen in hexadecimal
  void puthexw(u16int word)
  {
    puthexb((u8int)((word>>8)&0xFF));
    puthexb((u8int)word);
  }
  
  // Put a dword-sized integer on the screen in hexadecimal
  void puthexdw(u32int dword)
  {
    puthexb((u8int)((dword>>24)&0xFF));
    puthexb((u8int)((dword>>16)&0xFF));
    puthexb((u8int)((dword>>8)&0xFF));
    puthexb((u8int)dword);
  }
  
  void dec_cur_x()
  {
    if(cursor_x>5)
    {
      cursor_x--;
    }
    update_cursor();
  }
  
  void inc_cur_x()
  {
    if(cursor_x<79)
    {
      cursor_x++;
    }
    update_cursor();
  }
   
  