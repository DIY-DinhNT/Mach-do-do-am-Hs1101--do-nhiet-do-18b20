#define LCDPORT P2
sbit _RS=LCDPORT^0;
sbit _RW=LCDPORT^1;
sbit _E =LCDPORT^2;
bit  ___status=0;
#define lcd_delay 400

void delay(unsigned int j){
unsigned int i=0;
for(;i<j;i++);
}


void _lcd_init_write(unsigned char a){
_RS=0;
_RW=0;
LCDPORT=a;
_E=1;
delay(lcd_delay);
_E=0;
}





void lcd_com(unsigned char a){
unsigned char temp;
if(___status){
	___status=0;
	goto ___next123321;
	}
_RS=0;
___next123321:
_RW=0;
temp=a;
temp&=0xf0;
LCDPORT&=0x0f;
LCDPORT|=temp;
_E=1;
delay(lcd_delay);
_E=0;
temp=a<<4;
temp&=0xf0;
LCDPORT&=0x0f;
LCDPORT|=temp;
_E=1;
delay(lcd_delay);
_E=0;
}

void lcd_data(unsigned char a){
___status=1;
_RS=1;
lcd_com(a);
}



void lcd_init(void){
delay(lcd_delay);
_lcd_init_write(0x30);
delay(lcd_delay);
_lcd_init_write(0x30);
delay(lcd_delay);
_lcd_init_write(0x30);
delay(lcd_delay);
_lcd_init_write(0x20);
delay(lcd_delay);
lcd_com(0x28);
delay(lcd_delay);
lcd_com(4);
delay(lcd_delay);
lcd_com(0x85);
delay(lcd_delay);
lcd_com(6);
delay(lcd_delay);
lcd_com(1);
delay(lcd_delay);
lcd_com(15);
delay(lcd_delay);
}


void lcd_puts(char *aaa){
unsigned int i=0;
for(;aaa[i]!=0;i++)lcd_data(aaa[i]);
}
void lcd_gotoxy(unsigned char row,unsigned char column)
{
	switch(row)
		{
		case 1:
			lcd_com(0x80+column);
			break;

		case 2:
			lcd_com(0x80+0x40+column);
			break;

		default:
			break;
		}
}
void write_num(unsigned int number)
{
char ch,dv;
	ch = number / 10;
	dv = number % 10;

	lcd_data(0x30 + ch);
	lcd_data(0x30 + dv);
}