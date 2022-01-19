#include "Pit.h"


void initPIT() 
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; //enable clock gate
	
	PIT_MCR = 0x00;
	
	PIT_LDVAL1 = 0X000FA000;  //1024000 timer (40 ms)
														//Load value register = expirarea intreruperilor

	PIT_TCTRL1 = PIT_TCTRL_TIE_MASK; 
	PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK;
	
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn,128);
	NVIC_EnableIRQ(PIT_IRQn);
}