//
// Created by samuel on 14/09/2020.
//

#include "mqtt.h"
#include "esp_system.h"

//const char *mqtt_topics = "/#";
const char *mqtt_topics_on_off_back = "/background";
const char *mqtt_topics_on_off_time = "/clock";

const char *mqtt_topics_on_off_temp = "/onoff/temp";
const char *mqtt_topics_on_off_alarm = "/onoff/alarm";
//const char *mqtt_topics_on_off_all = "/onoff/all";
const char *mqtt_topics_brightness = "/brightness";
const char *mqtt_topics_invert = "/invert";
const char *mqtt_topics_hue = "/hue";
const char *mqtt_topics_sat = "/sat";
const char *mqtt_topics_effect = "/effect";
const char *mqtt_topics_speed = "/speed";
const char *mqtt_topics_temp = "/temp";
const char *mqtt_topics_alarm_hour = "/alarm/hour";
const char *mqtt_topics_alarm_minute = "/alarm/minute";
const char *mqtt_topics_time_hour = "/time/hour";
const char *mqtt_topics_time_minute = "/time/minute";
const char *mqtt_topics_time_sync = "/time/sync";

//const char *mqtt_reports_on_off_all = "/reports/onoff/all";
const char *mqtt_reports_on_off_back = "/reports/onoff/background";
const char *mqtt_reports_on_off_time = "/reports/onoff/time";
const char *mqtt_reports_on_off_temp = "/reports/onoff/temp";
const char *mqtt_reports_on_off_alarm = "/reports/onoff/alarm";
const char *mqtt_reports_brightness = "/reports/brightness";
const char *mqtt_reports_temp = "/reports/temp";
const char *mqtt_reports_time = "/reports/time";
const char *mqtt_reports_hue = "/reports/hue";
const char *mqtt_reports_sat = "/reports/sat";
const char *mqtt_reports_effect = "/reports/effect";

/* The unique clientId */
char clientid[64];

//Config config;
WiFiClient mqtt_wifi_client;
PubSubClient mqtt_client(mqtt_wifi_client);

void createClientId()
{
    uint64_t mac = ESP.getEfuseMac();
    //sprintf(clientid, "%s-%016x", "HexaClock", mac);
    snprintf(clientid, 64, "hexaclock-%llX", ESP.getEfuseMac());
}

void mqtt_begin()
{
    createClientId();
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

        char topic[64];

        // char chipId[64];
        // snprintf(chipId, 64, "HexClock-%llX", ESP.getEfuseMac());

        // String clientId = "HexClock-" + getUniqueId();
        //  const char* clientId2 = "HexaClock-" + ESP.ESP_getFlashChipId();

        if (mqtt_client.connect(clientid, config.config.broker_user, config.config.broker_pass))
        {
            Serial.println("Connected to MQTT");

            mqtt_client.publish("hexaclock/discover/advertise", clientid);
            mqtt_reportConfig();

            sprintf(topic, "%s/#", clientid);
            mqtt_client.subscribe(topic);

            Serial.print("Subscribed to :");
            Serial.print(topic);
            Serial.println();
        }
        else
        {
            Serial.print("Failed to connect to mqtt server rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");

            // Wait 5 seconds before retrying
            //delay(5000);
        }
    }
}

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    char topic_2[64];

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
    if (String(topic).endsWith(mqtt_topics_brightness))
    {
        uint8_t brightness = atoi((char *)payload);
        config.setBrightness(brightness);
        mqtt_client.publish(mqtt_reports_brightness, String(brightness).c_str());
    }

    if (String(topic).endsWith(mqtt_topics_on_off_back))
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setBackgroundOn(on);
        mqtt_client.publish(mqtt_reports_on_off_back, on ? "on" : "off");
    }

    if (String(topic).endsWith(mqtt_topics_on_off_time))
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setTimeOn(on);
        mqtt_client.publish(mqtt_reports_on_off_time, on ? "on" : "off");
    }
    
    if (String(topic).endsWith(mqtt_topics_invert))
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config.setInvertOn(on);
        mqtt_client.publish(mqtt_topics_invert, on ? "on" : "off");
    }

    if (String(topic).endsWith(mqtt_topics_speed))
    {
        float speed = atoi((char *)payload);
        int speed_int = map((uint8_t)speed, 0, 100, 0, 255);
        config.setSpeed(speed_int);
        mqtt_client.publish(mqtt_topics_speed, String(speed_int).c_str());
    }
  
    if (String(topic).endsWith(mqtt_topics_effect))
    {
        if (strcmp((char *)payload, "color_fade") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "color_fade");
            config.setAnimation(annimations::COLORFADE);
        }
        if (strcmp((char *)payload, "fish") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "fish");
            config.setAnimation(annimations::FISH);
        }
        if (strcmp((char *)payload, "breathing") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "breathing");
            config.setAnimation(annimations::BREATHING);
        }
        if (strcmp((char *)payload, "christmas") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "christmas");
            config.setAnimation(annimations::CHRISTMAS);
        }
        if (strcmp((char *)payload, "wopr") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "wopr");
            config.setAnimation(annimations::WOPR);
        }
        if (strcmp((char *)payload, "sine") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "sine");
            config.setAnimation(annimations::SINE);
        }
        if (strcmp((char *)payload, "pride") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "pride");
            config.setAnimation(annimations::PRIDE);
        }
        if (strcmp((char *)payload, "rain") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "rain");
            config.setAnimation(annimations::RAIN);
        }
        if (strcmp((char *)payload, "fire") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "fire");
            config.setAnimation(annimations::FIRE);
        }
        if (strcmp((char *)payload, "plasma") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "plasma");
            config.setAnimation(annimations::PLASMA);
        }
    }
}

void mqtt_reportTemperature(float value)
{
    mqtt_client.publish(mqtt_reports_temp, String(value).c_str());
}

void mqtt_reportConfig()
{
    //mqtt_client.publish(mqtt_reports_on_off_all, config.getBackgroundOn() && config.getTimeOn() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_on_off_back, config.getBackgroundOn() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_on_off_time, config.getTimeOn() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_brightness, String(config.getBrightness()).c_str());
    mqtt_client.publish(mqtt_reports_hue, String((map(config.getColorHue(), 0, 255, 0, 360))).c_str());
    mqtt_client.publish(mqtt_reports_sat, String((map(config.getColorSat(), 0, 255, 0, 100))).c_str());
    /*
        mqtt_client.publish(mqtt_reports_huesat,(
                                    String(map(config_read_color_hue(),0,255,0,360)) +","+ String(map(config_read_color_saturation(),0,255,0,100))
        ).c_str());*/

    switch (config.getAnimation())
    {
        case STARTUP:
        case STARTUP_WIFI:
            break;
        case COLORFADE:
            mqtt_client.publish(mqtt_reports_effect, "color_fade");
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
    /*
    if (!mqtt_client.connected()){
        mqtt_reconnect();
    }*/

  if (mqtt_client.connected()){
    mqtt_client.loop();
  }
}
