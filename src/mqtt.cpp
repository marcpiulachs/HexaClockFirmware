//
// Created by samuel on 14/09/2020.
//

#include "mqtt.h"
#include "esp_system.h"

char *mqtt_all_topic;
char *mqtt_topics_on_off_power;
char *mqtt_topics_on_off_back;
char *mqtt_topics_on_off_time;
char *mqtt_topics_on_off_temp;
char *mqtt_topics_on_off_alarm;

char *mqtt_topics_brightness;
//char *mqtt_topics_invert;
//char *mqtt_topics_hue;
//char *mqtt_topics_sat;
char *mqtt_topics_effect;
char *mqtt_topics_speed;
char *mqtt_topics_temp;
//char *mqtt_topics_alarm_hour;
//char *mqtt_topics_alarm_minute;
char *mqtt_topics_time_hour;
char *mqtt_topics_time_minute;
//char *mqtt_topics_time_sync;

char *mqtt_reports_on_off_power;
char *mqtt_reports_on_off_back;
char *mqtt_reports_on_off_time;
char *mqtt_reports_on_off_temp;
char *mqtt_reports_on_off_alarm;
char *mqtt_reports_brightness;
char *mqtt_reports_temp;
char *mqtt_reports_time;
//char *mqtt_reports_hue;
//char *mqtt_reports_sat;
char *mqtt_reports_effect;

/* The unique clientId */
char clientid[64];

//Config config;
WiFiClient mqtt_wifi_client;
PubSubClient mqtt_client(mqtt_wifi_client);

void create_mqtt_clientId()
{
    // Creates the device ID based on its MAC address
    snprintf(clientid, 64, "hexaclock-%llX", ESP.getEfuseMac());
}

void create_mqtt_topics ()
{
    asprintf(&mqtt_all_topic, def_mqtt_all_topic, clientid);

    asprintf(&mqtt_topics_on_off_power, def_mqtt_topics_on_off_power, clientid);
    asprintf(&mqtt_topics_on_off_back, def_mqtt_topics_on_off_back, clientid);
    asprintf(&mqtt_topics_on_off_time, def_mqtt_topics_on_off_time, clientid);
    asprintf(&mqtt_topics_on_off_temp, def_mqtt_topics_on_off_temp, clientid);
    asprintf(&mqtt_topics_on_off_alarm, def_mqtt_topics_on_off_alarm, clientid);
    asprintf(&mqtt_topics_brightness, def_mqtt_topics_brightness, clientid);
    asprintf(&mqtt_topics_effect, def_mqtt_topics_effect, clientid);
    asprintf(&mqtt_topics_speed, def_mqtt_topics_speed, clientid);
    asprintf(&mqtt_topics_time_hour, def_mqtt_topics_time_hour, clientid);
    asprintf(&mqtt_topics_time_minute, def_mqtt_topics_time_minute, clientid);
    asprintf(&mqtt_topics_temp, def_mqtt_topics_temp, clientid);

    asprintf(&mqtt_reports_on_off_power, def_mqtt_reports_on_off_power, clientid);
    asprintf(&mqtt_reports_on_off_back, def_mqtt_reports_on_off_back, clientid);
    asprintf(&mqtt_reports_on_off_time, def_mqtt_reports_on_off_time, clientid);
    asprintf(&mqtt_reports_brightness, def_mqtt_reports_brightness, clientid);
    asprintf(&mqtt_reports_time, def_mqtt_reports_time, clientid);
    asprintf(&mqtt_reports_effect, def_mqtt_reports_effect, clientid);
    asprintf(&mqtt_reports_on_off_temp, def_mqtt_reports_on_off_temp, clientid);
    asprintf(&mqtt_reports_on_off_alarm, def_mqtt_reports_on_off_alarm, clientid);
    asprintf(&mqtt_reports_temp, def_mqtt_reports_temp, clientid);
}

void mqtt_begin()
{
    create_mqtt_clientId();
    create_mqtt_topics();
    mqtt_client.setServer(config.config.broker_host, config.config.broker_port);
    mqtt_client.setCallback(mqtt_callback);
}

void mqtt_reconnect()
{
    if (!mqtt_client.connected())
    {
        Serial.println("Attempting MQTT connection...");
        Serial.println();
        Serial.print("Host:");
        Serial.print(config.config.broker_host);
        Serial.println();
        Serial.print("Client Id:");
        Serial.print(clientid);
        Serial.println();

        if (mqtt_client.connect(clientid, config.config.broker_user, config.config.broker_pass))
        {
            Serial.println("Connected to MQTT");

            mqtt_client.publish("hexaclock/discover/advertise", clientid);
            mqtt_client.subscribe(mqtt_all_topic);

            Serial.println();
            Serial.print("Subscribed to :");
            Serial.print(mqtt_all_topic);
            Serial.println();

            // Report config values
            mqtt_report_config();
        }
        else
        {
            Serial.print("Failed to connect to mqtt server rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");
        }
    }
}

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{

    //char topic_2[64];

    /*
    Serial.println("-----------------------");
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
    */
   
    payload[length] = '\0';

    /*
    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_back)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setBackgroundOn(on);
        mqtt_client.publish(mqtt_reports_on_off_back, on ? "on" : "off");
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_time)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setTimeOn(on);
        mqtt_client.publish(mqtt_reports_on_off_time, on ? "on" : "off");
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_alarm)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.getAlarmOn(on);
        mqtt_client.publish(mqtt_reports_on_off_alarm, on ? "on" : "off");
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_temp)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setTempOn(on);
        mqtt_client.publish(mqtt_reports_on_off_temp, on ? "on" : "off");
    }
    
    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_all)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;

        config.setTimeOn(on);
        config.setBackgroundOn(on);
        config.setTempOn(on);
        config.getAlarmOn(on);

        //mqtt_client.publish(mqtt_reports_on_off_all, on ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_back, on ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_time, on ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_temp, on ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_alarm, on ? "on" : "off");
    }
    
    sprintf(topic_2, "%s%s", clientid, mqtt_topics_brightness);
    if (strcmp(topic, topic_2) == 0)
    {
        uint8_t brightness = atoi((char *)payload);
        config.setBrightness(brightness);
        mqtt_client.publish(mqtt_reports_brightness, String(brightness).c_str());
        if (brightness > 0)
        {
            mqtt_client.publish(mqtt_reports_on_off_time, "on");
        }
    }

    sprintf(topic_2, "%s%s", clientid, mqtt_topics_hue);
    if (strcmp(topic, topic_2) == 0)
    {
        float hue = atoi((char *)payload);
        int hue_int = map((int)hue, 0, 360, 0, 255);
        mqtt_client.publish(mqtt_reports_hue, String(hue_int).c_str());
        config.setColorHue((uint8_t)hue_int);
    }

    sprintf(topic_2, "%s%s", clientid, mqtt_topics_sat);
    if (strcmp(topic, topic_2) == 0)
    {
        float sat = atoi((char *)payload);
        int sat_int = map((uint8_t)sat, 0, 100, 0, 255);
        mqtt_client.publish(mqtt_reports_sat, String(sat_int).c_str());
        config.setColorSat((uint8_t)sat_int);
    }

    sprintf(topic_2, "%s%s", clientid, mqtt_topics_temp);
    if (strcmp(topic, topic_2) == 0)
    {
    }

    sprintf(topic_2, "%s%s", clientid, mqtt_topics_time_hour);
    if (strcmp(topic, topic_2) == 0)
    {
    }

    sprintf(topic_2, "%s%s", clientid, mqtt_topics_time_minute);
    if (strcmp(topic, topic_2) == 0)
    {
    }

    sprintf(topic_2, "%s%s", clientid, mqtt_topics_alarm_hour);
    if (strcmp(topic, topic_2) == 0)
    {
    }

    sprintf(topic_2, "%s%s", clientid, mqtt_topics_alarm_minute);
    if (strcmp(topic, topic_2) == 0)
    {
    }
*/
    if (strcmp(topic, mqtt_topics_on_off_power) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setIsOn(on);
        report_on();
    }
    else if (strcmp(topic, mqtt_topics_brightness) == 0)
    {
        uint8_t brightness = atoi((char *)payload);
        config.setBrightness(brightness);
        report_brightness();
    }
    else if (strcmp(topic, mqtt_topics_temp) == 0)
    {
        report_temp();
    }
    else if (strcmp(topic, mqtt_topics_on_off_back) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setBackgroundOn(on);
        report_background_on();
    }
    else if (strcmp(topic, mqtt_topics_on_off_time) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setTimeOn(on);
        report_time_on();
        //mqtt_client.publish(mqtt_reports_on_off_time, on ? "on" : "off", true);
    }
    else if (strcmp(topic, mqtt_topics_on_off_temp) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setTempOn(on);
        report_temp_on();
        //mqtt_client.publish(mqtt_reports_on_off_temp, on ? "on" : "off", true);
    }
    else if (strcmp(topic, mqtt_topics_on_off_alarm) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setAlarmOn(on);
        report_alarm_on();
        //mqtt_client.publish(mqtt_reports_on_off_alarm, on ? "on" : "off", true);
    }
    else if (strcmp(topic, mqtt_topics_speed) == 0)
    {
        float speed = atoi((char *)payload);
        int speed_int = map((uint8_t)speed, 0, 100, 0, 255);
        config.setSpeed(speed_int);
        report_speed();
        //mqtt_client.publish(mqtt_topics_speed, String(speed_int).c_str(), true);
    }
    else if (strcmp(topic, mqtt_topics_temp) == 0)
    {
        float speed = atoi((char *)payload);
        int speed_int = map((uint8_t)speed, 0, 100, 0, 255);
        config.setSpeed(speed_int);
        report_speed();
        //mqtt_client.publish(mqtt_topics_speed, String(speed_int).c_str(), true);
    }
    else if (strcmp(topic, mqtt_topics_effect) == 0)
    {
        if (strcmp((char *)payload, "fade") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "fade", true);
            config.setAnimation(annimations::COLORFADE);
        }
        else if (strcmp((char *)payload, "fish") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "fish", true);
            config.setAnimation(annimations::FISH);
        }
        else if (strcmp((char *)payload, "breathing") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "breathing", true);
            config.setAnimation(annimations::BREATHING);
        }
        else if (strcmp((char *)payload, "christmas") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "christmas", true);
            config.setAnimation(annimations::CHRISTMAS);
        }
        else if (strcmp((char *)payload, "wopr") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "wopr", true);
            config.setAnimation(annimations::WOPR);
        }
        else if (strcmp((char *)payload, "sine") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "sine", true);
            config.setAnimation(annimations::SINE);
        }
        else if (strcmp((char *)payload, "pride") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "pride", true);
            config.setAnimation(annimations::PRIDE);
        }
        else if (strcmp((char *)payload, "rain") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "rain", true);
            config.setAnimation(annimations::RAIN);
        }
        else if (strcmp((char *)payload, "fire") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "fire", true);
            config.setAnimation(annimations::FIRE);
        }
        else if (strcmp((char *)payload, "plasma") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "plasma", true);
            config.setAnimation(annimations::PLASMA);
        }
        else
        {
            report_animation();
        }
    }
}

/*
void mqtt_report_float(const char* report, float value)
{
    char topic[64] = "";
    sprintf(topic, "%s%s", clientid, report);
    mqtt_client.publish(topic, String(value).c_str());
}

void mqtt_report_int(const char* report, int value)
{
    char topic[64] = "";
    sprintf(topic, "%s%s", clientid, report);
    mqtt_client.publish(topic, String(value).c_str());
}

void mqtt_report_string(const char* report, const char* value)
{
    char topic[64] = "";
    sprintf(topic, "%s%s", clientid, report);
    mqtt_client.publish(topic, String(value).c_str());
}
*/

void mqtt_report_config()
{
    report_temp();
    report_speed();
    report_alarm_on();
    report_temp_on();
    report_on();
    report_brightness();
    report_time_on();
    report_background_on();
    report_animation();
}

void report_temp()
{
    char value[16];
    sprintf(value, "%d", (int)config.getSpeed());
    mqtt_client.publish(mqtt_reports_temp,  value, true);
}

void report_speed()
{
    char value[16];
    sprintf(value, "%d", (int)config.getSpeed());
    mqtt_client.publish(mqtt_topics_speed,  value, true);
}

void report_alarm_on()
{
    mqtt_client.publish(mqtt_reports_on_off_alarm, config.getAlarmOn() ? "on" : "off", true);
}

void report_temp_on()
{
    mqtt_client.publish(mqtt_reports_on_off_temp, config.getTempOn() ? "on" : "off", true);
}

void report_on()
{
    mqtt_client.publish(mqtt_reports_on_off_power, config.getIsOn() ? "on" : "off", true);
}

void report_brightness()
{
    mqtt_client.publish(mqtt_reports_brightness, String(config.getBrightness()).c_str());
}

void report_time_on()
{
    mqtt_client.publish(mqtt_reports_on_off_time, config.getTimeOn() ? "on" : "off");
}

void report_background_on()
{
    mqtt_client.publish(mqtt_reports_on_off_back, config.getBackgroundOn() ? "on" : "off");
}

void report_animation()
{
    switch (config.getAnimation())
    {
        case STARTUP:
        case STARTUP_WIFI:
            break;
        case COLORFADE:
            mqtt_client.publish(mqtt_reports_effect, "fade");
            break;
        case BREATHING:
            mqtt_client.publish(mqtt_reports_effect, "breathing");
            break;
        case CHRISTMAS:
            mqtt_client.publish(mqtt_reports_effect, "christmas");
            break;
    }    
}

void mqtt_loop()
{
  if (mqtt_client.connected()){
      mqtt_client.loop();
  }
}