//
// Created by samuel on 14/09/2020.
//

#include "mqtt_functions.h"

const char* mqtt_topics = "hexclock/#";
const char* mqtt_topics_send_temp1 = "hexclock/sensors/temp1";
const char* mqtt_topics_send_temp2 = "hexclock/sensors/temp2";
const char* mqtt_topics_on_off_back = "hexclock/onoff/background";
const char* mqtt_topics_on_off_time = "hexclock/onoff/time";
const char* mqtt_topics_brightness = "hexclock/brightness";

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
        config_write_background_on(  strcmp((char *)payload,"on")==0  );
    }
    if(strcmp(topic,mqtt_topics_on_off_time) == 0) {
        config_write_time_on(  strcmp((char *)payload,"on")==0  );
    }
    if(strcmp(topic,mqtt_topics_brightness) == 0) {
        config_write_brightness(  atoi( (char *)payload ) );
    }
}

void mqtt_sendfloat(const char* topic,float value) {
    char result[7];
    dtostrf(value, 4, 2, result);
    mqtt_client.publish(topic, result);
}

void mqtt_loop() {
    if (!mqtt_client.connected()) {
        mqtt_reconnect();
    }
    mqtt_client.loop();
}
