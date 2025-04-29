//-- Inspiration PS2-related functions Module Header --//
#ifndef PS2_H
#define PS2_H

//~~~~~~~~~~~~~~~~~~~~~~ PS/2-related Defines~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

# define PS2_RW        0x60
# define PS2_COMMAND   0x64
# define PS2_STATUS    0x64
# define KYB_ST_OK     0xAA
# define KYB_LED       0xED
# define KYB_SCANCODE  0xF0
# define PS2_IDENTIFY  0xF2
# define KYB_TYPEDELAY 0xF3
# define KYB_SCAN_YES  0xF4
# define KYB_SCAN_NO   0xF5
# define PS2_ACK       0xFA
# define KYB_RESEND    0xFE
# define KYB_RESET_ST  0xFF
# define PS2_1_EN      0xAE
# define PS2_1_DIS     0xAD

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

  // Prototypes for ps2.c
  void enable_a20();
  void init_keyboard();
  void ps2_wait_r();
  void ps2_wait_w();

#endif