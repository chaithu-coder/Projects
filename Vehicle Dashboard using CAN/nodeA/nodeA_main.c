#include "header.h"
#include <LPC21xx.H>

#define LEFT_INDICATOR ((IOPIN0 >> 14) & 1)
#define RIGHT_INDICATOR ((IOPIN0>>15)&1)
#define HEADLIGHT ((IOPIN0 >> 16) & 1)

unsigned char s[20];
unsigned char s1[20];

float vout, tempr;
CAN1 frame; // create struct var

/*FLAGS FOR CONTROL*/
int left = 0, right = 0, head = 0,c1,c2,c3;

unsigned int num, num1, speed, temp,temp1; // normal variables

int main()
{
	int adcval = 0;
	adc_init();
	can1_init();
	uart0_init(9600);

	config_vic_ent0();
	 config_ent0();

	while (1)
	{
	
		//frame.id = 0x1FF;
		frame.rtr = 0;
		frame.dlc = 8;
		/* LEFT INDICATOR MONITORING */
		if(left)
		{
				left=0;
	
			if (c1==1)
			{
				
				num = 0x1A;
				 frame.id = 0x200;
				uart0_tx_string("left id on\r\n");
			}
			else if(c1==2)
			{
				
				num = 0x1B;
				frame.id = 0x200;
					uart0_tx_string("left id off\r\n");
				c1=0;	
			}
		}
		
		/* RIGHT INDICATOR MONITORING */
		if(right)
		{
			right=0;
			
			if (c2==1)
			{
				num = 0x1A;
				frame.id = 0x201;
				uart0_tx_string("right id on\r\n");
				
			}
			else if(c2==2)
			{
				num = 0x1B;
				frame.id = 0x201;
				c2=0;
				uart0_tx_string("right id off\r\n");
				
			}
		 }

		/* HEAD LIGHT MONITORING */
		 if(head)
		 {
			 	head=0;
			if (c3==1)
			{
			frame.id = 0x202;
			uart0_tx_string("head id on\r\n");
				num = 0x1A;
				
			}
			else if(c3==2)
			{
				c3=0;
				frame.id = 0x202;
				num = 0x1B;
				uart0_tx_string("head id off\r\n");
				
			}
		 }

		// STORED INTO A BYTEA
		frame.byteA = num;

		/* TEMPERATURE READING */
		adcval = adc_read(1);
		vout = (adcval * 3.3f) / 1023.0f;
		tempr = (vout - 0.5f) / 0.01f;

		num1 = ((int)tempr) % 100;
		num1 = ((num1 / 10) << 4) | (num1 % 10); // CONVERTED TO HEX

		/* POTENTIOAMETER READING */
		temp = adc_read(2);
		temp1=uart0_speed(temp);
		speed=temp1;
		speed = ((speed / 100) << 8) | (((speed % 100) / 10) << 4) | (speed % 10); // CONVERTED TO HEX

		////**** PRINTING ON TERMINAL READING ****////
		uart0_tx_string("TEMPARATURE VALUE :");
		uart0_tx_float(tempr);
		uart0_tx_string("\r\n");

		uart0_tx_string("SPEED IN KMPH :");
		
		uart0_tx_integer(temp1);
		uart0_tx_string("\r\n");

		num1 = (speed << 8) | num1;
		frame.byteB = num1;
		/* DATA FRAME SENDING.....*/
		can1_tx(frame);
		delay_ms(500); // DATA FRAME SENDING....FOR EVREY 500ms
	}
}
