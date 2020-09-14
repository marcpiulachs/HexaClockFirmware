//
// Created by samuel on 14/09/2020.
//

#ifndef HEXCLOCK_EEPROM_FUNCTIONS_H
#define HEXCLOCK_EEPROM_FUNCTIONS_H

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_ADDR_IS_SET 0x00
#define EEPROM_ADDR_BRIGHTNESS 0x01
#define EEPROM_ADDR_BACKGROUND_ON 0x02
#define EEPROM_ADDR_TIME_ON 0x03

void    config_begin();
void    config_reset();

uint8_t config_read_brightness();
void    config_write_brightness(uint8_t value);
bool    config_read_background_on();
void    config_write_background_on(bool value);
bool    config_read_time_on();
void    config_write_time_on(bool value);


#endif //HEXCLOCK_EEPROM_FUNCTIONS_H
