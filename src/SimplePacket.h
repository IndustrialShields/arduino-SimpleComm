#ifndef __SimplePacket_H__
#define __SimplePacket_H__

#include <Arduino.h>

class SimplePacket {
	public:
		explicit SimplePacket();
		virtual ~SimplePacket();

	public:
		// Packet functions
		void clear();
		void setSource(uint8_t source);
		void setDestination(uint8_t destination);
		void setType(uint8_t type);

		uint8_t getSource() const;
		uint8_t getDestination() const;
		uint8_t getType() const;

		// Payload (data) functions
		bool set(bool data);
		bool set(char data);
		bool set(unsigned char data);
		bool set(int data);
		bool set(unsigned int data);
		bool set(long data);
		bool set(unsigned long data);
		bool set(double data);
		bool set(const uint8_t *data, uint8_t len);
		bool set(const char *data);
		bool set(const char *data, uint8_t len);
		bool set(const String &data);

		bool getBool() const;
		char getChar() const;
		unsigned char getUChar() const;
		int getInt() const;
		unsigned int getUInt() const;
		long getLong() const;
		unsigned long getULong() const;
		double getDouble() const;
		const uint8_t *getBuffer(uint8_t &len) const;
		const char *getString() const;
		const char *getString(uint8_t &len) const;

		uint8_t getDataLength() const;

	private:
		bool init(uint8_t len);

	private:
		uint8_t _source;
		uint8_t _destination;
		uint8_t _type;
		uint8_t _len;
		uint8_t *_data;
};

#endif // __SimplePacket_H__
