//
// Created by samuel on 14/09/2020.
//

#include "eeprom_functions.h"

void config_begin() {
    EEPROM.begin(512);  //Initialize EEPROM

    if(EEPROM.read(EEPROM_ADDR_IS_SET) == 143) {
        config_reset();
        EEPROM.write(EEPROM_ADDR_IS_SET, 143);
        EEPROM.commit();
    }
}
void config_reset() {
    config_write_brightness(180);
    config_write_background_on(true);
    config_write_time_on(true);
}

uint8_t config_read_brightness() {
    return EEPROM.read(EEPROM_ADDR_BRIGHTNESS);
}
void config_write_brightness(uint8_t value) {
    EEPROM.write(EEPROM_ADDR_BRIGHTNESS, value);
    EEPROM.commit();
}

bool config_read_background_on() {
    return EEPROM.read(EEPROM_ADDR_BACKGROUND_ON) == 1;
}
void config_write_background_on(bool value){
    EEPROM.write(EEPROM_ADDR_BACKGROUND_ON, value);
    EEPROM.commit();
}

bool config_read_time_on(){
    return EEPROM.read(EEPROM_ADDR_TIME_ON) == 1;
}
void config_write_time_on(bool value){
    EEPROM.write(EEPROM_ADDR_TIME_ON, value);
    EEPROM.commit();
}