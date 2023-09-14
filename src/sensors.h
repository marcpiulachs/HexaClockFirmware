//
// Created by samuel on 14/09/2020.
//

#ifndef HEXCLOCK_SENSORS_H
#define HEXCLOCK_SENSORS_H
#define DEBUG_HEXCLOCK

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>

#define TEMPERATURE_PRECISION 10

class sensors {
    public:
        explicit sensors(byte onewire_bus);
        void begin();
        float getSensorTemp();
        //float getSensorTemp2();

    private:
        OneWire *oneWire;
        DallasTemperature *ds18b20;
        DeviceAddress sensor{};
        float temperature;

        #ifdef DEBUG_HEXCLOCK
            void printAddress(DeviceAddress address);
        #endif
};


#endif //HEXCLOCK_SENSORS_H
