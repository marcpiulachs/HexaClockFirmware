//
// Created by samuel on 14/09/2020.
//

#include "eeprom_functions.h"

void config_begin(bool force_reset) {
    EEPROM.begin(512);  //Initialize EEPROM

    if(EEPROM.read(EEPROM_ADDR_IS_SET) == 143 || force_reset) {
        config_reset();
        EEPROM.write(EEPROM_ADDR_IS_SET, 143);
        EEPROM.commit();
    }
}
void config_reset() {
    config_write_brightness(150);
    config_write_background_on(true);
    config_write_time_on(true);
    config_write_temp_on(false);
    config_write_annimation(annimations::BREATHING);
    config_write_color_hue(50);
    config_write_color_saturation(255);
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

bool config_read_temp_on(){
    return EEPROM.read(EEPROM_ADDR_TEMP_ON) == 1;
}

void config_write_temp_on(bool value){
    EEPROM.write(EEPROM_ADDR_TEMP_ON, value);
    EEPROM.commit();
}

annimations config_read_annimation() {
    annimations x = (annimations) EEPROM.read(EEPROM_ADDR_ANNIMATION);
    return x;
}

void config_write_annimation(annimations value) {
    EEPROM.write(EEPROM_ADDR_ANNIMATION, (int)value);
    EEPROM.commit();
}

uint8_t config_read_color_hue() {
    return EEPROM.read(EEPROM_ADDR_HUE);
}

void config_write_color_hue(uint8_t value) {
    EEPROM.write(EEPROM_ADDR_HUE, value);
    EEPROM.commit();
}

uint8_t config_read_color_saturation() {
    return EEPROM.read(EEPROM_ADDR_SAT);
}

void config_write_color_saturation(uint8_t value) {
    EEPROM.write(EEPROM_ADDR_SAT, value);
    EEPROM.commit();
}
