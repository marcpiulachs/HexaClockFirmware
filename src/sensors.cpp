//
// Created by samuel on 14/09/2020.
//

#include "sensors.h"

sensors::sensors(byte onewire_bus) {
    this->oneWire = new OneWire(onewire_bus);
    this->ds18b20 = new DallasTemperature(this->oneWire);

}

void sensors::begin() {
    this->ds18b20->begin();

    if (!this->ds18b20->getAddress(this->sensor, 0)){
        #ifdef DEBUG_HEXCLOCK
            Serial.println("Unable to find address for Device 0");
        #endif
    }

    /*
    if (!this->ds18b20->getAddress(this->temp_sensor2, 1)){
        #ifdef DEBUG_HEXCLOCK
            Serial.println("Unable to find address for Device 1");
        #endif
    }*/

    #ifdef DEBUG_HEXCLOCK
        Serial.print("Device 0 Address: "); printAddress(this->sensor); Serial.println();
     //   Serial.print("Device 1 Address: "); printAddress(this->temp_sensor2); Serial.println();
    #endif

    this->ds18b20->setResolution(this->sensor, TEMPERATURE_PRECISION);
   // this->ds18b20->setResolution(this->temp_sensor2, TEMPERATURE_PRECISION);

    this->ds18b20->setWaitForConversion(false);
    this->ds18b20->requestTemperatures();
}



void sensors::printAddress(uint8_t *address) {
    for (uint8_t i = 0; i < 8; i++)
    {
        // zero pad the address if necessary
        if (address[i] < 16) Serial.print("0");
        Serial.print(address[i], HEX);
    }
}

float sensors::getSensorTemp() {
    if (this->ds18b20->isConversionComplete()) {
        this->temperature = this->ds18b20->getTempC(this->sensor);
       // this->temp2 = this->ds18b20->getTempC(this->temp_sensor2);
        this->ds18b20->requestTemperatures();
    }
    return this->temperature;
}