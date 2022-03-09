#include <REGX52.H>
#include <lcd.h>
#include <stdio.h>
#include "hs1101/hs1101.c"
#include "ds18b20.c"
#define xoa_man_hinh          	0x01
#define tat_con_tro          	0x0c
#define ve_dau_dong_thu_nhat   	0x80
sbit relay = 	P3^7;
sbit sw1   =	P0^0;
sbit sw2   =	P0^1;
         
int xung,dem,frequency;
void delay_ms(unsigned int i)
{
unsigned int j,k;
for(j=0;j<i;j++)
   for(k=0;k<120;k++);
}
void ngat0(void) interrupt 0
{
xung++;
}
void ngat_timer_0(void) interrupt 1
{
dem++;
if(dem >= 4000)
	{
	dem=0;
	frequency = xung-2600;
	xung=0;
	}

}

void main(void)
{ 
 int humi,nhiet_do,nhiet_do2,nhiet_do3,nhiet_do_khong_che=40;
char str[20];
TMOD = 0x02;
TH0=TL0=-250;
IT0=1;
IE=0x83;
TR0=1;
lcd_init();
lcd_com(xoa_man_hinh);
while(1)
	{
	if(sw1 == 0)	{nhiet_do_khong_che++; if(nhiet_do_khong_che>=150) nhiet_do_khong_che=0; }
	if(sw2 == 0)	{nhiet_do_khong_che--; if(nhiet_do_khong_che<=0) nhiet_do_khong_che=150; }
	 nhiet_do  = ReadTemp();
	 nhiet_do2 = ReadTemp();
	 nhiet_do3 = ReadTemp();
	 if((nhiet_do2 >= nhiet_do-4)&&(nhiet_do2 <= nhiet_do+4)&&(nhiet_do3 >= nhiet_do2-4)&&(nhiet_do3 <= nhiet_do2+4))
	  	{			 
		if(nhiet_do2 > nhiet_do_khong_che)	relay =1; else relay=0;
		humi=HS1101_GetHumi(frequency);
	    sprintf(str,"Do Am:   %d %%   ",humi);
	    lcd_gotoxy(1,0);
	    lcd_puts(str);
		sprintf(str,"T=%doC  Tkc=%doC   ",nhiet_do,nhiet_do_khong_che);
		lcd_gotoxy(2,0);
		lcd_puts(str);
		}
	 delay_ms(100);	
	}
}
