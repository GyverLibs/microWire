This is an automatic translation, may be incorrect in some places. See sources and examples!

#microWire
Lightweight library with a standard set of tools for working with hardware I2C
- Lighten your code by simply replacing Wire.h with microWire.h
- ATmega168/328p (nano,uno,mini), ATmega32u4 (leonardo,micro) , ATmega2560 (mega)

### Compatibility
AVR ATmega168/328p (nano,uno,mini), ATmega32u4 (leonardo,micro), ATmega2560 (mega)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **microWire** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/microWire/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
Not

<a id="usage"></a>
## Usage
```cpp
voidbegin(void); // bus initialization
void setClock(uint32_t clock); // manual setting of the bus frequency 31-900 kHz (in hertz)
void beginTransmission(uint8_t address); // open a connection (for writing data)
uint8_t endTransmission(bool stop); // close the connection, make stop or restart (default - stop)
uint8_t endTransmission(void); // close the connection, make a stop
void write(uint8_t data); // send data bytes to the bus, send immediately, format - byte "unsigned char"
void requestFrom(uint8_t address , uint8_t length , bool stop); // open a connection and request data from the device, release or hold the bus
void requestFrom(uint8_t address , uint8_t length); // open a connection and request data from the device, release the bus
uint8_t read(void); // read bytes, NO BUFFER!!! , read all requested bytes at once , stop or restart after reading the last byte, configurable in requestFrom
uint8_t available(void); // will return the number of bytes left to read
```

<a id="example"></a>
## Example
```cpp
/* Example of writing and reading data in I2C - EEPROM "AT24C32" */

// #include <Wire.h> // replace Wire.h with microWire.h
#include <microWire.h>

uint8_t chipAddress = 0x57; // device address (use i2c scanner to determine)
uint16_t cellAddress = 3064; // address of the first cell where we will write and where to read
uint8_t data_0 = 115; // data to be written to EEPROM (compare with this number when reading)
uint8_t data_1 = 14;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  /* record */
  Wire.beginTransmission(chipAddress); // start transfer with device , call by address
  Wire.write(highByte(cellAddress)); // send the high byte of the first cell address
  Wire.write(lowByte(cellAddress)); // send the low byte of the first cell addressyki
  Wire.write(data_0); // send data byte
  wire.write(data_1); // send another byte of data
  Wire.endTransmission(); // complete transfer

  delay(50); // wait

  /* read */
  Wire.beginTransmission(chipAddress); // start transfer with device , call by address
  Wire.write(highByte(cellAddress)); // send the high byte of the address of the first cell
  Wire.write(lowByte(cellAddress)); // send the low byte of the address of the first cell
  Wire.endTransmission(); // complete transfer
  Wire.requestFrom(chipAddress , 2); // request our 2 bytes of data
  while (Wire.available()) { // until the requested data runs out
    Serial.println(Wire.read()); // read and output them
  }
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v2.1
- v2.2 by firexx - added features for full compatibility with the Wire API

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!