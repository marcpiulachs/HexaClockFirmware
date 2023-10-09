#ifndef _CONFIG_H
#define _CONFIG_H

#include <Arduino.h>
#include <EEPROM.h>
#include "display.h"

#define EEPROM_ADDR_IS_SET 0x00
#define EEPROM_ADDR_BRIGHTNESS 0x01
#define EEPROM_ADDR_BACKGROUND_ON 0x02
#define EEPROM_ADDR_TIME_ON 0x03
#define EEPROM_ADDR_ANNIMATION 0x04
#define EEPROM_ADDR_TEMP_ON 0x07
#define EEPROM_ADDR_ALARM_ON 0x08
// #define EEPROM_ADDR_TEMP_ON 0x07

#define EEPROM_ADDR_HUE 0x05
#define EEPROM_ADDR_SAT 0x06
#define EEPROM_ADDR_WIFI_SET 0x7
#define EEPROM_ADDR_CONF_SET 0x8

#define EEPROM_ADDR_WIFI 0x64

typedef struct {
    char ssid[64];
    char pass[64];
} wifiCredentials_t;

typedef struct {
    uint8_t brightness;
    bool background;
    bool temp;
    bool time;
    bool alarm;
    uint8_t sat;
    uint8_t hue;
    byte animation;
} config_t;

class Config
{
public:
    wifiCredentials_t wifiCredentials;
    config_t config;

    void begin(bool force_reset);
    void reset();

    uint8_t getBrightness();
    void setBrightness(uint8_t value);

    bool getBackgroundOn();
    void setBackgroundOn(bool value);

    bool getTimeOn();
    void setTimeOn(bool value);

    bool getTempOn();
    void setTempOn(bool value);

    bool setAlarmOn();
    void getAlarmOn(bool value);

    annimations getAnimation();
    void setAnimation(annimations value);

    uint8_t getColorHue();
    void setColorHue(uint8_t value);
    uint8_t getColorSat();
    void setColorSat(uint8_t value);

    void SaveCredentials();
    void ReadCredentials();
};

#endif //_CONFIG_H
