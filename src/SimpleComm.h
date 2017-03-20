#ifndef __SimpleComm_H__
#define __SimpleComm_H__

#include <Arduino.h>

#include "SimplePacket.h"

class SimpleComm {
	public:
		explicit SimpleComm(Stream &stream);

	public:
		void begin(uint8_t address);

		bool send(SimplePacket &packet);
		bool send(SimplePacket &packet, uint8_t destination);
		bool send(SimplePacket &packet, uint8_t destination, uint8_t type);
		bool receive(SimplePacket &packet);

	private:
		uint8_t calcCRC(uint8_t *buffer, size_t len);

	private:
		Stream &_stream;
		uint8_t _address;
};

#endif // __SimplePacket_H__
