/*  Arduino DUE Memory Expansion Sample Program
    Author:  Nathalis

   Sample program to use a Serial SRAM chip to expand memory for an Arduino DUE
   giving access to an additional 128kB of random access memory.  The 23LC1024 uses
   the Software Serial Peripheral Interface (Software-SPI) to transfer data and commands between the
   UNO and the memory chip.

   Used the following components:
   (1) Arduino DUE
   (2) Microchip 23LC1024 SPI SRAM chip
   
   Wiring:
   23LC1024 - DUE:
   ---------------
   Pin1 (JSC) -- Pin 2 (CS) (with 10K pullup to +5V)
   Pin2 (SO)  -- Pin 6 (MISO)
   Pin3 (NU)  -- 10K -- +5V
   Pin4 (GND) -- GND
   Pin5 (SI)  -- Pin 5 (MOSI)
   Pin6 (SCK) -- Pin 7 (SCK)
   Pin7 (HOLD) -- 10K -- +5V
   Pin8 (V+)  -- +5V
*/
#include <SRAMdue.h>

#define CSPIN 2       // Default Chip Select Line for Uno (change as needed)
SRAMdue sram;       //initialize an instance of this class

/*******  Set up code to define variables and start the SCI and SPI serial interfaces  *****/
void setup()
{
  uint32_t address = 0;                       // create a 32 bit variable to hold the address (uint32_t=long)
  Serial.begin(9600);                         // set communication speed for the serial monitor

  Serial.println("Setting up...");
  
  sram.begin(CSPIN,6,5,7); // CSpin, MISOpin,  MOSIpin, SCKpin
  ///sram.SetMode(CSPIN,0);
    
  // And now the fun begins:
  /**********Write a Single Byte *******************/
  byte data = 0;                              // initialize the data
  for(int i = 0; i <=5; i++){                 // Let's write 5 individual bytes to memory 
    address = i;                              // use the loop counter as the address
    sram.WriteByte(address, data);            // now write the data to that address
    data+=2;                                  // increment the data by 2 
  }

/********* Read a single Byte *********************/
  Serial.println("Reading each data byte individually: ");
  byte value;                                 // create variable to hold the data value read
  for(int i = 0; i <=5; i++){                 // start at memory location 0 and end at 5
    address = i;                              // use the loop counter as the memory address
    value = sram.ReadByte(address);           // reads a byte of data at that memory location
    Serial.println(value);                    // Let's see what we got
  }

}

void loop()
{
}
