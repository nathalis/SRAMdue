/**
 * SoftwareSpiMaster.h
 * https://github.com/thni323/SoftwareSpiMaster
 * 12.2019
 */ 
#ifndef _SOFTWARESPIMASTER_
#define _SOFTWARESPIMASTER_

#include <Arduino.h>

class SoftwareSpiMaster
{
public:
    /**
     * Default constructor
     */ 
    SoftwareSpiMaster();

    /**
     * Start a SPI master using the given pins
     * @param clk Clock pin
     * @param miso Master Out / Slave In pin
     * @param miso Master In / Slave Out pin
     * @param ss (optional) Slave Select pin
     *            Sets the corresponding pin to low during SPI transfer.
     */  
    void begin(uint8_t clk, uint8_t mosi, uint8_t miso);

    /**
     * Stops the SPI master
     * Sets previously used pins as input.
     */ 
    void end();

    /**
     * Transfer a single byte to the slave
     * @param value The byte value to transfer
     * @return The byte value returned from slave
     */ 
    uint8_t transfer(uint8_t value);

    /**
     * Transfer a buffer to the slave
     * Note: Given size must not exceed capacity of sendBuf or recBuf!
     * @param sendBuf Pointer to the data to send
     * @param recBuf Pointer to a buffer for received from slave
     * @param size The number of bytes to be send         
     */ 
    void transfer(const uint8_t* sendBuf, uint8_t* recBuf, uint16_t size);

    /**
     * Added for compability, same ass @see transfer(const uint8_t* sendBuf, uint8_t* recBuf, uint16_t size)
     */ 
    void transferBytes(const uint8_t* sendBuf, uint8_t* recBuf, uint16_t size);

private:
    bool initialized();

    uint8_t pinCLK;
    uint8_t pinMISO;
    uint8_t pinMOSI;
};

#endif //_SOFTWARESPIMASTER_