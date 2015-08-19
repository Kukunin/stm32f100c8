#include "lcd.h"

const uint16_t lcd_x_size = 239;
const uint16_t lcd_y_size = 319;

void lcd_init()
{
  digitalWrite(RST, 1);
  digitalWrite(RST, 0);
  digitalWrite(RST, 1);
  digitalWrite(CS, 1);
  digitalWrite(WR, 1);

  WriteCommandData(0x00E5, 0x78F0); // set SRAM internal timing
  WriteCommandData(0x0001, 0x0100); // set Driver Output Control
  WriteCommandData(0x0002, 0x0200); // set 1 line inversion
  WriteCommandData(0x0003, 0x1030); // set GRAM write direction and BGR=1.
  WriteCommandData(0x0004, 0x0000); // Resize register
  WriteCommandData(0x0008, 0x0207); // set the back porch and front porch
  WriteCommandData(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
  WriteCommandData(0x000A, 0x0000); // FMARK function
  WriteCommandData(0x000C, 0x0000); // RGB interface setting
  WriteCommandData(0x000D, 0x0000); // Frame marker Position
  WriteCommandData(0x000F, 0x0000); // RGB interface polarity
  //*************Power 00On sequence ****************//
  WriteCommandData(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
  WriteCommandData(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
  WriteCommandData(0x0012, 0x0000); // VREG1OUT voltage
  WriteCommandData(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
  WriteCommandData(0x0007, 0x0001);
  delay(200); // Dis-ch00arge capacitor power voltage
  WriteCommandData(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
  WriteCommandData(0x0011, 0x0227); // Set DC1[2:0], DC0[2:0], VC[2:0]
  delay(50); // Delay 5000ms
  WriteCommandData(0x0012, 0x000D); // 0012
  delay(50); // Delay 5000ms
  WriteCommandData(0x0013, 0x1200); // VDV[4:0] for VCOM amplitude
  WriteCommandData(0x0029, 0x000A); // 04  VCM[5:0] for VCOMH
  WriteCommandData(0x002B, 0x000D); // Set Frame Rate
  delay(50); // Delay 5000ms
  WriteCommandData(0x0020, 0x0000); // GRAM horizontal Address
  WriteCommandData(0x0021, 0x0000); // GRAM Vertical Address
  // ----------- Adjust00 the Gamma Curve ----------//
  WriteCommandData(0x0030, 0x0000);
  WriteCommandData(0x0031, 0x0404);
  WriteCommandData(0x0032, 0x0003);
  WriteCommandData(0x0035, 0x0405);
  WriteCommandData(0x0036, 0x0808);
  WriteCommandData(0x0037, 0x0407);
  WriteCommandData(0x0038, 0x0303);
  WriteCommandData(0x0039, 0x0707);
  WriteCommandData(0x003C, 0x0504);
  WriteCommandData(0x003D, 0x0808);
  //------------------ 00Set GRAM area ---------------//
  WriteCommandData(0x0050, 0x0000); // Horizontal GRAM Start Address
  WriteCommandData(0x0051, 0x00EF); // Horizontal GRAM End Address
  WriteCommandData(0x0052, 0x0000); // Vertical GRAM Start Address
  WriteCommandData(0x0053, 0x013F); // Vertical GRAM Start Address
  WriteCommandData(0x0060, 0xA700); // Gate Scan Line
  WriteCommandData(0x0061, 0x0001); // NDL,VLE, REV
  WriteCommandData(0x006A, 0x0000); // set scrolling line
  //-------------- Part00ial Display Control ---------//
  WriteCommandData(0x0080, 0x0000);
  WriteCommandData(0x0081, 0x0000);
  WriteCommandData(0x0082, 0x0000);
  WriteCommandData(0x0083, 0x0000);
  WriteCommandData(0x0084, 0x0000);
  WriteCommandData(0x0085, 0x0000);
  //-------------- Pane00l Control -------------------//
  WriteCommandData(0x0090, 0x0010);
  WriteCommandData(0x0092, 0x0000);
  WriteCommandData(0x0007, 0x0133);
}
