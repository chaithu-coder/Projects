#include <lpc21xx.h>
#include "header.h"
#define THRE ((U0LSR >> 5) & 1)
void uart0_init(unsigned int baud)
{
	int a[] = {15, 60, 30, 0, 15};
	unsigned int pclk = 0, result = 0;
	pclk = a[VPBDIV] * 1000000;
	result = pclk / (16 * baud);
	PINSEL0 |= 5;
	U0LCR = 0X83;
	U0DLL = result & 0xFF;
	U0DLM = (result >> 8) & 0xFF;
	U0LCR ^= (1 << 7);
}
// transmit function
void uart0_tx(unsigned char data)
{
	U0THR = data;
	while (THRE == 0)
		;
}
// transmit string
void uart0_tx_string(char *ptr)
{
	while (*ptr)
	{
		U0THR = *ptr;
		while (THRE == 0)
			;
		ptr++;
	}
}

// reciver function
#define RDR (U0LSR & 1)

unsigned char uart0_rx(void)
{

	while (RDR == 0)
		;

	return U0RBR;
}

void uart0_int(unsigned int n)
{
	uart0_tx((n / 100) + 48);
	uart0_tx(((n / 10) % 10) + 48);
	uart0_tx((n % 10) + 48);
}

void uart0_rx_string(char *ptr, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		while (RDR == 0)
			;
		ptr[i] = U0RBR;
		if (ptr[i] == '\r')
			break;
		ptr[i] = ('\0');
	}
}

// void uart0_tx_integer(int num)
// {
// 	char buff[20];
//	sprintf(buff,"%d",num);
//	uart0_tx_string(buff);
// }
void uart0_tx_integer(int n)

{

	int i = 0, r;

	char s[20];
	if (n < 0)

	{

		uart0_tx('-');

		n = -n;
	}
	if (n == 0)
		uart0_tx('0');
	else
	{
		while (n != 0)

		{

			r = n % 10;

			s[i] = r + 48;

			i++;

			n = n / 10;
		}

		for (i = i - 1; i >= 0; i--)
			uart0_tx(s[i]);
	}
}

//  void uart0_tx_float(float num)
// {
// 	char buff[20];
//	sprintf(buff,"%f",num);
//	uart0_tx_string(buff);
// }

void uart0_tx_float(float f)

{

	int m;

	if (f < 0)

	{

		uart0_tx('-');

		f = -f;
	}

	m = f;

	uart0_tx_integer(m);

	uart0_tx('.');

	m = (f - m) * 1000;

	uart0_tx_integer(m);
}

int hextodeci(int num)
{
	int deci = 0;
	int i;
	int div = 1, mul = 1;
	for (i = 0; i < 8; i++)
	{
		deci = deci + ((num / div) % 0x10) * mul;
		div = div * 0x10;
		mul = mul * 10;
	}
	return deci;
}

void clearstr( char *s, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		s[i] = 0;
	}
}

unsigned int uart0_speed(unsigned int input)
{
	unsigned int min,max;
	float speed;
	min=0;
	max=1023;//12 bit resolution

	speed=((float)(max-input)/(max-min))*100;
	return speed;
}

