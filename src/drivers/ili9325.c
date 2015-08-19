#include "lcd.h"

const uint16_t lcd_x_size = 239;
const uint16_t lcd_y_size = 319;
extern uint16_t RS, CS, WR, RST;

void send_command(uint16_t c);
void send_data(uint16_t d);
void send_command_data(uint16_t cmd, uint16_t data);

void lcd_init()
{
  digitalWrite(RST, 1);
  digitalWrite(RST, 0);
  digitalWrite(RST, 1);
  digitalWrite(CS, 1);
  digitalWrite(WR, 1);

  send_command_data(0x00E5, 0x78F0); // set SRAM internal timing
  send_command_data(0x0001, 0x0100); // set Driver Output Control
  send_command_data(0x0002, 0x0200); // set 1 line inversion
  send_command_data(0x0003, 0x1030); // set GRAM write direction and BGR=1.
  send_command_data(0x0004, 0x0000); // Resize register
  send_command_data(0x0008, 0x0207); // set the back porch and front porch
  send_command_data(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
  send_command_data(0x000A, 0x0000); // FMARK function
  send_command_data(0x000C, 0x0000); // RGB interface setting
  send_command_data(0x000D, 0x0000); // Frame marker Position
  send_command_data(0x000F, 0x0000); // RGB interface polarity
  //*************Power 00On sequence ****************//
  send_command_data(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
  send_command_data(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
  send_command_data(0x0012, 0x0000); // VREG1OUT voltage
  send_command_data(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
  send_command_data(0x0007, 0x0001);
  delay(200); // Dis-ch00arge capacitor power voltage
  send_command_data(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
  send_command_data(0x0011, 0x0227); // Set DC1[2:0], DC0[2:0], VC[2:0]
  delay(50); // Delay 5000ms
  send_command_data(0x0012, 0x000D); // 0012
  delay(50); // Delay 5000ms
  send_command_data(0x0013, 0x1200); // VDV[4:0] for VCOM amplitude
  send_command_data(0x0029, 0x000A); // 04  VCM[5:0] for VCOMH
  send_command_data(0x002B, 0x000D); // Set Frame Rate
  delay(50); // Delay 5000ms
  send_command_data(0x0020, 0x0000); // GRAM horizontal Address
  send_command_data(0x0021, 0x0000); // GRAM Vertical Address
  // ----------- Adjust00 the Gamma Curve ----------//
  send_command_data(0x0030, 0x0000);
  send_command_data(0x0031, 0x0404);
  send_command_data(0x0032, 0x0003);
  send_command_data(0x0035, 0x0405);
  send_command_data(0x0036, 0x0808);
  send_command_data(0x0037, 0x0407);
  send_command_data(0x0038, 0x0303);
  send_command_data(0x0039, 0x0707);
  send_command_data(0x003C, 0x0504);
  send_command_data(0x003D, 0x0808);
  //------------------ 00Set GRAM area ---------------//
  send_command_data(0x0050, 0x0000); // Horizontal GRAM Start Address
  send_command_data(0x0051, 0x00EF); // Horizontal GRAM End Address
  send_command_data(0x0052, 0x0000); // Vertical GRAM Start Address
  send_command_data(0x0053, 0x013F); // Vertical GRAM Start Address
  send_command_data(0x0060, 0xA700); // Gate Scan Line
  send_command_data(0x0061, 0x0001); // NDL,VLE, REV
  send_command_data(0x006A, 0x0000); // set scrolling line
  //-------------- Part00ial Display Control ---------//
  send_command_data(0x0080, 0x0000);
  send_command_data(0x0081, 0x0000);
  send_command_data(0x0082, 0x0000);
  send_command_data(0x0083, 0x0000);
  send_command_data(0x0084, 0x0000);
  send_command_data(0x0085, 0x0000);
  //-------------- Pane00l Control -------------------//
  send_command_data(0x0090, 0x0010);
  send_command_data(0x0092, 0x0000);
  send_command_data(0x0007, 0x0133);
}

void set_xy(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1)
{
  swap(x0, y0);
  swap(x1, y1);
  y0=lcd_y_size-y0;
  y1=lcd_y_size-y1;
  swap(y0, y1);

  send_command_data(0x20,x0);
  send_command_data(0x21,y0);
  send_command_data(0x50,x0);
  send_command_data(0x52,y0);
  send_command_data(0x51,x1);
  send_command_data(0x53,y1);
  send_command(0x22);
}

void lcd_off()
{
  send_command(0x28);
}

void lcd_on()
{
  send_command(0x29);
}

void set_pixel(uint16_t color)
{
  send_data(color);
}

/* Private methods */
void send_command(uint16_t c)
{
  digitalWrite(RS,0);
  digitalWrite(CS,0);
  setDataBus(c);
  digitalWrite(WR,0);
  digitalWrite(WR,1);
  digitalWrite(CS,1);
}
void send_data(uint16_t d)
{
  digitalWrite(RS,1);
  digitalWrite(CS,0);
  setDataBus(d);
  digitalWrite(WR,0);
  digitalWrite(WR,1);
  digitalWrite(CS,1);

}
void send_command_data(uint16_t cmd, uint16_t data)
{
  send_command(cmd);
  send_data(data);
}
