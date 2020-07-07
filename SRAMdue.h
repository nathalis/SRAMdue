
#ifndef SRAMdue_h
#define SRAMdue_h

#include <Arduino.h>
#include <SPI.h>

/************SRAM opcodes: commands to the 23LC1024 memory chip ******************/
#define RDMR        5       // Read the Mode Register
#define WRMR        1       // Write to the Mode Register
#define READ        3       // Read command
#define WRITE       2       // Write command
#define RSTIO     0xFF      // Reset memory to SPI mode
#define ByteMode    0x00    // Byte mode (read/write one byte at a time)
#define Sequential  0x40    // Sequential mode (read/write blocks of memory)

extern byte CS;		    // Global variable for CS pin (default 10)

class SRAMdue {
  public:
    SRAMdue();
    ~SRAMdue();
    void begin(byte CSpin, byte MISOpin, byte MOSIpin, byte SCKpin);
    void SetMode(byte CSpin, char Mode);
    void WriteByte(uint32_t address, byte data_byte);
    byte ReadByte(uint32_t address);
};

#endif
