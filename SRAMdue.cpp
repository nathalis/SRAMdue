
#include <Arduino.h>
#include "SoftwareSpiMaster.h"

SoftwareSpiMaster spi;

 
//#include "Arduino.h"
#include "SRAMdue.h"

SRAMdue::SRAMdue(){/*nothing to construct*/}
SRAMdue::~SRAMdue(){/*nothing to destruct*/}

byte CS=10; // default CS global variable

byte MISO_pin=6;
byte MOSI_pin=5;
byte SCK_pin=7;

/*  Set up the memory chip to either single byte or sequence of bytes mode **********/


void SRAMdue::begin(byte CSpin, byte MISOpin, byte MOSIpin, byte SCKpin){            // Select for single or multiple byte transfer
  CS=CSpin;
  spi.begin(SCKpin, MOSIpin, MISOpin);  
}

void SRAMdue::SetMode(byte CSpin, char Mode){            // Select for single or multiple byte transfer
  CS=CSpin; // set global variable CS to user-defined CS pin
  pinMode(CS, OUTPUT);	                        // set CS pin to output mode
  digitalWrite(CS, LOW);                        // set SPI slave select LOW
  spi.transfer(WRMR);                           // command to write to mode register
  spi.transfer(Mode);                           // set for sequential mode
  digitalWrite(CS, HIGH);                       // release chip select to finish command
}

/************ Byte transfer functions ***************************/
void SRAMdue::WriteByte(uint32_t address, byte data_byte) {
  SetMode(CS,ByteMode);                 // set to send/receive single byte of data
  digitalWrite(CS, LOW);                         // set SPI slave select LOW;
  spi.transfer(WRITE);                           // send WRITE command to the memory chip
  spi.transfer((byte)(address >> 16));           // send high byte of address
  spi.transfer((byte)(address >> 8));            // send middle byte of address
  spi.transfer((byte)address);                   // send low byte of address
  spi.transfer(data_byte);                       // write the data to the memory location
  digitalWrite(CS, HIGH);                        //set SPI slave select HIGH
}

byte SRAMdue::ReadByte(uint32_t address) {
  SetMode(CS,ByteMode);                 // set to send/receive single byte of data
  char read_byte;
  digitalWrite(CS, LOW);                         // set SPI slave select LOW;
  spi.transfer(READ);                            // send READ command to memory chip
  spi.transfer((byte)(address >> 16));           // send high byte of address
  spi.transfer((byte)(address >> 8));            // send middle byte of address
  spi.transfer((byte)address);                   // send low byte of address
  read_byte = spi.transfer(0x00);                // read the byte at that address
  digitalWrite(CS, HIGH);                        // set SPI slave select HIGH;
  return read_byte;                              // send data back to the calling function
}

                   
