#ifndef __ADC_H
#define __ADC_H

#include "sys.h" 


void AD_Init(void);
uint16_t AD_GetValue(void);
float	Get_battery_volt(void);

#endif
