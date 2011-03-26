### Mcp23s17

A C++ object to control the Microchip MCP23S17 16-bit IO Expander. For the Arduino Platform.

### Introduction

Mcp23s17 is a simple object which mimics the typical Arduino functions for digital reads, digital writes, to set output pins etc. To use, we just wire up the SPI bus and instantiate a new object. By default, the chip powers up with all pins configured as high-impedance inputs. This library may also work with other AVR microcontroller devices (after some tweaking). This library was tested on Arduino UNO.

### Features

* All 16 pins are read / written to at once
* Generally fast SPI operation (up to 10Mhz)
* Generic example (works with all 328P Arduinos)
* Requires only very minor modifications for Arduino MEGA.
* Can instantiate multiple Mcp23s17 objects, one for each connected device
* Very simple interface and very few configuration
* Single-pin commands `obj.pinMode()`, `obj.digitalRead()`, `obj.digitalWrite()`
* As this is 16-bit IO expander, then 16-bit addressing with uint16_t datatype
* `obj.port()` to read or write to both ports at once.
* No methods for the 2x 8-bit ports individually (not needed).

### Requirements

* The SPI version of this chip (NOT wire/I2C). [MCP23S17 Product Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/21952b.pdf)
* [Arduino Spi Library (by Cam Thompson)](http://www.arduino.cc/playground/Code/Spi)* 

\* Other versions of Arduino Spi library (such as `SPI.h`) wont work / wernt tested.

### Getting Started

Pretty much everything is explained within the example sketch file. Open Mcp23s17Example.pde in Arduino IDE and upload it to your microcontroller device. Check that all of the SPI interface pins are connected OK for your device.

Dreamcat4


### Credit

* Mcp23s17 Version 1 - By Dreamcat4.

