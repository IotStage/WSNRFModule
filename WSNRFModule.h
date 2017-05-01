#ifndef WSNRFModuleSensor_h
#define WSNRFModuleSensor_h

#include <stdlib.h>
#include <stdint.h>
#include <Arduino.h>
#include "SX1276/SX1276.h"
#include <Console.h>

#define ADDSERVER 8
#define ADDNODE 3
#define MODE 1 //mode transmission (1, 2, 4, ... 10)
#define CHANNEL CH_16_868
#define MAXCURRENT 0x1B
#define POWER 'M' // // Select output power (Max, High or Low)
  /* H=13dBm M=17dBm  measured at the antenna connector*/

class RFModule
{
public:
	RFModule();
	RFModule(uint8_t add, uint8_t addrServer);
	//~RFModule();
	void initRF();
	bool checkPacket();
	void saveData(String datas);
	void sendData(String datas);
	void sendData(String datas, uint8_t idClient);
	String paquet;

private:
	const uint8_t _addnode;
	const uint8_t _addserver;
	SX1276 *radio;

	
};


#endif