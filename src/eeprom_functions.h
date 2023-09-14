//
// Created by samuel on 14/09/2020.
//

#ifndef HEXCLOCK_EEPROM_FUNCTIONS_H
#define HEXCLOCK_EEPROM_FUNCTIONS_H

#include <Arduino.h>
#include <EEPROM.h>
#include "annimation_manager.h"

#define EEPROM_ADDR_IS_SET 0x00
#define EEPROM_ADDR_BRIGHTNESS 0x01
#define EEPROM_ADDR_BACKGROUND_ON 0x02
#define EEPROM_ADDR_TIME_ON 0x03
#define EEPROM_ADDR_ANNIMATION 0x04
#define EEPROM_ADDR_TEMP_ON 0x07

#define EEPROM_ADDR_HUE 0x05
#define EEPROM_ADDR_SAT 0x06

void    config_begin(bool force_reset);
void    config_reset();


uint8_t config_read_brightness();
void    config_write_brightness(uint8_t value);

bool    config_read_background_on();
void    config_write_background_on(bool value);

bool    config_read_time_on();
void    config_write_time_on(bool value);

bool    config_read_temp_on();
void    config_write_temp_on(bool value);

annimations config_read_annimation();
void        config_write_annimation(annimations value);

uint8_t config_read_color_hue();
void    config_write_color_hue(uint8_t value);
uint8_t config_read_color_saturation();
void    config_write_color_saturation(uint8_t value);

#endif //HEXCLOCK_EEPROM_FUNCTIONS_H
