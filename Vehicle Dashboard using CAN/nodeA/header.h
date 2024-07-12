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


//lcd
void clearcgram(void);
void headcgram(void);
void rightcgram(void);
void leftcgram(void);
//uart
void uart0_hex(unsigned int);
void uart0_int(unsigned int );
void uart0_init(unsigned int);
void uart0_tx(unsigned char );
void uart0_tx_string(char *);
unsigned char uart0_rx(void);
void rfid_read(char *);
int hextodeci(int );
void clearstr( char *, int );
//adc
short int adc_read(unsigned char );
void adc_init(void);
void uart0_tx_integer(int );
unsigned int uart0_speed(unsigned int);
void uart0_tx_float(float );

//can
typedef struct CAN1_MSG
{
   unsigned int id;
   unsigned char rtr;
   unsigned char dlc;
   unsigned int byteA;
   unsigned int byteB;

}CAN1;


void can1_init(void);
void can1_tx(CAN1 v);
void can1_rx(CAN1 *ptr);

////**** EXTERNAL_INTERRUPT HEADER  ****////
void config_vic_ent0(void);
void config_ent0(void);



