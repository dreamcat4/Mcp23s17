// This example demonstrates control over SPI to the Microchip MCP23S17 16-bit IO expander
// SPI Pinouts are for Arduino Uno and Arduino Duemilanove board (will differ for Arduino MEGA)

// Download these into your Sketches/libraries/ folder...

// The Spi library by Cam Thompson. It was originally part of FPU library (micromegacorp.com)
// Available from http://arduino.cc/playground/Code/Fpu or http://www.arduino.cc/playground/Code/Spi
// Including Spi.h vv below initializea the MOSI, MISO, and SPI_CLK pins as per ATMEGA 328P
#include <Spi.h>

// Mcp23s17 library available from https://github.com/dreamcat4/Mcp23s17
#include <Mcp23s17.h>

// Wire up the SPI Interface common lines:
// #define SPI_MOSI             11 //arduino   <->   SPI Master Out Slave In   -> SI  (Pin 13 on MCP23S17 DIP)
// #define SPI_MISO             12 //arduino   <->   SPI Master In Slave Out   -> SO  (Pin 14 on MCP23S17 DIP)
// #define SPI_CLOCK            13 //arduino   <->   SPI Slave Clock Input     -> SCK (Pin 12 on MCP23S17 DIP)

// Then choose any other free pin as the Slave Select (pin 10 if the default but doesnt have to be)
#define MCP23S17_SLAVE_SELECT_PIN  9 //arduino   <->   SPI Slave Select           -> CS  (Pin 11 on MCP23S17 DIP)

// SINGLE DEVICE
// Instantiate a single Mcp23s17 object
MCP23S17 Mcp23s17 = MCP23S17( MCP23S17_SLAVE_SELECT_PIN );

// MULTIPLE DEVICES
// Up to 8 MCP23S17 devices can share the same SPI bus and slave select pins.
// Assign each chip a unique 3-bit device address (by setting the A2,A1,A0 pins)
// Then below, device address is optional 2nd parameter to the constructor fn...
// MCP23S17 Mcp23s17_0 = MCP23S17(MCP23S17_SLAVE_SELECT_PIN,0x0);
// ...
// MCP23S17 Mcp23s17_7 = MCP23S17(MCP23S17_SLAVE_SELECT_PIN,0x7);

void setup()
{
  // Example usage

  // Set all pins to be outputs (by default they are all inputs)
  Mcp23s17.pinMode(OUTPUT);

  // Change all pins at once, 16-bit value
  Mcp23s17.port(0x0F0F);

  // Write to individual pins
  Mcp23s17.digitalWrite(8,LOW);
  Mcp23s17.digitalWrite(12,HIGH);

  // Read all pins at once, 16-bit value
  uint16_t pinstate = Mcp23s17.port();

  // Set pin 14 (GPIO B6) to be an input
  Mcp23s17.pinMode(14,INPUT);

  // Read the value of pin 14
  Mcp23s17.digitalRead(14);
}

// Cycle the output lines at a staggered rate, pin/2 milliseconds
long timeoutInterval = 1;
long previousMillis = 0;
uint16_t counter = 0x0000;

void timeout()
{
  Mcp23s17.port(counter++);
}  

void loop()
{
  // handle timeout function, if any
  if (  millis() - previousMillis > timeoutInterval )
  {
    timeout();
    previousMillis = millis();
  }
  // Loop.
}


