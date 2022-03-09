
  ******************************************************************************
  * Ten Tep      :        ds18b20.c
  * Tac Gia      :        Mai Van Cong
  * Cong Ty      :        Dientu686
  * Website      :        dientu686.com
  * Phien Ban    :        V1.0.0
  * Ngay         :        09-05-2013
  * Tom Tat      :        Dinh nghia ham do do am HS1101, khai bao bang tra.
  *       
sbit DQ  = P1^0;
 //******************************************************************************//
void delay_18B20(unsigned int i)
{
	while(i--);
}
//******************************************************************************//
void Init_DS18B20(void) 
{
	 unsigned char x=0;
	 DQ = 1;          
	 delay_18B20(8);  	   
	 DQ = 0;          
	 delay_18B20(80); 
	 DQ = 1;          
	 delay_18B20(14);
	 x=DQ;            
	 delay_18B20(20);
}
//******************************************************************************//
unsigned char ReadOneChar(void)
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	 {
		  DQ = 0; 
		  dat>>=1;
		  DQ = 1; 
		  if(DQ)
		  dat|=0x80;
		  delay_18B20(4);
	 }
 	return(dat);
}
//******************************************************************************//
void WriteOneChar(unsigned char dat)
{
 	unsigned char i=0;
 	for (i=8; i>0; i--)
 	{
  		DQ = 0;
 		DQ = dat&0x01;
    	delay_18B20(5);
 		DQ = 1;
    	dat>>=1;
 }
}
//******************************************************************************//
int ReadTemp(void)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned char t=0;
	int nhiet_thuc;

	Init_DS18B20();
	WriteOneChar(0xCC);    		 // cho phep dieu khien truy nhap truc tiep den lenh nho sensor ma khong can gui chuoi ma sensor
	WriteOneChar(0x44); 		 // khoi dong qua trinh do va chuyen doi du lieu

	delay_18B20(100);    

	Init_DS18B20();
	WriteOneChar(0xCC); 
	WriteOneChar(0xBE); 	    // Cho phep thiet bi doc nd bo nho nhap

	delay_18B20(100);

	a=ReadOneChar();    
	b=ReadOneChar();   	
	nhiet_thuc=b<<4;
	nhiet_thuc+=(a&0xf0)>>4;    
	return(nhiet_thuc);       
}
