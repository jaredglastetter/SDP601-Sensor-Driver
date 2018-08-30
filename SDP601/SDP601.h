#ifndef _SDP601_h
#define _SDP601_h


#include <stdint.h>
#include <unistd.h>

//CRC
#define POLYNOMIAL 0x131

//Pressure Sensor
#define SCALE_FACTOR 60.0
#define SDP601_CMD_LEN 1
#define SDP601_READ_LEN 3
#define SDP601_MEASURE_CMD 0xF1

//Pi
#define FILENAME "/dev/i2c-1"


class SDP601
{
	public:
		SDP601(int);

		int init();
		int Connect();
		void WriteCommand();
		int MeasurePressure(int &result);
		int CheckCRC();

	private:
		int _sensorAddr;

		int _fileI2C;

		char _data[2];
		uint8_t _checksum;

};

#endif
