#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

#include <stdint.h>


float Convert_CtoF(uint16_t Temp_in_C);
uint16_t Calculate_Temp_inC(uint16_t ADC_Value);

#endif