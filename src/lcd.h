#define LCD_18	18
#define LCD_22	22
#define LCD_22SPI	23
#define LCD_24	24
#define LCD_25	25
#define LCD_28	28

#define swap(i,j)	{int t;t=i;i=j;j=t;}
#define CAL_X 				0x00378F66UL
#define CAL_Y 				0x03C34155UL
#define CAL_S 				0x000EF13FUL

#define RIGHT 			9999
#define CENTER 			9998

extern void setDataBus(int c);

void delayP(int a);
void DspSignalColor(unsigned char h,unsigned char l);
void LCDInit(void);
void SetPinNU(int Rrs, int Rcs, int Rwr, int Rrst);
void SetLCDSize(int a);
//void swap(unsigned int i,unsigned int j);
void WriteCommand(unsigned int c);
void WriteData(unsigned int c);
void WriteCommandData(unsigned int cmd,unsigned int dat);
void SetXY(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1);
void Pant(unsigned int color);
void fillScr(unsigned int color);
void fillScrRGB(int r, int g, int b);
void clrScr();
void LcdOff();
void LcdOn();
void clrXY();
void setColor(long int color);
void setColorRGB(int r, int g, int b);
void setBackColor(int color);
void setBackColorRGB(int r, int g, int b);
void drawRect(int x1, int y1, int x2, int y2);
void drawHLine(int x, int y, int l);
void drawVLine(int x, int y, int l);
void drawLine(int x1, int y1, int x2, int y2);
void drawRoundRect(int x1, int y1, int x2, int y2);
void drawPixel(int x, int y);
void setPixel(int color);
void fillRect(int x1, int y1, int x2, int y2);
void fillRoundRect(int x1, int y1, int x2, int y2);
void drawCircle(int x, int y, int radius);
void fillCircle(int x, int y, int radius);
unsigned short int PgmRead(unsigned short int *p);
void printChar(unsigned char c, int x, int y);
void setFont(unsigned short int mxsize,unsigned short int mysize,unsigned short int moffset);
void rotateChar(unsigned char c, int x, int y, int pos, int deg);
void print(char *st, int x, int y, int deg);
//void print(String st, int x, int y, int deg);
unsigned char* getFont();
unsigned int getFontXsize();
unsigned int getFontYsize();
int getDisplayXSize();
int getDisplayYSize();
void printNumI(long num, int x, int y, int length, char filler);
void printNumF(double num, unsigned char dec, int x, int y, char divider, int length, char filler);
void drawBitmap(int x, int y, int sx, int sy, unsigned int* data, int deg, int rox, int roy);
void drawBitmapP(int x, int y, int sx, int sy, unsigned int* data, int scale);
