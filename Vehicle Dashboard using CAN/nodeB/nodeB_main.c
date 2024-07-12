#include <LPC21xx.H>
#include "header.h"
#include<stdio.h>
#define all (3<<17);
#define li (1<<17);
#define ri (1<<18);
#define he (1<<19);

 ////**** FOR STORING THE VALUE TO PRINT ON THE TERMINAL   ****////
 char speed[20];
 char temp[20];


int byteA=0,byteB=0,id;

CAN1 frame;

 ////**** START MAIN()  ****////
int main()
{
	IODIR0=all;
	IOSET0=all;
 	can1_init();
	uart0_init(9600);
	lcd_init();

	lcd_cmd(0x01);
	lcd_cmd(0x80);
	
	delay_sec(1);

	uart0_tx_string("node B working ....\r\n");	////**** FOR DEBUGGING PURPOSE ****////
	 
	while(1)
	{	 //lcd_str("S");
	 	 can1_rx(&frame);
		 delay_sec(1);
	  	 lcd_cmd(0x01);
		 
		if(frame.rtr==0)////**** IF DATA FRAME  ****////
		{		
//	lcd_string("df");
					uart0_tx_string("node B:data frame\r\n");
					byteA=frame.byteA;		
					byteB=frame.byteB;
					

						////**** LEFT INDICATOR MONITORING  ****////
					if(frame.id==0x200)
					{
								
						if(byteA==0x1A)
						{
							uart0_tx_string("left indicator on\r\n");	
							lcd_cmd(0xc0);
							lcd_data('<');
	                        IOSET0=all;    
	                        IOCLR0=li;
	                        
						
						}
						else if(byteA==0x1B)
						{
								uart0_tx_string("left indicator off\r\n");
								IOSET0=all;
								lcd_cmd(0x01);
								
						}
					 }
						
							////**** RIGHT INDICATOR MONITORING  ****////
					if(frame.id==0x201)
					{
							if(byteA==0x1A)
							{
									uart0_tx_string("right indicator on\r\n");
									
								lcd_cmd(0xc3);
								lcd_data('>');
		                        IOSET0=all;    
		                        IOCLR0=ri;
							}
							else if(byteA==0x1B)
							{
									
									uart0_tx_string("right indicator off\r\n");
									IOSET0=all;
									lcd_cmd(0x01);
							}
					  }

						////**** HEADLIGHT INDICATOR MONITORING  ****////

					if(frame.id==0x202)
					{

							if(byteA==0x1A)
							{
									
									uart0_tx_string("headlight on\r\n");
								lcd_cmd(0xce);
								lcd_data('*');
		                        IOSET0=all;    
		                        IOCLR0=he;
							}
							else if(byteA==0x1B)
							{
									
									uart0_tx_string("headlight off\r\n");
									IOSET0=all;
									lcd_cmd(0x01);
							}
					}


				

		}
		  
		else  ////**** IF REMOTE FRAME  ****////
		{
		   uart0_tx_string("node B:Remote frame\r\n");
		   lcd_str("rf");
		   }

			////**** SPEED VALUE ****////				
					sprintf(speed,"%d",(int)((frame.byteB>>8)&0xfff));	
					uart0_tx_string("speed--> ");
					uart0_tx_string(speed);
					uart0_tx_string("kmph\r\n");
					
					lcd_cmd(0x80);
					lcd_str(speed);
					lcd_str("kmph");

					////**** TEMPARATURE  ****////
					sprintf(temp,"%d",(frame.byteB&0xff));	
					uart0_tx_string("temp--> ");
					uart0_tx_string(temp);
					uart0_tx_string("deg.\r\n");

					lcd_cmd(0x89);
					lcd_str(temp);
					lcd_str("^C");

	} 
	
}	  

