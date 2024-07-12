//recive driver of node B
#include"header.h"

#define RBS (C2GSR &1)
#define TCS ((C1GSR>>3)&1)
void can1_init(void)
{
	PINSEL1|=0x14000;
	VPBDIV=1;//pclk=60MHz
	C2MOD=1;//SELECT RESET MODE
	C2BTR=0x001C001D;//set 125kbps baud rate
	AFMR=2;//accept all incoming msgs
	C2MOD=0;//cancel reset mode
}

void can1_tx(CAN1 v)
{
	C2TID1=v.id;
	C2TFI1=v.dlc<<16;//dlc=8 and rtr=0
	if(v.rtr==0)//if data frame
	{
		C2TDA1=v.byteA;
		C2TDB1=v.byteB;
	}
	else //if remote frame
	{
		C2TFI1|=(1<<30); //rtr=1
	}
	C2CMR=1|(1<<5);//START TRANSMISSION & SELECT tXbuf1
	while(TCS==0);//tcs
}

void can1_rx(CAN1 *ptr)
{
	while(RBS==0);
	ptr->id=C2RID;
	ptr->dlc=(C2RFS>>16)&0xF; //extract dlc
	ptr->rtr=(C2RFS>>30)&0x1;
	
	if(ptr->rtr==0) //if data frame
	{
		ptr->byteA=C2RDA;
		ptr->byteB=C2RDB;
	}
	C2CMR=(1<<2); //Release rxbuf
}
		







		
