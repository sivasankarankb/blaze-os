// Inspiration ISR Library  

  void enable_ints()
  {
    __asm__("sti");
  }
  
  void disable_ints()
  {
    __asm__("cli");
  }
  
  char misr0[]="\nException : Division by zero";
  char misr1[]="\nException : Debug Exceptions";
  char misr2[]="\nException : Intel Reserved (You shouldn\'t be seeing this!)";
  char misr3[]="\nException : Breakpoint";
  char misr4[]="\nException : Overflow";
  char misr5[]="\nException : Bounds check";
  char misr6[]="\nException : Invalid Opcode";
  char misr7[]="\nException : Coprocessor Not Available";
  char misr8[]="\nException : Double Fault";
  char misr9[]="\nException : Coprocessor Segment Overrun";
  char misr10[]="\nException : Invalid TSS";
  char misr11[]="\nException : Segment Not Present";
  char misr12[]="\nException : Stack Exception";
  char misr13[]="\nException : General Protection Fault";
  char misr14[]="\nException : Page Fault";
  char misr15[]="\nException : Intel Reserved (You shouldn\'t be seeing this!)";
  char misr16[]="\nException : Coprocessor Error";
  char misr17_31[]="\nException : Intel Reserved (You shouldn\'t be seeing this!)";
  
  void isr0()
  {
    kputs(misr0);
    __asm__("cli;hlt;");
  };
  
  void isr1()
  {
    kputs(misr1);
    __asm__("cli;hlt;");
  };
  
  void isr2()
  {
    kputs(misr2);
    __asm__("cli;hlt;");
  };
  
  void isr3()
  {
    kputs(misr3);
    __asm__("cli;hlt;");
  };
  
  void isr4()
  {
    kputs(misr4);
    __asm__("cli;hlt;");
  };
  
  void isr5()
  {
    kputs(misr5);
    __asm__("cli;hlt;");
  };
  
  void isr6()
  {
    kputs(misr6);
    __asm__("cli;hlt;");
  };
  
  void isr7()
  {
    kputs(misr7);
    __asm__("cli;hlt;");
  };
  
  void isr8()
  {
    kputs(misr8);
    __asm__("cli;hlt;");
  };
  
  void isr9()
  {
    kputs(misr9);
    __asm__("cli;hlt;");
  };
  
  void isr10()
  {
    kputs(misr10);
    __asm__("cli;hlt;");
  };
  
  void isr11()
  {
    kputs(misr11);
    __asm__("cli;hlt;");
  };
  
  void isr12()
  {
    kputs(misr12);
    __asm__("cli;hlt;");
  };
  
  void isr13()
  {
    kputs(misr13);
    __asm__("cli;hlt;");
  };
  
  void isr14()
  {
    kputs(misr14);
    __asm__("cli;hlt;");
  };
  
  void isr15()
  {
    kputs(misr15);
    __asm__("cli;hlt;");
  };
  
  void isr16()
  {
    kputs(misr16);
    __asm__("cli;hlt;");
  };
  
  void isr17_31()
  {
    kputs(misr17_31);
    __asm__("cli;hlt;");
  };
  
  void int46()
  {
    kputs("\n\t\t\t    Inspiration v.1.1\n");    
  };
  
  void int47()
  {
    unsigned char chi,chj,chk;
    unsigned int ni,nj,nk;
    __asm__("" : "=bh"(chi));
    
    if(chi==0)
    {
      __asm__("" : "=ax"(chj),"=cx"(chk),"=edx"(ni));
      memset((unsigned char *) ni,chj,(0+chk));
    }
    
    else if(chi==1)
    {
      __asm__("" : "=eax"(ni),"=ecx"(nj),"=dx"(nk));
      memcopy((unsigned char *) ni,(unsigned char *) nj,nk);
    }    
  };
  