# SRAMdue
Arduino DUE Communications with 23LC1024 SRAM chip

Library based on sample program to use a Serial SRAM chip to expand memory for an Arduino Due giving access to an additional 128kB of random access memory.  The 23LC1024 uses the Software Serial Peripheral Interface (Soft-SPI) to transfer data and commands between the DUE and the memory chip.


    Author:  Nathalis

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
   
   
   
