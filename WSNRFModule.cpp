#include <WSNRFModule.h>

RFModule::RFModule(): _addnode(ADDNODE), _addserver(ADDSERVER)
{};

RFModule::RFModule(uint8_t add, uint8_t addrServer): _addnode(add), _addserver(addrServer)
{};

void RFModule::initRF()
{
	radio = new SX1276();
	// Serial.println("SX1276 module and Arduino: send packets without ACK");
	radio->ON(); 
	radio->setMode(MODE);
	//Serial.println(e, DEC);
	radio->setChannel(CHANNEL);
	//Serial.println("Setting Channel: state ");
	//Serial.println(e, DEC);
	radio->setMaxCurrent(MAXCURRENT);
	//radio->getMaxCurrent();
	// Select output power (Max, High or Low)
	/* H=13dBm M=17dBm  measured at the antenna connector*/
	radio->setPower(POWER);
	//Serial.println("Setting Power: state ");
	//Serial.println(e);
	radio->setNodeAddress(_addnode);
	paquet = "";
	//Serial.println(e, DEC);
	// Print a success message
	Serial.print("radio module successfully configured ");
};

bool RFModule::checkPacket()
{
	 int e = radio->receivePacketTimeout(1000);
   String p = radio->getPacketRecu();
   if(e == 0 && p.length()>0){ 
     //sendDonnees( formatagePaquet());
     //Serial.println("paquet envoye avec succes");
   	return true;
   }else return false;
};

void RFModule::saveData(String sensor)
{
	Process logdata;
	logdata.begin("python");
	logdata.addParameter("/root/datalogger.py");  //
	//logdata.addParameter("vitesse");
	logdata.addParameter(sensor);//
	//Console.println(sensor);
	logdata.run();
};

void RFModule::sendData(String datas)
{
	sendData(datas, _addserver);
};

void RFModule::sendData(String paq, uint8_t idClient)
{
	char buff[paq.length()+1];
	paq.toCharArray(buff, paq.length()+1); 
	radio->sendPacketTimeout(idClient, buff);
};


