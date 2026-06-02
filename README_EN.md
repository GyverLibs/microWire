This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/microWire.svg?color=brightgreen)](https://github.com/GyverLibs/microWire/releases/latest/download/microWire.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/microWire.svg)](https://registry.platformio.org/libraries/gyverlibs/microWire)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/microWire?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# microWire
Lightweight library with a standard set of tools for working with I2C hardware
- Make your code easier by simply replacing Wire.h with microWire. h h
- ATmega168/328p (nano,uno,mini), ATmega32u4 (leonardo,micro) , ATmega2560 (mega)

### Compatibility
AVR ATmega168/328p (nano,uno,mini), ATmega32u4 (leonardo,micro), ATmega2560 (mega)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **microWire** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/microWire/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
No.

<a id="usage"></a>
## Use of use
```cpp
void begin(void);            				// tyre initialization
void setClock(uint32_t clock);       		// manual setting of the bus frequency 31-900 kHz (in hertz)
void beginTransmission(uint8_t address); 	// Open the connection (to record data)
uint8_t endTransmission(bool stop);  		// Close the connection, make a stop or restart (by default - stop)
uint8_t endTransmission(void);  			// close the connection, make a stop
void write(uint8_t data);                	// send bytes of data to the bus, sending is done immediately, format - byte "unsigned char"
void requestFrom(uint8_t address , uint8_t length , bool stop); //open the connection and request data from the device, release or hold the bus
void requestFrom(uint8_t address , uint8_t length);  			//open the connection and request data from the device, release the bus
uint8_t read(void);                      	// read byte, Buffer No!!!, read all requested bytes at once, stop or restart after reading the last byte, configured in requestFrom
uint8_t available(void);                 	// Return the number of bytes left to read
```

<a id="example"></a>
## Example
```cpp
/* Пример записи и чтения данных в I2C - EEPROM "AT24C32" */

// #include <Wire.h> // Replace Wire.h with microWire. h h
#include <microWire.h>

uint8_t chipAddress = 0x57; // Device address (use i2c scaner to determine)
uint16_t cellAddress = 3064; // The address of the first cell, where we will write and where to read
uint8_t data_0 = 115; // data that we write in EEPROM (compare with this number when reading )
uint8_t data_1 = 14;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  /* запись */
  Wire.beginTransmission(chipAddress);  // Start transfer with the device, call to the address
  Wire.write(highByte(cellAddress));    // Send the highest byte of the first cell address
  Wire.write(lowByte(cellAddress));     // Send the junior byte of the cell's first address
  Wire.write(data_0);                   // drop off
  Wire.write(data_1);                   // We're unloading another byte of data.
  Wire.endTransmission();               // finalize

  delay(50);                            // wait

  /* чтение */
  Wire.beginTransmission(chipAddress);  // Start transfer with the device, call to the address
  Wire.write(highByte(cellAddress));    // Send the highest byte of the address of the first cell
  Wire.write(lowByte(cellAddress));     // Send a minor byte of the address of the first cell
  Wire.endTransmission();               // finalize
  Wire.requestFrom(chipAddress , 2);    // request your 2 bytes of data
  while (Wire.available()) {            // until the requested data is exhausted
    Serial.println(Wire.read());        // read and deduce them
  }
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v2.1
- v2.2 from firexx - added features for full compatibility with the Wire API

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
