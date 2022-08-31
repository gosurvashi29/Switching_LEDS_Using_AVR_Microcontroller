//glow led by pressing switch once and off the led by pressing it twice
# define F_CPU 1000000
#include <avr/io.h>
# include <util/delay.h>
void lcd_init();
void disp_cmd(unsigned int cmd);
void disp_data(int cmd);
void disp_num(unsigned int num);
void disp_string(  char *str);
int main(void)
{
	DDRA=0X00;
	DDRB=0XFF;
	PORTA=0XFF;
	DDRC = 0XFF;

	lcd_init();
	
	int i1=0;
	int i2=0;
	int i3=0;
	int i4=0;
	int i5=0;
	int i6=0;
	int i7=0;
	int i8=0;
	while (1)
	{
		if ((PINA==0b11111110) && (i1==0))
		{
			while (PINA==0XFE);
			
			
			PORTB=(PORTB+0X01);//1
			disp_cmd(0X80);
			disp_num(1);
			i1=1;
		}
		
		 if ((PINA==0b11111101)  && (i2==0))
		{
			while (PINA==0XFD);
			PORTB=(PORTB+0X02);//2
			disp_cmd(0X81);
			disp_num(2);
			i2=1;
		}
		 if ((PINA==0b11111011)  && (i3==0))
		{
			while (PINA==0XFB);
			PORTB=(PORTB+0X04);//3
			disp_cmd(0X82);
			disp_num(3);
			i3=1;
		}
		 if ((PINA==0b11110111) && (i4==0))
		{
			while (PINA==0XF7);
			PORTB=(PORTB+0X08);//4
			disp_cmd(0X83);
			disp_num(4);
			i4=1;
		}
		 if ((PINA==0b11101111) && (i5==0))
		{
			while (PINA==0XEF);
			PORTB=(PORTB+0X10);//5
			disp_cmd(0X84);
			disp_num(5);
			i5=1;
		}
		 if ((PINA==0b11011111)  && (i6==0))
		{
			while (PINA==0XDF);
			PORTB=(PORTB+0X20);//6
			disp_cmd(0X85);
			disp_num(6);
			i6=1;
		}
		 if ((PINA==0b10111111)  && (i7==0))
		{
			while (PINA==0XBF);
			PORTB=(PORTB+0X40);//7
			disp_cmd(0X86);
			disp_num(7);
			i7=1;
		}			
		 if ((PINA==0b01111111)  && (i8==0))
		{
			while (PINA==0X7F);
			PORTB=(PORTB+0X80);//8
			disp_cmd(0X87);
			disp_num(8);
			i8=1;
		}
		 if ((PINA==0XFE)  && (i1==1))
		 {
			 while (PINA==0XFE);
			 PORTB=(PORTB-0X01);//1
			 disp_cmd(0X80);
			 disp_data(' ');
			 i1=0;
		 }

		 if ((PINA==0XFD) && (i2==1))
		{
			while (PINA==0XFD);
			PORTB=(PORTB-0X02);//2
			disp_cmd(0X81);
			disp_data(' ');
			i2=0;
		}
		 if ((PINA==0XFB) && (i3==1))
		{
			while (PINA==0XFB);
			PORTB=(PORTB-0X04);//3
			disp_cmd(0X82);
			disp_data(' ');
		i3=0;
		}
		if ((PINA==0XF7) && (i4==1))
		{
			while (PINA==0XF7);
			PORTB=(PORTB-0X08);//4
			disp_cmd(0X83);
			disp_data(' ');
		i4=0;
		}
		 if ((PINA==0XEF) && (i5==1))
		{
			while (PINA==0XEF);
			PORTB=(PORTB-0X10);//5
			disp_cmd(0X84);
			disp_data(' ');
			i5=0;
		}
		 if ((PINA==0XDF) && (i6==1)) 
		{
			while (PINA==0XDF);
			PORTB=(PORTB-0X20);//6
			disp_cmd(0X85);
			disp_data(' ');
			i6=0;
		}
		 if ((PINA==0XBF) && (i7==1))
		{
			while (PINA==0XBF);
			PORTB=(PORTB-0X40);//7
			disp_cmd(0X86);
			disp_data(' ');
			i7=0;
		}
		
		 if ((PINA==0X7F) &&(i8==1))
		{
			while (PINA==0X7F);
			PORTB=(PORTB-0X80);//8
			disp_cmd(0X87);
			disp_data(' ');
			i8=0;
		}
		
	}
	
	return 0;
}

void disp_cmd(unsigned int cmd)
{
	PORTC=((cmd & 0XF0)+0X04);
	_delay_ms(1);
	PORTC=PORTC - 0X04;
	PORTC=(((cmd<<4)& 0XF0)+0X04);
	_delay_ms(1);
	PORTC=PORTC-0X04;
	
}
void disp_data( int cmd)
{
	PORTC=((cmd  & 0XF0)+0X05);
	_delay_ms(1);
	PORTC=PORTC - 0X04;
	PORTC=(((cmd <<4)& 0XF0)+0X05);
	_delay_ms(1);
	PORTC=PORTC-0X04;
	
}

void disp_string( char *str)
{
	int i=0;
	while (str[i]!='\0')
	{
		disp_data (str[i]);
		i++;
		
	}
}

void disp_num(unsigned int num)
{
	int a=0;
	if (num==0)
	{
		disp_data(48);
	}
	disp_cmd (0X04);
	while (num!=0)
	{
		a=num % 10;
		disp_data(a+48);
		num=num/10;
	}
	disp_cmd (0X06);
}
void lcd_init()
{
	disp_cmd(0X02);
	disp_cmd(0X28);
	disp_cmd(0X0C);
	disp_cmd(0X06);
}