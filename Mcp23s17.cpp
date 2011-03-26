
// MCP23S17 SPI 16-bit IO expander
// http://ww1.microchip.com/downloads/en/DeviceDoc/21952b.pdf

// For the cmd, AAA is the 3-bit MCP23S17 device hardware address.
// Useful for letting up to 8 chips sharing same SPI Chip select
// #define MCP23S17_READ  B0100AAA1 
// #define MCP23S17_WRITE B0100AAA0 

// The default SPI Control Register - SPCR = B01010000;
// interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
// sample on leading edge of clk,system clock/4 rate (fastest).
// Enable the digital pins 11-13 for SPI (the MOSI,MISO,SPICLK)
#include <Spi.h>
#include "Mcp23s17.h"

//---------- constructor ----------------------------------------------------

MCP23S17::MCP23S17(uint8_t slave_select_pin)
{
  setup_ss(slave_select_pin);
  setup_device(0x00);
}

MCP23S17::MCP23S17(uint8_t slave_select_pin, byte aaa_hw_addr)
{
  // Set the aaa hardware address for this chip by tying the 
  // MCP23S17's pins (A0, A1, and A2) to either 5v or GND.
  setup_ss(slave_select_pin);

  // We enable HAEN on all connected devices before we can address them individually
  setup_device(0x00);
  write_addr(IOCON, read_addr(IOCON)|HAEN);

  // Remember the hardware address for this chip
  setup_device(aaa_hw_addr);
}

//------------------ protected -----------------------------------------------

uint16_t MCP23S17::byte2uint16(byte high_byte, byte low_byte)
{
  return (uint16_t)high_byte<<8 | (uint16_t)low_byte;
}

byte MCP23S17::uint16_high_byte(uint16_t uint16)
{
  return (byte)(uint16>>8);
}

byte MCP23S17::uint16_low_byte(uint16_t uint16)
{
  return (byte)(uint16 & 0x00FF);
}

void MCP23S17::setup_ss(uint8_t slave_select_pin)
{
  // Set slave select (Chip Select) pin for SPI Bus, and start high (disabled)
  ::pinMode(slave_select_pin,OUTPUT);
  ::digitalWrite(slave_select_pin,HIGH);
  this->slave_select_pin = slave_select_pin;
}

void MCP23S17::setup_device(uint8_t aaa_hw_addr)
{
  this->aaa_hw_addr = aaa_hw_addr;
  this->read_cmd  = B01000000 | aaa_hw_addr<<1 | 1<<0; // MCP23S17_READ  = B0100AAA1 
  this->write_cmd = B01000000 | aaa_hw_addr<<1 | 0<<0; // MCP23S17_WRITE = B0100AAA0
  // write_addr(IOCON, read_addr(IOCON)|SEQOP); // no need to enable SEQOP if BANK=0
}

uint16_t MCP23S17::read_addr(byte addr)
{
  byte low_byte;
  byte high_byte;
  ::digitalWrite(slave_select_pin, LOW);
  Spi.transfer(read_cmd);
  Spi.transfer(addr);
  low_byte  = Spi.transfer(0x0/*dummy data for read*/);
  high_byte = Spi.transfer(0x0/*dummy data for read*/);
  ::digitalWrite(slave_select_pin, HIGH);
  return byte2uint16(high_byte,low_byte);
}

void MCP23S17::write_addr(byte addr, uint16_t data)
{
  ::digitalWrite(slave_select_pin, LOW);
  Spi.transfer(write_cmd);
  Spi.transfer(addr);
  Spi.transfer(uint16_low_byte(data));
  Spi.transfer(uint16_high_byte(data));
  ::digitalWrite(slave_select_pin, HIGH);
}

//---------- public ----------------------------------------------------

void MCP23S17::pinMode(bool mode)
{
  uint16_t input_pins;
  if(mode == INPUT)
    input_pins = 0xFFFF;
  else
    input_pins = 0x0000;

  write_addr(IODIR, input_pins);
}

void MCP23S17::port(uint16_t value)
{
  write_addr(GPIO,value);
}

uint16_t MCP23S17::port()
{
  return read_addr(GPIO);
}

void MCP23S17::pinMode(uint8_t pin, bool mode)
{
  if(mode == INPUT)
    write_addr(IODIR, read_addr(IODIR) | 1<<pin );
  else
    write_addr(IODIR, read_addr(IODIR) & ~(1<<pin) );
}

void MCP23S17::digitalWrite(uint8_t pin, bool value)
{
  if(value)
    write_addr(GPIO, read_addr(GPIO) | 1<<pin );  
  else
    write_addr(GPIO, read_addr(GPIO) & ~(1<<pin) );  
}

int MCP23S17::digitalRead(uint8_t pin)
{
  (int)(read_addr(GPIO) & 1<<pin);
}



