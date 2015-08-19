#include "lcd.h"
#include "SFont.h"

uint8_t lcd_orientation = LANDSCAPE;
/* Unprocessed */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


extern const unsigned char PSmallFont[1144];
extern const unsigned char PBigFont[3044];
extern const unsigned char PSevenSegNumFont[2004];

int TP_X,TP_Y;
int fch,fcl,bch,bcl;
unsigned short int x_Size,y_Size,offset;
const unsigned char* font;
unsigned long int  touch_x_left, touch_x_right, touch_y_top, touch_y_bottom;
unsigned long int  _default_orientation;
unsigned char      prec;
int 	           gLCDSize;
int  		   SDA1,SCL1;

void SetLCDSize(int a)
{
  gLCDSize = a;
}

void fillScr(unsigned int color)
{
  int i,j;
  set_xy(0,0,lcd_y_size,lcd_x_size);

  for(i=0;i<lcd_x_size;i++)
    {
      for (j=0;j<lcd_y_size;j++)
        {
          set_pixel(color);
        }
    }
}

void fillScrRGB(int r, int g, int b)
{
  int color;

  color = ((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
  fillScr(color);
}

void clrScr()
{
  unsigned int i,j;
  set_xy(0,0,lcd_y_size,lcd_x_size);
  for(i=0;i<240;i++)
    {
      for(j=0;j<320;j++)
        {
          set_pixel(0x0000);
        }
    }

}
void clrXY()
{
  //	if (lcd_orientation==PORTRAIT)
  if(0)
    {
      set_xy(0,0,lcd_x_size,lcd_y_size);
    }
  else
    {
      set_xy(0,0,lcd_y_size,lcd_x_size);
    }
}
void setColor(long int color)
{
  fch=(color>>8);
  fcl=(color & 0xFF);
}
void setColorRGB(int r, int g, int b)
{
  fch=((r&248)|g>>5);
  fcl=((g&28)<<3|b>>3);
}
void setBackColor(int color)
{
  bch=(int)(color>>8);
  bcl=(int)(color & 0xFF);
}
void setBackColorRGB(int r, int g, int b)
{
  bch=((r&248)|g>>5);
  bcl=((g&28)<<3|b>>3);
}
void drawRect(int x1, int y1, int x2, int y2)
{
  drawHLine(x1, y1, x2-x1);
  drawHLine(x1, y2, x2-x1);
  drawVLine(x1, y1, y2-y1);
  drawVLine(x2, y1, y2-y1);
}
void drawHLine(int x, int y, int l)
{
  int j;
  if (l<0)
    {
      l = -l;
      y -= l;
    }

  set_xy(x,y,x+l,y);

  for (j=x;j<x+l;j++)
    {
      set_pixel((fch<<8)|fcl);
    }

  clrXY();
}

void drawVLine(int x, int y, int l)
{
  int j;
  if (l<0)
    {
      l = -l;
      y -= l;
    }

  set_xy(x,y,x,y+l);
  for (j=y;j<y+l;j++)
    {
      set_pixel((fch<<8)|fcl);
    }

  clrXY();
}
void drawLine(int x1, int y1, int x2, int y2)
{
  int t,col,row;
  unsigned int dx,dy;
  short int xstep,ystep;

  if (y1==y2)
    {
      drawHLine(x1, y1, x2-x1);
    }
  else if (x1==x2)
    {
      drawVLine(x1, y1, y2-y1);
    }
  else
    {
      dx = (x2 > x1 ? x2 - x1 : x1 - x2);
      xstep =  x2 > x1 ? 1 : -1;
      dy = (y2 > y1 ? y2 - y1 : y1 - y2);
      ystep =  y2 > y1 ? 1 : -1;
      col = x1, row = y1;

      if (dx < dy)
        {
          t = - (dy >> 1);
          while (1)
            {
              set_xy (col, row, col, row);
              set_pixel((fch<<8)|fcl);
              if (row == y2)
                return;
              row += ystep;
              t += dx;
              if (t >= 0)
                {
                  col += xstep;
                  t   -= dy;
                }
            }
        }
      else
        {
          t = - (dx >> 1);
          while (1)
            {
              set_xy (col, row, col, row);
              set_pixel ((fch<<8)|fcl);
              if (col == x2)
                return;
              col += xstep;
              t += dy;
              if (t >= 0)
                {
                  row += ystep;
                  t   -= dx;
                }
            }
        }
    }
  clrXY();
}
void drawRoundRect(int x1, int y1, int x2, int y2)
{
  if (x1>x2)
    {
      swap(x1, x2);
    }
  if (y1>y2)
    {
      swap(y1, y2);
    }
  if ((x2-x1)>4 && (y2-y1)>4)
    {
      drawPixel(x1+1,y1+1);
      drawPixel(x2-1,y1+1);
      drawPixel(x1+1,y2-1);
      drawPixel(x2-1,y2-1);
      drawHLine(x1+2, y1, x2-x1-4);
      drawHLine(x1+2, y2, x2-x1-4);
      drawVLine(x1, y1+2, y2-y1-4);
      drawVLine(x2, y1+2, y2-y1-4);
    }
}
void drawPixel(int x, int y)
{
  set_xy(x, y, x, y);
  //	set_xy(y,x,y,x);
  set_pixel((fch<<8)|fcl);
}
void fillRect(int x1, int y1, int x2, int y2)
{
  int i;
  if (x1>x2)
    {
      swap(x1, x2);
    }
  if (y1>y2)
    {
      swap(y1, y2);
    }
  set_xy(x1, y1, x2, y2);
  set_pixel((fch<<8)|fcl);

  set_pixel(((long)(x2-x1)+1)*((long)(y2-y1)+1));
  if (lcd_orientation==PORTRAIT)
    //	if(0)
    {
      for (i=0; i<(((y2-y1)/2)+1); i++)
        {
          drawHLine(x1, y1+i, x2-x1);
          drawHLine(x1, y2-i, x2-x1);
          //	delay(100);
        }
    }
  else
    {
      for (i=0; i<((x2-x1)/2)+1; i++)
        {
          drawVLine(x1+i, y1, y2-y1);
          drawVLine(x2-i, y1, y2-y1);
          //	delay(100);
        }
    }


}
void fillRoundRect(int x1, int y1, int x2, int y2)
{
  int i;
  if (x1>x2)
    {
      swap(x1, x2);
    }
  if (y1>y2)
    {
      swap(y1, y2);
    }

  if ((x2-x1)>4 && (y2-y1)>4)
    {
      for (i=0; i<((y2-y1)/2)+1; i++)
        {
          switch(i)
            {
            case 0:
              drawHLine(x1+2, y1+i, x2-x1-4);
              drawHLine(x1+2, y2-i, x2-x1-4);
              //delay(100);
              break;
            case 1:
              drawHLine(x1+1, y1+i, x2-x1-2);
              drawHLine(x1+1, y2-i, x2-x1-2);
              //delay(100);
              break;
            default:
              drawHLine(x1, y1+i, x2-x1);
              drawHLine(x1, y2-i, x2-x1);
            }
        }
    }
}
void drawCircle(int x, int y, int radius)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x1 = 0;
  int y1 = radius;

  set_xy(x, y + radius, x, y + radius);

  set_pixel((fch<<8)|fcl);
  set_xy(x, y - radius, x, y - radius);

  set_pixel((fch<<8)|fcl);
  set_xy(x + radius, y, x + radius, y);

  set_pixel((fch<<8)|fcl);
  set_xy(x - radius, y, x - radius, y);

  set_pixel((fch<<8)|fcl);

  while(x1 < y1)
    {
      if(f >= 0)
        {
          y1--;
          ddF_y += 2;
          f += ddF_y;
        }
      x1++;
      ddF_x += 2;
      f += ddF_x;
      set_xy(x + x1, y + y1, x + x1, y + y1);

      set_pixel((fch<<8)|fcl);
      set_xy(x - x1, y + y1, x - x1, y + y1);

      set_pixel((fch<<8)|fcl);
      set_xy(x + x1, y - y1, x + x1, y - y1);

      set_pixel((fch<<8)|fcl);
      set_xy(x - x1, y - y1, x - x1, y - y1);

      set_pixel((fch<<8)|fcl);
      set_xy(x + y1, y + x1, x + y1, y + x1);

      set_pixel((fch<<8)|fcl);
      set_xy(x - y1, y + x1, x - y1, y + x1);

      set_pixel((fch<<8)|fcl);
      set_xy(x + y1, y - x1, x + y1, y - x1);

      set_pixel((fch<<8)|fcl);
      set_xy(x - y1, y - x1, x - y1, y - x1);

      set_pixel((fch<<8)|fcl);
    }
  clrXY();
}
void fillCircle(int x, int y, int radius)
{
  int y1,x1;
  for(y1=-radius; y1<=0; y1++)
    for(x1=-radius; x1<=0; x1++)
      if(x1*x1+y1*y1 <= radius*radius)
        {
          drawHLine(x+x1, y+y1, 2*(-x1));
          drawHLine(x+x1, y-y1, 2*(-x1));
          break;
        }
}
void setFont(unsigned short int mxsize,unsigned short int mysize,unsigned short int moffset)
{
  x_Size=mxsize;
  y_Size=mysize;
  offset=moffset;
}

void printChar(unsigned char c, int x, int y)
{
  unsigned char i;
  unsigned char ch;
  unsigned int j;
  unsigned int temp;
  int zz;

  if(x_Size == 16)
    {
      font = &PBigFont[0];
    }
  else if(x_Size == 32)
    {
      font = &PSevenSegNumFont[0];
    }
  else
    {
      font = &PSmallFont[0];
    }

  if (lcd_orientation==PORTRAIT)
    //	if(0)
    {
      set_xy(x,y,x+x_Size-1,y+y_Size-1);
      temp=((c-offset)*((x_Size/8)*y_Size))+4;
      for(j=0;j<((x_Size/8)*y_Size);j++)
        {
          ch =(unsigned char) *(&font[temp]);
          for(i=0;i<8;i++)
            {
              if((ch&(1<<(7-i)))!=0)
                {
                  set_pixel((fch<<8)|fcl);
                }
              else
                {
                  set_pixel((bch<<8)|bcl);
                }
            }
          temp++;
        }
    }
  else
    {
      temp=((c-offset)*((x_Size/8)*y_Size))+4;

      for(j=0;j<((x_Size/8)*y_Size);j+=(x_Size/8))
        {
          set_xy(x,y+(j/(x_Size/8)),x+x_Size-1,y+(j/(x_Size/8)));
          for (zz=(x_Size/8)-1; zz>=0; zz--)
            {
              ch = (unsigned char)*(&font[temp+zz]);
              for(i=0;i<8;i++)
                {
                  if((ch&(1<<i))!=0)
                    {
                      set_pixel((fch<<8)|fcl);
                    }
                  else
                    {
                      set_pixel((bch<<8)|bcl);
                    }
                }
            }
          temp+=(x_Size/8);
        }
    }
  clrXY();

}
void rotateChar(unsigned char c, int x, int y, int pos, int deg)
{
  unsigned char i,j,ch;
  unsigned int temp;
  unsigned int newx,newy;
  int zz;
  double radian;
  radian=deg*0.0175;

  //font = &PSmallFont[0];
  if(x_Size == 16)
    {
      font = &PBigFont[0];
    }
  else if(x_Size == 32)
    {
      font = &PSevenSegNumFont[0];
    }
  else
    {
      font = &PSmallFont[0];
    }
  temp=((c-offset)*((x_Size/8)*y_Size))+4;
  for(j=0;j<y_Size;j++)
    {
      for (zz=0; zz<(x_Size/8); zz++)
        {
          //ch=pgm_read_byte(&cfont.font[temp+zz]);
          ch=*(&font[temp+zz]);
          for(i=0;i<8;i++)
            {
              newx=x+(((i+(zz*8)+(pos*x_Size))*cos(radian))-((j)*sin(radian)));
              newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*x_Size))*sin(radian)));

              set_xy(newx,newy,newx+1,newy+1);
              if((ch&(1<<(7-i)))!=0)
                {
                  set_pixel((fch<<8)|fcl);
                }
              else
                {
                  set_pixel((bch<<8)|bcl);
                }
            }
        }
      temp+=(x_Size/8);
    }
  clrXY();
}
void print(char *st, int x, int y, int deg)
{
  int stl, i;

  stl = strlen(st);

  if (lcd_orientation==PORTRAIT)
    //	if(0)
    {
      if (x==RIGHT)
        x=(lcd_x_size+1)-(stl*x_Size);
      if (x==CENTER)
        x=((lcd_x_size+1)-(stl*x_Size))/2;
    }
  else
    {
      if (x==RIGHT)
        x=(lcd_y_size+1)-(stl*x_Size);
      if (x==CENTER)
        x=((lcd_y_size+1)-(stl*x_Size))/2;
    }

  for (i=0; i<stl; i++)
    if (deg==0)
      printChar(*st++, x + (i*(x_Size)), y);
    else
      rotateChar(*st++, x, y, i, deg);
}
const unsigned char* getFont()
{
  return font;
}

unsigned int getFontXsize()
{
  return x_Size;
}

unsigned int getFontYsize()
{
  return y_Size;
}
int getDisplayXSize()
{
  if (lcd_orientation==PORTRAIT)
    //	if(0)
    return lcd_x_size+1;
  else
    return lcd_y_size+1;
}

int getDisplayYSize()
{
  if (lcd_orientation==PORTRAIT)
    //	if(0)
    return lcd_y_size+1;
  else
    return lcd_x_size+1;
}
void printNumI(long num, int x, int y, int length, char filler)
{
  char buf[25];
  char st[27];
  int neg=0;
  int c=0, f=0;
  int i;

  if (num==0)
    {
      if (length!=0)
        {
          for (c=0; c<(length-1); c++)
            st[c]=filler;
          st[c]=48;
          st[c+1]=0;
        }
      else
        {
          st[0]=48;
          st[1]=0;
        }
    }
  else
    {
      if (num<0)
        {
          neg=1;
          num=-num;
        }

      while (num>0)
        {
          buf[c]=48+(num % 10);
          c++;
          num=(num-(num % 10))/10;
        }
      buf[c]=0;

      if (neg)
        {
          st[0]=45;
        }

      if (length>(c+neg))
        {
          for (i=0; i<(length-c-neg); i++)
            {
              st[i+neg]=filler;
              f++;
            }
        }

      for (i=0; i<c; i++)
        {
          st[i+neg+f]=buf[c-i-1];
        }
      st[c+neg+f]=0;

    }

  print(st,x,y,0);
}
void printNumF(double num, unsigned char dec, int x, int y, char divider, int length, char filler)
{
  char buf[25];
  char st[27];
  int neg=0;
  int c=0, f=0;
  int c2;
  long mult;
  unsigned long inum;
  int i,j;

  if (dec<1)
    dec=1;
  if (dec>5)
    dec=5;

  if (num==0)
    {
      if (length!=0)
        {
          for (c=0; c<(length-2-dec); c++)
            st[c]=filler;
          st[c]=48;
          st[c+1]=divider;
          for (i=0; i<dec; i++)
            st[c+2+i]=48;
          st[c+2+dec]=0;
        }
      else
        {
          st[0]=48;
          st[1]=divider;
          for (i=0; i<dec; i++)
            st[2+i]=48;
          st[2+dec]=0;
        }
    }
  else
    {
      if (num<0)
        {
          neg=1;
          num=-num;
        }

      mult = 1;
      for (j = 0; j < dec; j++)
        mult = mult * 10;
      inum=(long)(num*mult + 0.5);

      while (inum>0)
        {
          buf[c]=48+(inum % 10);
          c++;
          inum=(inum-(inum % 10))/10;
        }
      if ((num<1) && (num>0))
        {
          buf[c]=48;
          c++;
        }
      while (c<(dec+1))
        {
          buf[c]=48;
          c++;
        }
      buf[c]=0;

      if (neg)
        {
          st[0]=45;
        }

      if (length>(c+neg-1))
        {
          for (i=0; i<(length-c-neg-1); i++)
            {
              st[i+neg]=filler;
              f++;
            }
        }

      c2=neg;
      for (i=0; i<c; i++)
        {
          st[c2+f]=buf[c-i-1];
          c2++;
          if ((c-(c2-neg))==dec)
            {
              st[c2+f]=divider;
              c2++;
            }
        }
      st[c2+f]=0;
    }

  print(st,x,y,0);
}

void drawBitmap(int x, int y, int sx, int sy, unsigned int* data, int deg, int rox, int roy)
{
  unsigned int col;
  int tx, ty, newx, newy;
  double radian;
  radian=deg*0.0175;

  if (deg==0)
    drawBitmapP(x, y, sx, sy, data,0);
  else
    {
      for (ty=0; ty<sy; ty++)
        for (tx=0; tx<sx; tx++)
          {
            col=*(&data[(ty*sx)+tx]);

            newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
            newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));

            set_xy(newx, newy, newx, newy);
            set_pixel((col<<8)|col);
          }
    }
  clrXY();
}

void drawBitmapP(int x, int y, int sx, int sy, unsigned int* data, int scale)
{
  unsigned int col;
  int tx, ty, tc, tsx, tsy;

  if (scale==1)
    {
      if (lcd_orientation==PORTRAIT)
        {
          set_xy(x, y, x+sx-1, y+sy-1);
          for (tc=0; tc<(sx*sy); tc++)
            {
              col=*(&data[tc]);
              set_pixel((col>>8)|col);
            }
        }
      else
        {
          for (ty=0; ty<sy; ty++)
            {
              set_xy(x, y+ty, x+sx-1, y+ty);
              for (tx=sx; tx>=0; tx--)
                {
                  col=*(&data[(ty*sx)+tx]);
                  set_pixel((col>>8)|col);
                }
            }

        }
    }
  else
    {
      if (lcd_orientation==PORTRAIT)
        {
          for (ty=0; ty<sy; ty++)
            {
              set_xy(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
              for (tsy=0; tsy<scale; tsy++)
                for (tx=0; tx<sx; tx++)
                  {
                    col=*(&data[(ty*sx)+tx]);
                    for (tsx=0; tsx<scale; tsx++)
                      set_pixel((col>>8)|col);
                  }
            }
        }
      else
        {
          for (ty=0; ty<sy; ty++)
            {
              for (tsy=0; tsy<scale; tsy++)
                {
                  set_xy(x, y+(ty*scale)+tsy, x+((sx*scale)-1), y+(ty*scale)+tsy);
                  for (tx=sx; tx>=0; tx--)
                    {
                      col=*(&data[(ty*sx)+tx]);
                      set_pixel((col>>8)|col);
                    }
                }
            }
	}
      clrXY();
    }
}
