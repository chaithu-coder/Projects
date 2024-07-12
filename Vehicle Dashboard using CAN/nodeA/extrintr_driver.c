#include<lpc21xx.h>
extern int c1,c2,c3,left,right,head; 
void EINT1_Handler(void)__irq
{
	c1++;
	left=1;
	EXTINT=(1<<1);
	VICVectAddr=0;
}
void EINT2_Handler(void)__irq
{
	c2++;
	right=1;

	EXTINT=(1<<2);
	VICVectAddr=0;
}
void EINT3_Handler(void)__irq
{
	c3++;

	head=1;
	EXTINT=(1<<0);
	VICVectAddr=0;
}

void config_vic_ent0(void)
{
	VICIntSelect=0;
	VICVectAddr0=(unsigned int)EINT1_Handler;
	VICVectAddr1=(unsigned int)EINT2_Handler;
	VICVectAddr2=(unsigned int)EINT3_Handler;
	VICVectCntl0=15|(1<<5);
	VICVectCntl1=16|(1<<5);
	VICVectCntl2=14|(1<<5);
	VICIntEnable|=(7<<14);
}

void config_ent0(void)
{
	PINSEL1|=0x1;
	PINSEL0|=0xA0000000;
	EXTPOLAR=0;
	EXTMODE=0x7;
}
