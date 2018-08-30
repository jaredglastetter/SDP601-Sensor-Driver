#include "SDP601.h"
#include <stdio.h>
#include <iostream>
#include <time.h>

#define SDP601_ADDR 0x41


SDP601 pressureSensor(SDP601_ADDR);





int main()
{
	//printf("*****  Testing SDP601 Pressure sensor *****\n");
	int result;
	
	if ( !pressureSensor.init()  )
		return 0;

	if(!pressureSensor.Connect())
		return 0;

	while(1)
	{
		
		
		pressureSensor.WriteCommand();
		pressureSensor.MeasurePressure(result);


		std::cout << result / 60.0 << std::endl;
		
		usleep(5000);
		
	}

	return 0;
}

