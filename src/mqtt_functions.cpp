//
// Created by samuel on 14/09/2020.
//

#include "mqtt_functions.h"

const char* mqtt_topics             = "hexclock/#";
const char* mqtt_topics_send_temp1  = "hexclock/sensors/temperature";
const char* mqtt_topics_send_temp2  = "hexclock/sensors/temp2";
const char* mqtt_topics_on_off_back = "hexclock/onoff/background";
const char* mqtt_topics_on_off_time = "hexclock/onoff/time";
const char* mqtt_topics_on_off_all  = "hexclock/onoff/all";
const char* mqtt_topics_brightness  = "hexclock/brightness";
const char* mqtt_topics_huesat      = "hexclock/hue";
const char* mqtt_topics_effect      = "hexclock/effect";

const char* mqtt_reports_on_off_all  = "hexclock/reports/onoff/all";
const char* mqtt_reports_on_off_back = "hexclock/reports/onoff/background";
const char* mqtt_reports_on_off_time = "hexclock/reports/onoff/time";
const char* mqtt_reports_brightness  = "hexclock/reports/brightness";
const char* mqtt_reports_huesat      = "hexclock/reports/hue";
const char* mqtt_reports_effect      = "hexclock/reports/effect";

WiFiClient mqtt_wifi_client;
PubSubClient mqtt_client(mqtt_wifi_client);

void mqtt_begin() {
    mqtt_client.setServer(mqtt_host, 1883);
    mqtt_client.setCallback(mqtt_callback);
}

void mqtt_reconnect() {
    Serial.println("mqtt_reconnect");
    delay(100);
    while (!mqtt_client.connected()) {
        Serial.println("Attempting MQTT connection...");

        String clientId = "HexClock-" + String(random(0xffff), HEX);
        if (mqtt_client.connect(clientId.c_str(),mqtt_user, mqtt_password)) {
            Serial.println("Connected to mqtt");

            mqtt_client.publish("discover/advertise", clientId.c_str());
            mqtt_report_current_config();

            mqtt_client.subscribe(mqtt_topics);
        } else {
            Serial.print("Failed to connect to mqtt server rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';

    if(strcmp(topic,mqtt_topics_on_off_back) == 0) {
        bool x = strcmp((char *)payload,"on")==0;
        config_write_background_on(  x  );
        mqtt_client.publish(mqtt_reports_on_off_back, x ? "on" : "off");
    }
    if(strcmp(topic,mqtt_topics_on_off_time) == 0) {
        bool x = strcmp((char *)payload,"on")==0;
        config_write_time_on(x);
        mqtt_client.publish(mqtt_reports_on_off_time, x ? "on" : "off");
    }
    if(strcmp(topic,mqtt_topics_on_off_all) == 0) {
        bool x = strcmp((char *)payload,"on")==0;
        config_write_time_on(x);
        config_write_background_on(x);
        mqtt_client.publish(mqtt_reports_on_off_all, x ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_back, x ? "on" : "off");
        mqtt_client.publish(mqtt_reports_on_off_time, x ? "on" : "off");
    }
    if(strcmp(topic,mqtt_topics_brightness) == 0) {
        uint8_t x = atoi( (char *)payload );
        config_write_brightness( x );
        mqtt_client.publish(mqtt_reports_brightness, String(x).c_str());
        if(x>0) {
            mqtt_client.publish(mqtt_reports_on_off_time, "on");
        }
    }
    if (strcmp(topic, mqtt_topics_huesat) == 0)
    {
        float hue = 0;
        float sat = 0;

        sscanf((char *)payload, "%f,%f", &hue, &sat);
        mqtt_client.publish(mqtt_reports_huesat, (String((uint8_t)hue) + "," + String((uint8_t)sat)).c_str());

        int hue_int = map((int)hue, 0, 360, 0, 255);
        config_write_color_hue((uint8_t)hue_int);

        int sat_int = map((uint8_t)sat, 0, 100, 0, 255);
        config_write_color_saturation((uint8_t)sat_int);
    }
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

void mqtt_sendfloat(const char* topic,float value) {
    char result[7];
    dtostrf(value, 4, 2, result);
    mqtt_client.publish(topic, result);
}

void mqtt_report_current_config() {

    mqtt_client.publish(mqtt_reports_on_off_all, config_read_background_on()&&config_read_time_on() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_on_off_back,config_read_background_on() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_on_off_time,config_read_time_on() ? "on" : "off");
    mqtt_client.publish(mqtt_reports_brightness, String(config_read_brightness()).c_str());
    mqtt_client.publish(mqtt_reports_huesat,(
                                String(map(config_read_color_hue(),0,255,0,360)) +","+ String(map(config_read_color_saturation(),0,255,0,100))
    ).c_str());

    switch (config_read_annimation()) {
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

void mqtt_loop() {
    if (!mqtt_client.connected()) {
        mqtt_reconnect();
    }
    mqtt_client.loop();
}
