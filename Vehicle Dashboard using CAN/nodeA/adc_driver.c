#include<lpc21xx.h>
#include "header.h"
#define DONE ((ADDR>>31)&1)
void adc_init()
{
	PINSEL1|=0x04000000;//pinsel settings (p0.29 -Ain2)
	ADCR=0x00200400; //adcc setting using adcr
 }

short int adc_read(unsigned char ch_num)
{
	short int result=0;
	ADCR|=(1<<ch_num);
	ADCR|=(1<<24); //start adc
	while(DONE==0);
	ADCR^=(1<<24);//stop adc
	ADCR^=(1<<ch_num); //diselect ch_num;
	result=(ADDR>>6) &(0x3ff);
	return result;

}			


