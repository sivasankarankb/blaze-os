// Inspiration IRQ Library

  void irq0()
  {
  
  };
  
  char US_QWERTY_1[128]={
  // Key Presses

  1,//Escape
  '1','2','3','4','5','6','7','8','9','0',
  '-','=',
  '\b','\t',//Backspace and Tab
  'Q','W','E','R','T','Y','U','I','O','P',
  '[',']',
  '\n',//Enter
  2,//Left Control
  'A','S','D','F','G','H','J','K','L',
  ';','\'','`',
  3,//Left Shift
  '\\',
  'Z','X','C','V','B','N','M',',','.',
  '/',
  4,//Right Shift
  '*',
  5,//Left Alt
  ' ',//Spacebar
  14,//Capslock
  17,18,19,20,21,22,23,24,25,26,//F1 to F10
  15,//Number Lock
  16,//Scroll Lock
  
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
  27,28,// F11 and F12
  
  // Key Presses End
  0     // That's all
  };

  void irq1()
  {
    char ch;
    
    //io_wait_ps2_r();
    ch=in(0x60);
    
    if((!(ch&0x80))&&ch>0x0&&ch<0x53)
    {
      if(US_QWERTY_1[ch-1]==1)
      {
//        __asm__(" mov $0xFE,%al;\
  //                out %al,$0x64; ");
      }
      
      else
      {
        if(US_QWERTY_1[ch-1]>0x20)
        {
          kputf(US_QWERTY_1[ch-1]);
        }
        
        else if(US_QWERTY_1[ch-1]=='\n'||US_QWERTY_1[ch-1]=='\t'||US_QWERTY_1[ch-1]=='\b'||US_QWERTY_1[ch-1]==' ')
        {
          kputf(US_QWERTY_1[ch-1]);
        }
      }      
    }
    
    else
    {
    
    }
  };
  
  void irq2()
  {
  
  };
  
  void irq3()
  {
  
  };
  
  void irq4()
  {
  
  };
  
  void irq5()
  {
  
  };
  
  void irq6()
  {
  
  };
  
  void irq7()
  {
  
  };
  
  void irq8()
  {
  
  };
  
  void irq9()
  {
  
  };
  
  void irq10()
  {
  
  };
  
  void irq11()
  {
  
  };
  
  void irq12()
  {
    kputs("\nMouse\n");
  };
  
  void irq13()
  {
  
  };
  
  void irq14()
  {
  
  };
  
  void irq15()
  {
  
  };