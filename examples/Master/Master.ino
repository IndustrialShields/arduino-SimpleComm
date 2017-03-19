/*
   Copyright (c) 2017 Boot&Work Corp., S.L. All rights reserved

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <RS485.h>
#include <SimpleComm.h>

#define MASTER_ADDRESS 0x00
#define SLAVE_ADDRESS 0x01
#define TYPE 0x13

#define SEND_PERIOD 1000 // ms

SimpleComm RS485Comm(RS485);

unsigned int counter = 0;
unsigned long lastSent = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
	Serial.begin(9600L);

  // Start RS485
  RS485.begin(19200L);
  RS485.setTimeout(20);

  // Start SimpleComm system
  RS485Comm.begin(MASTER_ADDRESS);

	Serial.println("Master started");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  if (millis() - lastSent >= SEND_PERIOD) {
    // Prepare request packet
    SimplePacket request;
    request.set(counter);

    // Send it to slave through RS485 port
    if (RS485Comm.send(request, SLAVE_ADDRESS, TYPE)) {
      lastSent = millis();
      counter++;

      // Print the request
      Serial.print("Sent request: ");
      printPacket(request);
    }
  }

  // Get responses
  SimplePacket response;
  if (RS485Comm.receive(response)) {
    // Print the response
    Serial.print("Received response: ");
    printPacket(response);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void printPacket(const SimplePacket &packet) {
  Serial.print("dst: ");
  Serial.print(packet.getDestination(), HEX);
  Serial.print(", src: ");
  Serial.print(packet.getSource(), HEX);
  Serial.print(", typ: ");
  Serial.print(packet.getType(), HEX);
  Serial.print(", dat: ");
  uint8_t dlen;
  const uint8_t *data = packet.getBuffer(dlen);
  if (data) {
    while (dlen--) {
      Serial.print(*data++, HEX);
      Serial.print(' ');
    }
  } else {
    Serial.print("<empty>");
  }
  Serial.println();
}
