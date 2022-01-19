#include "Adc.h"

void init_ADC(void)
{
     
    // Enable ADC0 Clock
    SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
     

    // Configure ADC
    ADC0_SC1A |= (ADC_SC1_AIEN_MASK);  // Interrupt enabled
    ADC0_SC1A &= ~ADC_SC1_DIFF_MASK;   // Single Ended ADC
     
    ADC0_CFG1 = 0; // Reset register
    ADC0_CFG1 |= (ADC_CFG1_MODE(2)  |   // 10 bits mode
                        ADC_CFG1_ADICLK(1)|   // Input Bus Clock/2 (24 Mhz)
                        ADC_CFG1_ADIV(3)  |     // Clock divide by 8 (3 Mhz)
                                ADC_CFG1_ADLPC_MASK); // Low power mode
     
    ADC0_SC3  &= ~ADC_SC3_AVGE_MASK;
}
 
/**************************************************
* @function: adc_read
* @brief:    Read the ADC Module
* @param:    ch - ADC Channel
* @return:   none
***************************************************/
uint16_t ADC_Read(uint8_t ch)
{
    // Write to SC1A to start conversion
    ADC0_SC1A = ((ch & ADC_SC1_ADCH_MASK) | 
                       (ADC0_SC1A & 
                 (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK))); //interrupt enable | single-end mode seted
     
    while(ADC0_SC2 & ADC_SC2_ADACT_MASK);    // Conversion in progress
    while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // Run until the conversion is complete
     
    return ADC0_RA;
}
