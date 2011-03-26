
// MCP23S17 SPI 16-bit IO expander
// http://ww1.microchip.com/downloads/en/DeviceDoc/21952b.pdf

#ifndef Mcp23s17_h
#define Mcp23s17_h

class MCP23S17
{
  public:
    // You must set specify the slave select pin
    MCP23S17(uint8_t slave_select);
    // Optionally, up to 8 devices can share the same slave select pin
    MCP23S17(uint8_t slave_select, byte aaa_hw_addr);

    // GPIO 16-bit Combined Port (GPIO A0-A7 + GPIO B0-B7)
    void pinMode(bool mode);
    void port(uint16_t value);
    uint16_t port();

    // Work on individual pins 0-15
    void pinMode(uint8_t pin, bool mode);
    void digitalWrite(uint8_t pin, bool value);
    int  digitalRead(uint8_t pin);

    // Public Constants
    const static uint8_t GPIO_A0 = 0;
    const static uint8_t GPIO_A1 = 1;
    const static uint8_t GPIO_A2 = 2;
    const static uint8_t GPIO_A3 = 3;
    const static uint8_t GPIO_A4 = 4;
    const static uint8_t GPIO_A5 = 5;
    const static uint8_t GPIO_A6 = 6;
    const static uint8_t GPIO_A7 = 7;
    const static uint8_t GPIO_B0 = 8;
    const static uint8_t GPIO_B1 = 9;
    const static uint8_t GPIO_B2 = 10;
    const static uint8_t GPIO_B3 = 11;
    const static uint8_t GPIO_B4 = 12;
    const static uint8_t GPIO_B5 = 13;
    const static uint8_t GPIO_B6 = 14;
    const static uint8_t GPIO_B7 = 15;

  // Addressing individual ports - not implemented
    // // GPIO Port A
    // void porta_pinMode(bool mode);
    // void porta(byte value);
    // byte porta();
    // 
    // void porta_pinMode(uint8_t pin, bool mode);
    // void porta_digitalWrite(uint8_t pin, bool value);
    // int  porta_digitalRead(uint8_t pin);
    // 
    // // GPIO Port B
    // void portb_pinMode(bool mode);
    // void portb(byte value);
    // byte portb();
    // 
    // void portb_pinMode(uint8_t pin, bool mode);
    // void portb_digitalWrite(uint8_t pin, bool value);
    // int  portb_digitalRead(uint8_t pin);

  protected:
    // Protected Constants
    const static uint8_t IOCONA = 0x0A;   // Config register is here on power up
    const static uint8_t IOCON  = IOCONA; // Config register is here on power up

    // Config options
    // const static uint8_t SEQOP  = B00100000; // Not needed if BANK=0 (default)
    const static uint8_t HAEN   = B00001000; // Enable the AAA 3-bit chip select
    // We never set BANK, as that would re-map all the address mapping
    // for the registers. Avoiding BANK doesnt disable any features.
    // const static uint8_t BANK   = B10000000;
    // const static uint8_t MIRROR = B01000000; // we dont use interrupt feature

    // As BANK=0, Register addresses are therefore mapped per
    // "TABLE 1-6:  CONTROL REGISTER SUMMARY (IOCON.BANK = 0)"

    const static uint8_t IODIRA = 0x00;
    const static uint8_t IODIRB = 0x01;
    const static uint8_t IODIR  = IODIRA;

    const static uint8_t GPPUA  = 0x0C;
    const static uint8_t GPPUB  = 0x0D;
    const static uint8_t GPPU   = GPPUA;

    const static uint8_t GPIOA  = 0x12;
    const static uint8_t GPIOB  = 0x13;
    const static uint8_t GPIO   = GPIOA;

    uint8_t slave_select_pin;
    byte aaa_hw_addr;

    byte read_cmd;
    byte write_cmd;

    void setup_ss(uint8_t slave_select_pin);
    void setup_device(uint8_t aaa_hw_addr);

    uint16_t read_addr(byte addr);
    void write_addr(byte addr, uint16_t data);

    uint16_t byte2uint16(byte high_byte, byte low_byte);
    byte uint16_high_byte(uint16_t uint16);
    byte uint16_low_byte(uint16_t uint16);
};

#endif // Mcp23s17_h



