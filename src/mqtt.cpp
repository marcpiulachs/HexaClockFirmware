//
// Created by samuel on 14/09/2020.
//

#include "mqtt.h"
#include "esp_system.h"

const char* mqtt_topics              = "hexclock/#";
//const char* mqtt_topics_send_temp    = "hexclock/sensors/temp";
const char* mqtt_topics_on_off_back  = "hexclock/onoff/back";
const char* mqtt_topics_on_off_time  = "hexclock/onoff/time";
const char* mqtt_topics_on_off_temp  = "hexclock/onoff/temp";
const char* mqtt_topics_on_off_alarm = "hexclock/onoff/alarm";
const char* mqtt_topics_on_off_all   = "hexclock/onoff/all";
const char* mqtt_topics_brightness   = "hexclock/brightness";
const char* mqtt_topics_hue          = "hexclock/hue";
const char* mqtt_topics_sat          = "hexclock/sat";
const char* mqtt_topics_effect       = "hexclock/effect";

const char* mqtt_reports_on_off_all   = "hexclock/reports/onoff/all";
const char* mqtt_reports_on_off_back  = "hexclock/reports/onoff/background";
const char* mqtt_reports_on_off_time  = "hexclock/reports/onoff/time";
const char* mqtt_reports_on_off_temp  = "hexclock/reports/onoff/temp";
const char* mqtt_reports_on_off_alarm = "hexclock/reports/onoff/alarm";
const char* mqtt_reports_brightness   = "hexclock/reports/brightness";
const char* mqtt_reports_temp         = "hexclock/reports/temp";
//const char* mqtt_reports_huesat      = "hexclock/reports/hue";
const char* mqtt_reports_hue          = "hexclock/reports/hue";
const char* mqtt_reports_sat          = "hexclock/reports/sat";
const char* mqtt_reports_effect       = "hexclock/reports/effect";

WiFiClient mqtt_wifi_client;
PubSubClient mqtt_client(mqtt_wifi_client);

String getUniqueId() 
{
	uint8_t baseMac[6];
	// Get MAC address for WiFi station
	esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
	char baseMacChr[18] = {0};
	sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
	return String(baseMacChr);
}

void mqtt_begin()
{
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

        char chipId[64];
        snprintf(chipId, 64, "HexClock-%llX", ESP.getEfuseMac());

        String clientId = "HexClock-" + getUniqueId();
        // const char* clientId2 = "HexaClock-" + ESP.ESP_getFlashChipId();

        if (mqtt_client.connect(clientId.c_str(), mqtt_user, mqtt_password))
        {
            Serial.println("Connected to MQTT");

            mqtt_client.publish("discover/advertise", clientId.c_str());
            mqtt_reportConfig();

            mqtt_client.subscribe(mqtt_topics);
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

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    payload[length] = '\0';

    if (strcmp(topic, mqtt_topics_on_off_back) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config_write_background_on(on);
        mqtt_client.publish(mqtt_reports_on_off_back, on ? "on" : "off");
    }
    if (strcmp(topic, mqtt_topics_on_off_time) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config_write_time_on(on);
        mqtt_client.publish(mqtt_reports_on_off_time, on ? "on" : "off");
    }
    if (strcmp(topic, mqtt_topics_on_off_alarm) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config_write_alarm_on(on);
        mqtt_client.publish(mqtt_reports_on_off_alarm, on ? "on" : "off");
    }
    if (strcmp(topic, mqtt_topics_on_off_temp) == 0)
    {
        bool on = strcmp((char *)payload, "on") == 0;
        config_write_temp_on(on);
        mqtt_client.publish(mqtt_reports_on_off_temp, on ? "on" : "off");
    }
    if(strcmp(topic,mqtt_topics_on_off_all) == 0) 
    {
        bool on = strcmp((char *)payload,"on")==0;
        
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
    if(strcmp(topic,mqtt_topics_brightness) == 0) 
    {
        uint8_t brightness = atoi( (char *)payload );
        config_write_brightness( brightness );
        mqtt_client.publish(mqtt_reports_brightness, String(brightness).c_str());
        if (brightness > 0)
        {
            mqtt_client.publish(mqtt_reports_on_off_time, "on");
        }
    }
    if (strcmp(topic, mqtt_topics_hue) == 0)
    {
        float hue = atoi( (char *)payload );
        int hue_int = map((int)hue, 0, 360, 0, 255);
        mqtt_client.publish(mqtt_reports_hue, String(hue_int).c_str());
        config_write_color_hue((uint8_t)hue_int);
    }
    if (strcmp(topic, mqtt_topics_sat) == 0)
    {
        float sat = atoi( (char *)payload );
        int sat_int = map((uint8_t)sat, 0, 100, 0, 255);
        mqtt_client.publish(mqtt_reports_sat, String(sat_int).c_str());
        config_write_color_sat((uint8_t)sat_int);
    }
    /*
    if (strcmp(topic, mqtt_topics_huesat) == 0)
    {
        float hue = 0;
        float sat = 0;

        sscanf((char *)payload, "%f,%f", &hue, &sat);
        mqtt_client.publish(mqtt_reports_huesat, (String((uint8_t)hue) + "," + String((uint8_t)sat)).c_str());

        int hue_int = map((int)hue, 0, 360, 0, 255);
        config_write_color_hue((uint8_t)hue_int);

        int sat_int = map((uint8_t)sat, 0, 100, 0, 255);
        config_write_color_sat((uint8_t)sat_int);
    }*/
    if (strcmp(topic, mqtt_topics_effect) == 0)
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

void mqtt_reportConfig() {

    mqtt_client.publish(mqtt_reports_on_off_all, config_read_background_on()&&config_read_time_on() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_on_off_back,config_read_background_on() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_on_off_time,config_read_time_on() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_brightness, String(config_read_brightness()).c_str());
    mqtt_client.publish(mqtt_reports_hue,String((map(config_read_color_hue(),0,255,0,360))).c_str());
    mqtt_client.publish(mqtt_reports_sat,String((map(config_read_color_sat(),0,255,0,100))).c_str());
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
            mqtt_client.publish(mqtt_reports_effect, "color_fade");
            break;
        case BREATHING:
            mqtt_client.publish(mqtt_reports_effect, "breathing");
            break;
        case CHRISTMAS:
            mqtt_client.publish(mqtt_reports_effect,"christmas");
            break;
    }
}

void mqtt_loop()
{
    if (!mqtt_client.connected())
    {
            mqtt_reconnect();
    }
    mqtt_client.loop();
}
