#include<lpc21xx.h>

void delay_sec(unsigned int);
void delay_ms(unsigned int);
void lcd_data(unsigned char);
void lcd_cmd( unsigned char);
void lcd_init(void);
void lcd_str(char *);
void lcd_cgram(void);
void lcd_int(int );
void lcd_float(float);

//uart
void uart0_hex(unsigned int);
void uart0_int(unsigned int );
void uart0_init(unsigned int);
void uart0_tx(unsigned char );
void uart0_tx_string(char *);
unsigned char uart0_rx(void);
void rfid_read(char *);


//adc
short int adc_read(unsigned char );
void adc_init(void);
void uart0_tx_integer(int );

void uart0_tx_float(float );

//can
typedef struct CAN1_MSG
{
   unsigned int id;
   unsigned char rtr;
   unsigned char dlc;
   unsigned int byteA;
   unsigned int byteB;

}CAN1 ;


void can1_init(void);
void can1_tx(CAN1 v);
void can1_rx(CAN1 *ptr);

//EXTERNAL_INTERRUPT
void configVicExt0(void);
void configVicExt1(void);
void configVicExt2(void);
void  enableExtIntr2(void);
void  enableExtIntr1(void);
void  enableExtIntr0(void);



