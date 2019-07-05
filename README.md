# SimpleComm library for Arduino devices

## Gettings started

### Prerequisites
1. The [Arduino IDE](http://www.arduino.cc) 1.8.0 or higher

### Installing
1. Download the [library](http://www.github.com/industrialshields/arduino-SimpleComm.git) from the GitHub as a "ZIP" file.
2. From the Arduino IDE, select the downloaded "ZIP" file in the menu "Sketch/Include library/Add .ZIP library".
3. Now you can open any example from the "File/Examples/SimpleComm" menu.

## Reference

```c++
#include <SimpleComm.h>
```

The **SimpleComm** module sends and receives data through any Arduino Stream: RS-485, RS-232, Ethernet... It is enough flexible to support different kind of communication typologies: Ad-hoc, Master-Slave, Client-Server, and so on, using an easy to use API. 

The **SimplePacket** class encapsulates the data into a packet.

The `setData` function fills up the packet with the desired data for sending it to a remote device. It is possible to fill up the packet with different types of data: bool, char, unsigned char, int, unsigned int, long, unsigned long, double, string and even custom data types.

```c++
int num = 1234;
SimplePacket packet1;
packet1.setData(num);
```

```c++
SimplePacket packet2;
packet2.setData("text data");
```

```c++
typedef struct {
    int a;
    char b;
} customType;
customType customVar;
customVar.a = 1234;
customVar.b = 'B';
SimplePacket packet3;
packet3.setData(customVar, sizeof(customVar));
```

There are also getter functions, which return the data contained in the packet, depending on the data type. If length is specified, it returns the data length in bytes.

```c++
int num = packet1.getInt();
```

```c++
const char *str = packet2.getString();
```

```c++
const customType *var = (const customType*) packet3.getData();
```

The **SimpleComm** class is the interface for sending and receiving packets through the desired Arduino Stream.

The `begin(byte)` function enables the communication system and sets the devices identifier/address. Each device has its own address which identifies it. Devices receive packets sent to them, using their address, but not to others.

```c++
byte address = 1234;
SimpleComm.begin(address);
```

It is possible to send packets to a device with an address, and optionally define the packet type.

```c++
byte destination = 87;
SimpleComm.send(RS485, packet, destination);
SimpleComm.send(RS485, packet, destination, 0x33);
```

To send packets to all devices it is possible to send a broadcast packet with the destination field set to 0 (zero).

```c++
byte destination = 0;
SimpleComm.send(RS485, packet, destination);
```

The `receive` function receives a packet from another device, using the stream. It returns true if a packet is really received.

```c++
SimplePacket rxPacket;
if (SimpleComm.receive(RS485, rxPacket)) {
    // A packet is received
}
```

It is also possible to receive all the packets (sniffer mode) by setting the SimpleComm address to 0 (zero). This mode is useful when implementing a gateway node between Ethernet and RS-485.

```c++
byte address = 0;
SimpleComm.begin(address);
```
