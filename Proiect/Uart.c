#include "Uart.h"

void UART0_Transmit(uint8_t data)
{
	
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
				UART0->D = data;
	
}

void UART0_Transmit16bit(uint16_t data)
{
	
	
	uint8_t f8=((uint16_t)data & 0xff);
	uint8_t l8=((uint16_t)data  >> 8 & 0xff);	
	
	UART0_Transmit(f8);
	UART0_Transmit(l8);
	
}

void uartInit(){	
	//Activam ceasul pentru modulul UART0
  SIM->SCGC4 |= 0x0400;   /* enable clock for UART0 */
    SIM->SOPT2 |= 0x04000000;    /* use FLL output for UART Baud rate generator */
    UART0->C2 = 0;          /* turn off UART0 while changing configurations */
    UART0->BDH = 0x00;
    UART0->BDL = 0x17;      /* 57600 Baud */
    UART0->C4 = 0x0F;       /* Over Sampling Ratio 16 */
    UART0->C1 = 0x00;       /* 8-bit data */
    UART0->C2 = 0x08;       /* enable transmit */

    SIM->SCGC5 |= 0x0200;   /* enable clock for PORTA */
    PORTA->PCR[2] = 0x0200; /* make PTA2 UART0_Tx pin */
}
