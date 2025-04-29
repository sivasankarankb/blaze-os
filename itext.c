#include "proto.h"
// Inspiration Textmode Library
	
  // Updates the hardware cursor
  
  void update_cursor(int pos)
	{
		unsigned short	position = pos;

		// cursor LOW port to vga INDEX register
		out(0x3D4, 0x0F);
		out(0x3D5, (unsigned char)(position&0xFF));
    
		// cursor HIGH port to vga INDEX register
		out(0x3D4, 0x0E);
		out(0x3D5, (unsigned char)((position>>8)&0xFF));
	}

  int tpointer = 0 ;           // Text Pointer - Position of Cursor
  unsigned char tattr = 0x00 ; // Text Attributes - Color of characters

  // Sets the color for kputf
  
  void setccol(unsigned char col)
  {
    tattr = col;
  }

  // Sets the textponter
  
  void settptr(int tptr)
  {
    tpointer=tptr;
  }

  // Sets the background and forground color of every character on the screen
  
  void setbgfg(unsigned char col)
  {
    unsigned char *tvidmem= (unsigned char *)0xB8000;
    int i;
    
    for(i=0;i<80*25;i++)
    {
      tvidmem++;
      *tvidmem=col;
      tvidmem++;
    }
  }

  // Puts a string onto the screen
  
  void kputs(unsigned char *cha)
  {
    int i;
    
    for(i=0; cha[i]!='\0' ;i++)
    {
      kputf(cha[i]);
    }
  }

  // Puts a character without changings it's attribute on the screen

  void kput(unsigned char ch)
  {
    unsigned char *tvidmem= (unsigned char *)0xB8000;
    int caddr=tpointer*2;
    
    tvidmem+=caddr;
    *tvidmem=ch;
    tpointer++;
    
    return;
  }

  // Puts a character with the value set by setcol() on the screen

  void kputf(unsigned char ch)
  {
    
    if(tpointer>=(80*25))
    {
      scroll();
    tpointer-=80;
    }
    
    unsigned char *tvidmem= (unsigned char *)0xB8000;
    int caddr=tpointer*2;
    unsigned char txt_attr=tattr;
    
    tvidmem+=caddr;
    
    if(ch=='\n')
    {
      tpointer+=(80-(tpointer%80))-1;
    }
    
    else if(ch=='\b')
    {
      tpointer-=1;
      kput(' ');
      tpointer-=2;
    }
    
    else if(ch=='\t')
    {
      kput(' ');
      kput(' ');
      kput(' ');
      kput(' ');
      kput(' ');
      kput(' ');
      kput(' ');
      kput(' ');
      tpointer--;
    }
    
    else
    {
      *tvidmem=ch;
    }
    
    tvidmem++;
    *tvidmem=0x00;
    *tvidmem+=txt_attr;
    tpointer++;
    
    update_cursor(tpointer);
    
    return;
  }

  // Scrolls the screen up by one line non-undoable

  void scroll()
  {
    int tvids = 0xB8000+160;
    int tvidc = (0x0B8000+(80*25*2))-tvids;
    
    memcopy((unsigned char *)tvids,(unsigned char *)0x0B8000,tvidc);
    memset((unsigned char *)((0x0B8000+(80*25*2))-80*2),0,80*2);
  }

  // Prints Inspiration Version on the screen with Inline Assembly

  void prASM()
  {
    unsigned char ch[]="v.1";
    
    __asm__("movb %%al,0xB8000\n"::"al"(ch[0]));
    __asm__("movb %%al,0xB8002\n"::"al"(ch[1]));
    __asm__("movb %%al,0xB8004\n"::"al"(ch[2]));
  }
  
  // Clears the screen

  void clrscr()
  {
    unsigned char *tvidmem= (unsigned char *)0xB8000;
    int i;
    
    for(i=0;i<80*25;i++)
    {
      *tvidmem=0;
      tvidmem++;
      *tvidmem=0;
      tvidmem++;
      settptr(0);
      update_cursor(0);
    }
  }
  
  // Test for video mode 0x03
  
  void videomodetst()
  {
    unsigned char *vmode= (unsigned char *)0x0449;
    if(*vmode==0x03)
      kputs("8. Mode 0x03 : Yes\n");
    else
      kputs("8. Mode 0x03 : No\n");
  }
  
  void putnum(int num)
  {
    int len,j,k,num2;
    unsigned char nums[]="0123456789";
    
    num2=num;
    
    for(len=0;num!=0;len++)
    {
      num=num/10;
    }
    
    unsigned char *ttxt;
    ttxt[len]='\0';
    
    for(j=0;j<=len;j++)
    {
      ttxt[len-j-1]=nums[num2%10];
      num2=num2/10; 
    }
    
    kputs(ttxt);    
  }