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

#define SLAVE_ADDRESS 0x01

SimpleComm RS485Comm(RS485);

////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
	Serial.begin(9600L);

  // Start RS485
  RS485.begin(19200L);
  RS485.setTimeout(20);

  // Start SimplePacket system
  RS485Comm.begin(SLAVE_ADDRESS);

	Serial.println("Slave started");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // Wait for a request
  SimplePacket request;
  if (RS485Comm.receive(request)) {
    // Print the request
    Serial.print("Received request: ");
    printPacket(request);

    // Prepare response
    SimplePacket response;
    response.set(request.getInt());

    // Send response
    RS485Comm.send(response, request.getSource(), request.getType());

    // Print the response
    Serial.print("Sent response: ");
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
