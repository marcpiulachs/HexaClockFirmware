//
// Created by samuel on 14/09/2020.
//

#include "mqtt.h"
#include "esp_system.h"

const char *mqtt_topics = "/#";
const char *mqtt_topics_on_off_back = "/onoff/back";
const char *mqtt_topics_on_off_time = "/onoff/time";
const char *mqtt_topics_on_off_temp = "/onoff/temp";
const char *mqtt_topics_on_off_alarm = "/onoff/alarm";
const char *mqtt_topics_on_off_all = "/onoff/all";
const char *mqtt_topics_brightness = "/brightness";
const char *mqtt_topics_hue = "/hue";
const char *mqtt_topics_sat = "/sat";
const char *mqtt_topics_effect = "/effect";
const char *mqtt_topics_temp = "/temp";
const char *mqtt_topics_alarm_hour = "/alarm/hour";
const char *mqtt_topics_alarm_minute = "/alarm/minute";
const char *mqtt_topics_time_hour = "/time/hour";
const char *mqtt_topics_time_minute = "/time/minute";

const char *mqtt_reports_on_off_all = "/reports/onoff/all";
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

WiFiClient mqtt_wifi_client;
PubSubClient mqtt_client(mqtt_wifi_client);

void GenerateClientId()
{
    uint64_t mac = ESP.getEfuseMac();
    sprintf(clientid, "HexaClock-%016x", mac);
}

void mqtt_begin()
{
    GenerateClientId();
    mqtt_client.setServer(mqtt_host, 1883);
    mqtt_client.setCallback(mqtt_callback);
}

void mqtt_reconnect()
{
    Serial.println("mqtt_reconnect");
    delay(100);
    while (!mqtt_client.connected())
    {
        Serial.println("Attempting MQTT connection...");
        Serial.println("Client Id:");
        Serial.print(clientid);

        // char chipId[64];
        // snprintf(chipId, 64, "HexClock-%llX", ESP.getEfuseMac());

        // String clientId = "HexClock-" + getUniqueId();
        //  const char* clientId2 = "HexaClock-" + ESP.ESP_getFlashChipId();

        if (mqtt_client.connect(clientid, mqtt_user, mqtt_pass))
        {
            Serial.println("Connected to MQTT");

            mqtt_client.publish("discover/advertise", clientid);
            mqtt_reportConfig();

            mqtt_client.subscribe(strcat(clientid, mqtt_topics));
        }
        else
        {
            Serial.print("Failed to connect to mqtt server rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");

            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    payload[length] = '\0';

    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_back)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config_write_background_on(on);
        mqtt_client.publish(mqtt_reports_on_off_back, on ? "on" : "off");
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_time)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config_write_time_on(on);
        mqtt_client.publish(mqtt_reports_on_off_time, on ? "on" : "off");
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_alarm)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config_write_alarm_on(on);
        mqtt_client.publish(mqtt_reports_on_off_alarm, on ? "on" : "off");
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_temp)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config_write_temp_on(on);
        mqtt_client.publish(mqtt_reports_on_off_temp, on ? "on" : "off");
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_on_off_all)) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;

        config_write_time_on(on);
        config_write_background_on(on);
        config_write_temp_on(on);
        config_write_alarm_on(on);

        mqtt_client.publish(mqtt_reports_on_off_all, on ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_back, on ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_time, on ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_temp, on ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_alarm, on ? "on" : "off");
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_brightness)) == 0)
    {
        uint8_t brightness = atoi((char *)payload);
        config_write_brightness(brightness);
        mqtt_client.publish(mqtt_reports_brightness, String(brightness).c_str());
        if (brightness > 0)
        {
            mqtt_client.publish(mqtt_reports_on_off_time, "on");
        }
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_hue)) == 0)
    {
        float hue = atoi((char *)payload);
        int hue_int = map((int)hue, 0, 360, 0, 255);
        mqtt_client.publish(mqtt_reports_hue, String(hue_int).c_str());
        config_write_color_hue((uint8_t)hue_int);
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_sat)) == 0)
    {
        float sat = atoi((char *)payload);
        int sat_int = map((uint8_t)sat, 0, 100, 0, 255);
        mqtt_client.publish(mqtt_reports_sat, String(sat_int).c_str());
        config_write_color_sat((uint8_t)sat_int);
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_temp)) == 0)
    {
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_time_hour)) == 0)
    {
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_time_minute)) == 0)
    {
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_alarm_hour)) == 0)
    {
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_alarm_minute)) == 0)
    {
    }
    if (strcmp(topic, strcat(clientid, mqtt_topics_effect)) == 0)
    {
        if (strcmp((char *)payload, "color_fade") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "color_fade");
            config_write_annimation(annimations::COLORFADE);
        }
        if (strcmp((char *)payload, "breathing") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "breathing");
            config_write_annimation(annimations::BREATHING);
        }
        if (strcmp((char *)payload, "christmas") == 0)
        {
            mqtt_client.publish(mqtt_reports_effect, "christmas");
            config_write_annimation(annimations::CHRISTMAS);
        }
    }
}

/*
void mqtt_sendfloat(const char* topic,float value) {
    char result[7];
    dtostrf(value, 4, 2, result);
    mqtt_client.publish(topic, result);
}*/

void mqtt_reportTemperature(float value)
{
    mqtt_client.publish(mqtt_reports_temp, String(value).c_str());
}

void mqtt_reportConfig()
{
    mqtt_client.publish(mqtt_reports_on_off_all, config_read_background_on() && config_read_time_on() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_on_off_back, config_read_background_on() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_on_off_time, config_read_time_on() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_brightness, String(config_read_brightness()).c_str());
    mqtt_client.publish(mqtt_reports_hue, String((map(config_read_color_hue(), 0, 255, 0, 360))).c_str());
    mqtt_client.publish(mqtt_reports_sat, String((map(config_read_color_sat(), 0, 255, 0, 100))).c_str());
    /*
        mqtt_client.publish(mqtt_reports_huesat,(
                                    String(map(config_read_color_hue(),0,255,0,360)) +","+ String(map(config_read_color_saturation(),0,255,0,100))
        ).c_str());*/

    switch (config_read_annimation())
    {
        case STARTUP_START:
        case STARTUP_WIFI:
            break;
        case COLORFADE:
            mqtt_client.publish(strcat(clientid, mqtt_reports_effect), "color_fade");
            break;
        case BREATHING:
            mqtt_client.publish(strcat(clientid, mqtt_reports_effect), "breathing");
            break;
        case CHRISTMAS:
            mqtt_client.publish(strcat(clientid, mqtt_reports_effect), "christmas");
            break;
    }
}

void mqtt_loop()
{
    if (!mqtt_client.connected()){
        mqtt_reconnect();
    }

    mqtt_client.loop();
}
