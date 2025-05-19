#include <stdio.h>
#include "platinum_rtd_sensor.h"

char str[20];
double resistance, temperature;


void main(void)
{	
	// Calculate temperature (°C) from PT100 resistance (268.5 Ω) with initial guess 25°C
	temperature = RTD_CalculateTemperature(RTD_SENSOR_PT100, 268.5, 25); 
	
	sprintf(str, "Temperature is %0.2f", temperature);
	puts(str);
	
	// Calculate PT500 resistance (Ω) from temperature (438 °C)
	resistance = RTD_CalculateResistance(RTD_SENSOR_PT500, 438);
	
	sprintf(str, "Resistance is %0.2f", resistance);
	puts(str);
}
