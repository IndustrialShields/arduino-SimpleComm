# Arduino & ESP32 SimpleComm library
### by [Industrial Shields](https://www.industrialshields.com)

## Getting started

### Prerequisites
1. The [Arduino IDE](http://www.arduino.cc) 1.8.0 or higher
2. The [Industrial Shields Arduino boards](https://www.industrialshields.com/blog/industrial-shields-blog-1/post/installing-the-industrial-shields-boards-in-the-arduino-ide-63) or the [Industrial Shields ESP32 boards](https://www.industrialshields.com/blog/industrial-shields-blog-1/post/installing-the-industrial-shields-boards-in-the-arduino-ide-63) equivalent (optional, used in the examples).

### Installing
1. Download the [library](http://www.github.com/industrialshields/arduino-tools40) from the GitHub as a "ZIP" file.
2. From the Arduino IDE, select the downloaded "ZIP" file in the menu "Sketch/Include library/Add .ZIP library".
3. Now you can open any example from the "File/Examples/Tools40" menu.

## Reference

```c++
#include <SimpleComm.h>
```

The **SimpleComm** module sends and receives data through any Stream: RS-485, RS-232, Ethernet... It is enough flexible to support different kind of communication typologies: Ad-hoc, Master-Slave, Client-Server, and so on, using an easy to use API. 

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

The **SimpleComm** class is the interface for sending and receiving packets through the desired Stream.

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

## Compatibility between architectures
This library relies on standard C++ types (e.g., unsigned long, int) which can function correctly if the communicating architectures maintain consistent type sizes. However, problems may arise if you try to communicate different CPU architectures, such as ESP32 and Arduino. The C++ types that are defined in each architecture have different sizes, which will cause communication errors.

To ensure proper communication between different architectures and to address potential type size issues, the library provides a solution through the "SimplePacketConfig.h" header file. This file allows users to customise the types used in the library, thereby fixing the size of the types for proper communication:
* If you uncomment `#define UNIVERSAL_CPP` the types used will be the minimum size according to the C++ standard.
* If you uncomment `#define CUSTOM_TYPES`, the types used will be the size of what you define.
