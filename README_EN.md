This is an automatic translation, may be incorrect in some places. See sources and examples!

# Microwire
A light library with a standard set of tools for working with hardware i2c
- facilitate your code with a simple replacement of wire.h with microwire.h
- Atmega168/328p (Nano, UNO, Mini), Atmega32u4 (Leonardo, Micro), Atmega2560 (Mega)

## compatibility
AVR Atmega168/328p (Nano, UNO, Mini), Atmega32u4 (Leonardo, Micro), Atmega2560 (Mega)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** microwire ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download library] (https://github.com/gyverlibs/microwire/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
No

<a id="usage"> </a>
## Usage
`` `CPP
VOID Begin (VOID);// initialization of the tire
VOID setclock (Uint32_T Clock);// manual tire frequency installation 31-900 khz (in Hertz)
VOID BeginTransMission (Uint8_T Address);// Open the connection (for data recording)
Uint8_T EndtransMission (Bool Stop);// Close the connection, produce stop or restart (by default - Stop)
Uint8_T EndtransMission (VOID);// Close the connection, make stop
VOID Write (Uint8_T DATA);// Send bytes of the bytes of data, sending is carried out immediately, format - byte "Unsigned char"
VOID Requestfrom (Uint8_T Address, Uint8_t Length, Bool Stop);// Open the connection and request data from the device, release or hold the tire
VOID Requestfrom (Uint8_T Address, Uint8_t Length);// Open the connection and request data from the device, release the tire
uint8_t Read (VOID);// read a byte, no buffer !!!, read all the requested bytes, Stop or Restart after reading the last byte, is tuned in REquestfrom
Uint8_t Available (VOID);// will return the number of left bytes remaining
`` `

<a id="EXAMPLE"> </a>
## Example
`` `CPP
/ * Example of recording and reading data in i2C - Eeprom "AT24C32" */

// #include <wire.h> // Replace wire.hon microwire.h
#include <microwire.h>

uint8_t chipaddress = 0x57;// device address (use i2c Scaner to determine)
Uint16_T CELLADDRESS = 3064;// Address of the first cell where we will write and where to read
uint8_t data_0 = 115;// data that we will write in EEPROM (compare with this number when reading)
uint8_t data_1 = 14;

VOID setup () {
  Serial.Begin (9600);
  Wire.begin ();

  / * record */
  Wire.BegintransMission (Chipaddress);// Start gear with the device, call at the address
  Wire.write (Highbyte (Celladdress));// Send the senior byte of the first address of the cell
  Wire.write (Lowbyte (Celladdress));// Send the younger byte the first address of the cell
  Wire.write (Data_0);// Parch the byte data
  Wire.write (Data_1);// Parrating another byte of data
  Wire.endtransmission ();// We finish the program

  DELAY (50);// We will wait

  / * Reading */
  Wire.BegintransMission (Chipaddress);// Start gear with the device, call at the address
  Wire.write (Highbyte (Celladdress));// Send the senior byte of the address of the first cell
  Wire.write (Lowbyte (Celladdress));// Send the younger byte the address of the first cell
  Wire.endtransmission ();// We finish the program
  Wire.requestfrom (chipaddress, 2);// Request our 2 bytes of data
  While (wire.available ()) {// Until the requested data has ended
    Serial.println (wire.read ());// read and bring them out
  }
}

VOID loop () {
}
`` `

<a id="versions"> </a>
## versions
- V2.1
- V2.2 from Firexx - added functions for full compatibility with API Wire

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code