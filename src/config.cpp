#include "config.h"

void Config::begin(bool force_reset)
{
    // Initialize EEPROM
    EEPROM.begin(512);

    if ((EEPROM.read(EEPROM_ADDR_IS_SET) != HIGH) || force_reset)
    {
        reset();
        EEPROM.write(EEPROM_ADDR_IS_SET, EEPROM_ADDR_CONF_SET);
        EEPROM.commit();
    }
}

void Config::SaveCredentials(void)
{
    //EEPROM.put(EEPROM_ADDR_WIFI, wifiCredentials);
    //EEPROM.write(EEPROM_ADDR_WIFI_SET, HIGH);
    //EEPROM.commit();
}

// reading credentials from EEPROM and savind it in struct
void Config::ReadCredentials(void)
{
    //EEPROM.get(EEPROM_ADDR_WIFI, wifiCredentials); 
}

void Config::reset()
{
    /*
    setBrightness(150);
    setBackgroundOn(true);
    setTimeOn(true);
    setTempOn(false);
    setAnimation(annimations::BREATHING);
    setColorHue(50);
    setColorSat(255);*/
}

uint8_t Config::getBrightness()
{
    return EEPROM.read(EEPROM_ADDR_BRIGHTNESS);
}

void Config::set_brightness(uint8_t value)
{
    config.brightness = value;
    EEPROM.write(EEPROM_ADDR_BRIGHTNESS, value);
    EEPROM.commit();
}

bool Config::getBackgroundOn()
{
    return EEPROM.read(EEPROM_ADDR_BACKGROUND_ON) == 1;
}

void Config::set_background_on(bool value)
{
    config.background = value;
    /*
    EEPROM.write(EEPROM_ADDR_BACKGROUND_ON, value);
    EEPROM.commit();*/
}

bool Config::getIsOn()
{
    return true;
}

void Config::set_power_on(bool value)
{
    config.isOn = value;
}

bool Config::getTimeOn()
{
    return EEPROM.read(EEPROM_ADDR_TIME_ON) == 1;
}

void Config::set_time_on(bool value)
{
    config.time = value;
    //EEPROM.write(EEPROM_ADDR_TIME_ON, value);
    //EEPROM.commit();
}

void Config::setInvertOn(bool value)
{
    config.invert = value;
}

void Config::set_temp_on(bool value)
{
    EEPROM.write(EEPROM_ADDR_TEMP_ON, value);
    EEPROM.commit();
}

byte Config::getSpeed()
{
    return config.speed;
}

void Config::set_speed(byte value)
{
    config.speed = value;
}

bool Config::getAlarmOn()
{
    return config.alarm;
}

void Config::set_alarm_on(bool value)
{
    config.alarm = value;
}

bool Config::getTempOn()
{
    return EEPROM.read(EEPROM_ADDR_TEMP_ON) == 1;
}

annimations Config::getAnimation()
{
    annimations x = (annimations)EEPROM.read(EEPROM_ADDR_ANNIMATION);
    return x;
}

void Config::setAnimation(annimations value)
{
    config.animation = (int)value;
    EEPROM.write(EEPROM_ADDR_ANNIMATION, (int)value);
    EEPROM.commit();
}

uint8_t Config::getColorHue()
{
    return EEPROM.read(EEPROM_ADDR_HUE);
}

void Config::setColorHue(uint8_t value)
{
    EEPROM.write(EEPROM_ADDR_HUE, value);
    EEPROM.commit();
}

uint8_t Config::getColorSat()
{
    return EEPROM.read(EEPROM_ADDR_SAT);
}

void Config::setColorSat(uint8_t value)
{
    EEPROM.write(EEPROM_ADDR_SAT, value);
    EEPROM.commit();
}
