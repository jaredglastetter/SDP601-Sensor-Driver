#include "SDP601.h"
#include <stdio.h>
#include <iostream>

#define SDP601_ADDR1 0x41
#define SDP601_ADDR2 0x42
#define SDP601_ADDR3 0x43
#define SDP601_ADDR4 0x44
//#define SDP601_ADDR 0x44

int initSensors();

SDP601 pressureSensor1(SDP601_ADDR1);
SDP601 pressureSensor2(SDP601_ADDR2);
SDP601 pressureSensor3(SDP601_ADDR3);
SDP601 pressureSensor4(SDP601_ADDR4);

int main()
{
	printf("*****  Testing SDP601 Pressure sensor *****\n");
	int result; // maybe int *
	
	if( !initSensors())
		return 0;

	
	int results[4];
	while(1)
	{

		// sensor 1
		//printf("sensor 1 \n ---------------- \n");
		pressureSensor1.WriteCommand();
		pressureSensor1.MeasurePressure(results[0]);
		//printf("sensor reading: %f \n", result / 60.0);
		pressureSensor1.CheckCRC();

		// sensor 2
		//printf("sensor 2 \n ---------------- \n");
		pressureSensor2.WriteCommand();
		pressureSensor2.MeasurePressure(results[1]);
		//printf("sensor reading: %f \n", result / 60.0);
		pressureSensor2.CheckCRC();

		// sensor 3
		//printf("sensor 3 \n ---------------- \n");
		pressureSensor3.WriteCommand();
		pressureSensor3.MeasurePressure(results[2]);
		//printf("sensor reading: %f \n", result / 60.0);
		pressureSensor3.CheckCRC();

		// sensor 4
		//printf("sensor 4 \n ---------------- \n");
		pressureSensor4.WriteCommand();
		pressureSensor4.MeasurePressure(results[3]);
		//printf("sensor reading: %f \n", result / 60.0);
		//printf("---------------- \n");
		pressureSensor4.CheckCRC();

		std::cout << results[0]  / 60.0<< ", " << results[1] / 60.0 << ", "  << results[2]  / 60.0<< ", "  <<results[3] / 60.0<< std::endl;



		// pressureSensor.MeasurePressure(result);
		// printf("sensor reading: %f \n", result / 60.0);
		// pressureSensor.CheckCRC();

		usleep(5000);


	}

	return 0;
}

int initSensors()
{
	// sensor 1
	if ( !pressureSensor1.init()  )
		return 0;

	if(!pressureSensor1.Connect())
		return 0;

	//sensor 2
	if ( !pressureSensor2.init()  )
		return 0;

	if(!pressureSensor2.Connect())
		return 0;

	//sensor 3
	if ( !pressureSensor3.init()  )
		return 0;

	if(!pressureSensor3.Connect())
		return 0;

	//sensor 4
	if ( !pressureSensor4.init()  )
		return 0;

	if(!pressureSensor4.Connect())
		return 0;

	return 1;

}