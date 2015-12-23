#define LCD_A0 (0x1<<18)
#define LCD_WR (0x1<<16)
#define LCD_CS (0x1<<24)
#define LCD_RD (0x1<<17)
#define LCD_RES (0x1<<19)
#define LCD_DATA ((0x3<<25)|(0x3F<<2))

#define H_LCD_A0 (IOSET = LCD_A0)
#define L_LCD_A0 (IOCLR = LCD_A0)
#define H_LCD_WR (IOSET = LCD_WR)
#define L_LCD_WR (IOCLR = LCD_WR)
#define H_LCD_CS (IOSET = LCD_CS)
#define L_LCD_CS (IOCLR = LCD_CS)
#define H_LCD_RD (IOSET = LCD_RD)
#define L_LCD_RD (IOCLR = LCD_RD)
#define H_LCD_RES (IOSET = LCD_RES)
#define L_LCD_RES (IOCLR = LCD_RES)
#


void LCD_Init(void)				;
void Lcd_WriteCMD(unsigned char cmd)	;

void LCD_WriteData(unsigned char data)	 ;

unsigned char  LCD_ReadData(void)  ;

void LCD_SetCursor(unsigned char  x,unsigned char  y);

void LCD_Reset(void) ;	
