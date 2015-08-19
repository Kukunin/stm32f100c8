#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stdio_debug.h"
#include "math.h"
#include "lcd.h"

uint16_t RS = GPIO_Pin_0;
uint16_t CS = GPIO_Pin_2;
uint16_t WR = GPIO_Pin_3;
uint16_t RST = GPIO_Pin_4;

#define write_BSRR(byte, mask) (byte & mask) | ((~byte & mask) << 16)

void delay(int ms) {
  volatile int i;
  for(i = 0; i < ms; i++);
}

void digitalWrite(int pin, char value) {
  if(value == 1) {
    GPIOA->BSRR = pin;
  } else {
    GPIOA->BRR = pin;
  }
}

void setDataBus(int c) {
  //printf("Byte: %08x, ", c);
  //printf("ODR: %04x, ", GPIOB->ODR);
  GPIOB->BSRR = write_BSRR(c, 0xff00);
  //Convert 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1
  //To      0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0
  GPIOA->BSRR = write_BSRR(c << 5, 0x1fe0);
  //printf("ODR: %04x\n", GPIOB->ODR);
  //printf("GPIOA: %04x, GPIOB: %04x\n", GPIOA->ODR, GPIOB->ODR);
}

int main()
{

  //Enable GPIO A clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

  //Set PA1 as General purpose output
  GPIO_InitTypeDef GPIOA_StructInit = { GPIO_Pin_All, GPIO_Speed_2MHz, GPIO_Mode_Out_PP };
  GPIO_Init(GPIOA, &GPIOA_StructInit);
  GPIO_InitTypeDef GPIOB_StructInit = { GPIO_Pin_All, GPIO_Speed_2MHz, GPIO_Mode_Out_PP };
  GPIO_Init(GPIOB, &GPIOB_StructInit);

  printf("Hello world\r\n");

  //while(1);

  char buf[318];
  int x, y;
  int i;

  SetLCDSize(LCD_28);
  lcd_init();
  setFont(8,12,32);
  setColor(0x07e0);
  setBackColor(0xf800);

  printf("Init is ok!\n");
  setDataBus(0xff37);
  //while(1);

  while(1)
    {
      printf("Cycle\n");
      clrScr();
      setColorRGB(255, 0, 0);
      fillRect(0, 0, 319, 13);
      setColorRGB(64, 64, 64);
      fillRect(0, 226, 319, 239);
      setColorRGB(255, 255, 255);
      setBackColorRGB(255, 0, 0);
      print("* Universal Color TFT Display Library *", CENTER,1,0);

      setBackColorRGB(64, 64, 64);
      setColorRGB(255,255,0);
      print("<http://electronics.henningkarlsen.com>", CENTER,227,0);
      setColorRGB(0, 0, 255);
      drawRect(0, 14,319,225);

      setColorRGB(0, 0, 255);
      setBackColorRGB(0, 0, 0);
      drawLine(159, 15, 159, 224);
      drawLine(1, 119, 318, 119);
      for (i=9; i<310; i+=10)
        drawLine(i, 117, i, 121);
      for (i=19; i<220; i+=10)
        drawLine(157, i, 161, i);

      setColorRGB(0,255,255);
      print("Sin", 5, 15,0);
      for (i=1; i<318; i++)
        {
          drawPixel(i,119+(sin(((i*1.13)*3.14)/180)*95));
        }

      setColorRGB(255,0,0);
      print("Cos", 5, 27,0);
      for (i=1; i<318; i++)
        {
          drawPixel(i,119+(cos(((i*1.13)*3.14)/180)*95));
        }

      setColorRGB(255,255,0);
      print("Tan", 5, 39,0);
      for (i=1; i<318; i++)
        {
          drawPixel(i,119+(tan(((i*1.13)*3.14)/180)));
        }

      delay(2000);

      setColorRGB(0,0,0);
      fillRect(1,15,318,224);
      setColorRGB(0, 0, 255);
      setBackColorRGB(0, 0, 0);
      drawLine(159, 15, 159, 224);
      drawLine(1, 119, 318, 119);

      x=1;
      for (i=1; i<(318*20); i++)
        {
          x++;
          if (x==319)
            x=1;
          if (i>319)
            {
              if ((x==159)||(buf[x-1]==119))
                setColorRGB(0,0,255);
              else
                setColorRGB(0,0,0);
              drawPixel(x,buf[x-1]);
            }
          setColorRGB(0,255,255);
          y=119+(sin(((i*1.1)*3.14)/180)*(90-(i / 100)));
          drawPixel(x,y);
          buf[x-1]=y;
        }

      delay(2000);

      setColorRGB(0,0,0);
      fillRect(1,15,318,224);

      for (i=1; i<6; i++)
        {
          switch (i)
            {
            case 1:
              setColorRGB(255,0,255);
              break;
            case 2:
              setColorRGB(255,0,0);
              break;
            case 3:
              setColorRGB(0,255,0);
              break;
            case 4:
              setColorRGB(0,0,255);
              break;
            case 5:
              setColorRGB(255,255,0);
              break;
            }
          fillRect(70+(i*20), 30+(i*20), 130+(i*20), 90+(i*20));
        }

      delay(2000);

      setColorRGB(0,0,0);
      fillRect(1,15,318,224);

      for (i=1; i<6; i++)
        {
          switch (i)
            {
            case 1:
              setColorRGB(255,0,255);
              break;
            case 2:
              setColorRGB(255,0,0);
              break;
            case 3:
              setColorRGB(0,255,0);
              break;
            case 4:
              setColorRGB(0,0,255);
              break;
            case 5:
              setColorRGB(255,255,0);
              break;
            }
          fillRoundRect(190-(i*20), 30+(i*20), 250-(i*20), 90+(i*20));
        }

      delay(2000);

      setColorRGB(0,0,0);
      fillRect(1,15,318,224);

      for (i=1; i<6; i++)
        {
          switch (i)
            {
            case 1:
              setColorRGB(255,0,255);
              break;
            case 2:
              setColorRGB(255,0,0);
              break;
            case 3:
              setColorRGB(0,255,0);
              break;
            case 4:
              setColorRGB(0,0,255);
              break;
            case 5:
              setColorRGB(255,255,0);
              break;
            }
          fillCircle(100+(i*20),60+(i*20), 30);
        }

      delay(2000);

      setColorRGB(0,0,0);
      fillRect(1,15,318,224);

      // Draw some lines in a pattern
      setColorRGB(255,0,0);
      for (i=15; i<224; i+=5)
        {
          drawLine(1, i, (i*1.44)-10, 224);
        }
      setColorRGB(255,0,0);
      for (i=224; i>15; i-=5)
        {
          drawLine(318, i, (i*1.44)-11, 15);
        }
      setColorRGB(0,255,255);
      for (i=224; i>15; i-=5)
        {
          drawLine(1, i, 331-(i*1.44), 15);
        }
      setColorRGB(0,255,255);
      for (i=15; i<224; i+=5)
        {
          drawLine(318, i, 330-(i*1.44), 224);
        }

      delay(2000);

      setColorRGB(0,0,0);
      fillRect(1,15,318,224);

      // Draw some random circle
      fillScrRGB(0, 0, 255);
      setColorRGB(255, 0, 0);
      fillRoundRect(80, 70, 239, 169);

      setColorRGB(255, 255, 255);
      setBackColorRGB(255, 0, 0);
      print("That's it!", CENTER, 93,0);
      print("Restarting in a", CENTER, 119,0);
      print("few seconds...", CENTER, 142,0);

      setColorRGB(0, 255, 0);
      setBackColorRGB(0, 0, 255);
      delay(2000);
    }
}
