#include "MKL25Z4.h"
#include "Uart.h"
#include "Adc.h"
#include "Pit.h"


uint16_t valoare=0;
void PIT_IRQHandler(void)
{	

	PIT_TFLG1 = 0x01; 
	UART0_Transmit16bit(valoare);
	valoare=0;
}

int main(void)
{
	uartInit();
	init_ADC();
	initPIT();

  for (;;)
	{
		valoare = ADC_Read(8);
	}	

	return 0;

}  