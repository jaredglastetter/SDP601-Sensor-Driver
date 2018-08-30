#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include <fstream>

#include "SDP601.h"

SDP601::SDP601(int addr)
{
	_sensorAddr = addr;
}

int SDP601::init()
{
	char *filename = (char*)FILENAME;
	int init;

	if( (init = (_fileI2C = open(filename, O_RDWR) )) < 0)
	{
		printf("Error: Failed to open file \" %s \". \n",filename );
		return 0; 
	}
	//printf("init: %d \n", init);
	return 1;
}

int SDP601::Connect()
{
	int connect;
	if ( (connect = ioctl(_fileI2C, I2C_SLAVE, _sensorAddr)) < 0)
	{	
		printf("Error: Failed to connect to slave adress \" 0x%02x \". \n", _sensorAddr);
		return 0;
	}

	//printf("connect: %d \n", connect);
	return 1;
}

void SDP601::WriteCommand()
{
	
	if(write(_fileI2C, (const char[]){(char)SDP601_MEASURE_CMD}, SDP601_CMD_LEN) != SDP601_CMD_LEN) 
	{
			printf("Error: Failed to write command \" 0x%02x \"to sensor 0x%02x .\n", SDP601_MEASURE_CMD, _sensorAddr) ;		
	}
	
}

int SDP601::MeasurePressure(int &result)
{
	char buffer[10] = {0};
	int readBytes;

	int output = 0;
	

	if((readBytes = read(_fileI2C, buffer, SDP601_READ_LEN)) != SDP601_READ_LEN) // read 3 bytes 
	{
			printf("Error: Sensor 0x%02x number of bytes read: %d \n===================\n", _sensorAddr,readBytes);
			return 0;
	}	
	else
	{
		_data[0] = buffer[0];
		_data[1] = buffer[1];
		_checksum = buffer[2];

		output = (buffer[1] | buffer[0] << 8);				// join 2 bytes together

		const int negative = (output & (1 << 15)) != 0;		// get 2s compliment sign

		if(negative)										// convert to decimal from 2s compliment
		{
			result = output | ~((1<<16) - 1);
		}
		else
		{
			result = output;
		}
		
		return CheckCRC();
	}

}

int SDP601::CheckCRC()
{
	uint8_t crc = 0;
	uint8_t byteCtr;

	//calculates 8-Bit checksum with given polynomial
	for (byteCtr = 0; byteCtr < 2; ++byteCtr) { 
		crc ^= (_data[byteCtr]);
		for (uint8_t bit = 8; bit > 0; --bit) { 
			if (crc & 0x80) crc = (crc << 1) ^ POLYNOMIAL;
			else crc = (crc << 1);
		}
	}
	if (crc != _checksum) 
	{
		printf("0x%02x crc failed. \n===========\n", _sensorAddr);
		return 0;
	}
	else
	{
		return 1;
		//printf("crc successful.\n===========\n");
	}

}




