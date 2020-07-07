/**
 * SoftwareSpiMaster.cpp
 * https://github.com/thni323/SoftwareSpiMaster
 * 12.2019
 */
#include "SoftwareSpiMaster.h"

SoftwareSpiMaster::SoftwareSpiMaster()
{
    pinCLK = 0;
    pinMOSI = 0;
    pinMISO = 0;
}

void SoftwareSpiMaster::begin(uint8_t clk, uint8_t mosi, uint8_t miso)
{
    pinCLK = clk;
    pinMOSI = mosi;
    pinMISO = miso;

    if (initialized())
    {
        pinMode(pinCLK, OUTPUT);
        pinMode(pinMOSI, OUTPUT);
        pinMode(pinMISO, INPUT);
    }
}

void SoftwareSpiMaster::end()
{
    if (initialized())
    {
        pinMode(pinCLK, INPUT);
        pinMode(pinMOSI, INPUT);
        pinMode(pinMISO, INPUT);
    }
}

uint8_t SoftwareSpiMaster::transfer(uint8_t value)
{
    uint8_t readValue = 0;
    if (initialized())
    {
        for(uint8_t i = 0; i < 8; ++i)
        {
            digitalWrite(pinMOSI, (bool) (value & (1 << (7 - i))));
            delay(1);
            digitalWrite(pinCLK, HIGH);
            delay(1);
            readValue |= ((uint8_t) digitalRead(pinMISO)) << (7 - i);
            digitalWrite(pinCLK, LOW);
            delay(1);
        }
    }
    return readValue;
}

void SoftwareSpiMaster::transfer(const uint8_t* out, uint8_t* in, uint16_t size)
{
    if (initialized() && (size > 0) && (out != nullptr) && (in != nullptr))
    {
        for (uint16_t i=0; i < size; i++)
        {
            in[i] = transfer(out[i]);
        }
    }
}

void SoftwareSpiMaster::transferBytes(const uint8_t* sendBuf, uint8_t* recBuf, uint16_t size)
{
    transfer(sendBuf, recBuf, size);
}

bool SoftwareSpiMaster::initialized()
{
    return (pinCLK > 0) && (pinMOSI > 0) && (pinMISO > 0);
}
