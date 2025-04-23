// Inspiration IRQ Library

int lshft=0;
int lctrl=0;
int lalt=0;

int rshft=0;
int rctrl=0;
int ralt=0;

  void irq0()
  {
  
  };
  
  char US_QWERTY_1[128]={
  // Key Presses

  1,//Escape
  '1','2','3','4','5','6','7','8','9','0',
  '-','=',
  '\b','\t',//Backspace and Tab
  'q','w','e','r','t','y','u','i','o','p',
  '[',']',
  '\n',//Enter
  2,//Left Control
  'a','s','d','f','g','h','j','k','l',
  ';','\'','`',
  3,//Left Shift
  '\\',
  'z','x','c','v','b','n','m',',','.',
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
  
  char US_QWERTY_1_sh[128]={
  // Key Presses

  1,//Escape
  '!','@','#','$','%','^','&','*','(',')',
  '_','+',
  '\b','\t',//Backspace and Tab
  'Q','W','E','R','T','Y','U','I','O','P',
  '{','}',
  '\n',//Enter
  2,//Left Control
  'A','S','D','F','G','H','J','K','L',
  ':','\"','~',
  3,//Left Shift
  '|',
  'Z','X','C','V','B','N','M',',','.',
  '?',
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
    char ch;         // The byte recieved from KBC
    
    io_wait_ps2_r(); // Wait for input buffer to be full
    ch=in(0x60);     // Receive Byte from KBC
    
    // If the key was just pressed
    if((!(ch&0x80))&&ch>0x0&&ch<0x53)
    {
      // If Escape was Pressed
      if(US_QWERTY_1[ch-1]==1)
      {
        reboot(); // Reboot the system
      }
      
      // If the key pressed is not Escape
      else
      {
        // If the character is 'Displayable'
        if(US_QWERTY_1[ch-1]>0x20)
        {
          // If Capslock is on and if the character is between a to z
          if(capl==1&&US_QWERTY_1[ch-1]>='a'&&US_QWERTY_1[ch-1]<='z')
            kputf(US_QWERTY_1_sh[ch-1]);
          
          // If lshift or rshift is pressed
          else if(lshft==1||rshft==1)
          {
            // If Capslock is off
            if(!capl)
            {
              kputf(US_QWERTY_1_sh[ch-1]);
            }
            // if Capslock is on & charactes is between a to z
            else if(capl==1&&US_QWERTY_1[ch-1]>='a'&&US_QWERTY_1[ch-1]<='z')
            {
              kputf(US_QWERTY_1[ch-1]);
            }
            // Otherwise
            else
            {
              kputf(US_QWERTY_1_sh[ch-1]);
            }
          }
          // If none of these are true
          else
          {
            kputf(US_QWERTY_1[ch-1]);
          }
        }
        
        // If the character is 'Undisplayable' and is capslock
        else if(US_QWERTY_1[ch-1]==14)
        {
          // If capslock is off
          if(capl==0)
          {
            setLEDs(scrl,numl,1);
          }
          // Otherwise
          else
          {
            setLEDs(scrl,numl,0);
          }
        }
        
        //If the 'Undispayable' character is number lock
        else if(US_QWERTY_1[ch-1]==15)
        {
          // If numlock if off
          if(numl==0)
          {
            setLEDs(scrl,1,capl);
          }
          // Otherwise
          else
          {
            setLEDs(scrl,0,capl);
          }
        }
        
        // If the character is scroll lock
        else if(US_QWERTY_1[ch-1]==16)
        {
          // If scroll lock is off
          if(scrl==0)
          {
            setLEDs(1,numl,capl);
          }
          // Otherwise
          else
          {
            setLEDs(0,numl,capl);
          }
        }
        
        // If the charecter is enter,tab,backspace or space
        else if(US_QWERTY_1[ch-1]=='\n'||US_QWERTY_1[ch-1]=='\t'||US_QWERTY_1[ch-1]=='\b'||US_QWERTY_1[ch-1]==' ')
        {
          kputf(US_QWERTY_1[ch-1]);
        }
        
        // If the key pressed is lshift or rshift
        else if(US_QWERTY_1[ch-1]==3||US_QWERTY_1[ch-1]==4)
        {
          // If the key is lshift
          if(US_QWERTY_1[ch-1]==3)
          {
            lshft=1;
          }
          // If the key is rshift
          else if(US_QWERTY_1[ch-1]==4)
          {
            rshft=1;
          }
        }
      }      
    }
    
    // If the key was just released
    else if ((ch&0x80))
    {
      // If the key released is lshift
      if(ch^0x80==0x2A)
      {
        lshft=rshft=0;
      }
      // If the key released is rshift
      else if(ch^0x80==0x36)
      {
        rshft=0;
      }
      else
      {
      
      }
    }
    
    else
    {
    
    }
  end:;
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