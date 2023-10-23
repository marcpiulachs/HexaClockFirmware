//
// Created by samuel on 14/09/2020.
//

#include "sensors.h"

Sensors::Sensors(byte pin) {
    this->oneWire = new OneWire(pin);
    this->ds18b20 = new DallasTemperature(this->oneWire);
}

void Sensors::begin() 
{
    this->ds18b20->begin();

    if (!this->ds18b20->getAddress(this->sensor, 0)){
        #ifdef DEBUG_HEXCLOCK
            Serial.println("Unable to find address for Device 0");
        #endif
    }

    #ifdef DEBUG_HEXCLOCK
        Serial.print("Device 0 Address: "); 
        printAddress(this->sensor); 
        Serial.println();
    #endif

    this->ds18b20->setResolution(this->sensor, TEMPERATURE_PRECISION);
    this->ds18b20->setWaitForConversion(false);
    this->ds18b20->requestTemperatures();
}

void Sensors::printAddress(uint8_t *address) 
{
    for (uint8_t i = 0; i < 8; i++)
    {
        // zero pad the address if necessary
        if (address[i] < 16) Serial.print("0");
        Serial.print(address[i], HEX);
    }
}

float Sensors::getTemp() 
{
    if (this->ds18b20->isConversionComplete()) 
    {
        this->temperature = this->ds18b20->getTempC(this->sensor);
        this->ds18b20->requestTemperatures();
    }

    return this->temperature;
}