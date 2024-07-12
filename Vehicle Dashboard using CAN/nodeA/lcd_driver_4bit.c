#include <lpc21xx.h>

#include "header.h"

#define RS (1 << 17)

#define RW (1 << 18)

#define EN (1 << 19)

#define gpio 0xFE0000

void lcd_data(unsigned char data)

{

	unsigned int temp;

	IOCLR1 = gpio;

	temp = data << 16;

	IOSET1 = temp;

	IOSET1 = RS;

	IOCLR1 = RW;

	IOSET1 = EN;

	delay_ms(2);

	IOCLR1 = EN;

	IOCLR1 = gpio;

	// temp=((data&0XF)<<20);

	IOSET1 = temp << 4;

	IOSET1 = RS;

	IOCLR1 = RW;

	IOSET1 = EN;

	delay_ms(2);

	IOCLR1 = EN;
}

void lcd_cmd(unsigned char cmd)

{

	unsigned int temp;

	IOCLR1 = gpio;

	temp = ((cmd) << 16);

	IOSET1 = temp;

	IOCLR1 = RS;

	IOCLR1 = RW;

	IOSET1 = EN;

	delay_ms(2);

	IOCLR1 = EN;

	IOCLR1 = gpio;

	// temp=((cmd&0XF)<<20);

	IOSET1 = temp << 4;

	IOCLR1 = RS;

	IOCLR1 = RW;

	IOSET1 = EN;

	delay_ms(2);

	IOCLR1 = EN;
}

void lcd_init()

{

	IODIR1 = gpio;

	PINSEL2 = 0;

	lcd_cmd(0x02);

	lcd_cmd(0x28);

	lcd_cmd(0x0e);

	lcd_cmd(0x01);

	// IOCLR1=EN;
}

void lcd_str(char *p)

{

	while (*p != 0)

		lcd_data(*p++);
}

void lcd_int(int n)

{

	int i = 0, r;

	char s[20];

	if (n < 0)

	{

		lcd_data('-');

		n = -n;
	}

	while (n != 0)

	{

		r = n % 10;

		s[i] = r + 48;

		i++;

		n = n / 10;
	}

	for (i = i - 1; i >= 0; i--)

		lcd_data(s[i]);
}

void lcd_float(float f)

{

	int m;

	if (f < 0)

	{

		lcd_data('-');

		f = -f;
	}

	m = f;

	lcd_int(m);

	lcd_data('.');

	m = (f - m) * 1000;

	lcd_int(m);
}

unsigned char a[8] = {0x00, 0x02, 0x04, 0x08, 0x04, 0x02, 0x00};
void leftcgram(void)
{
	int i;
	lcd_cmd(0x40);
	for (i = 0; i < 8; i++)
	{
		lcd_data(a[i]);
	}
}

unsigned char b[8] = {0x00, 0x08, 0x04, 0x02, 0x04, 0x08, 0x00};
void rightcgram(void)
{
	int i;
	lcd_cmd(0x48);
	for (i = 7; i >= 0; i--)
	{
		lcd_data(b[i]);
	}
}

unsigned char c[8] = {0x04, 0x15, 0x0E, 0x04, 0x04, 0x0E, 0x15, 0x04};
void headcgram(void)
{
	int i;
	lcd_cmd(0x50);
	for (i = 7; i >= 0; i--)
	{
		lcd_data(c[i]);
	}
}

unsigned char d[8] = {0};
void clearcgram(void)
{
	int i;
	lcd_cmd(0x58);
	for (i = 7; i >= 0; i--)
	{
		lcd_data(d[i]);
	}
}
