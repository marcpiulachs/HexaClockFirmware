//
// Created by samuel on 14/09/2020.
//

#ifndef HEXCLOCK_MQTT_FUNCTIONS_H
#define HEXCLOCK_MQTT_FUNCTIONS_H

#define DEBUG_HEXCLOCK
#define MSG_BUFFER_SIZE	128

#include <stdint.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include "secret.h"
#include "eeprom_functions.h"

extern const char* mqtt_topics;
extern const char* mqtt_topics_send_temp1;
extern const char* mqtt_topics_send_temp2;
extern const char* mqtt_topics_on_off_back;
extern const char* mqtt_topics_on_off_time;
extern const char* mqtt_topics_on_off_all;
extern const char* mqtt_topics_brightness;
extern const char* mqtt_topics_huesat;
extern const char* mqtt_reports_huesat;
extern const char* mqtt_topics_effet;

extern const char* mqtt_reports_on_off_all;
extern const char* mqtt_reports_on_off_back;
extern const char* mqtt_reports_on_off_time;
extern const char* mqtt_reports_brightness;
extern const char* mqtt_reports_effet;

extern WiFiClient espClient;
extern PubSubClient client;

extern void mqtt_begin();
extern void mqtt_loop();

extern void mqtt_sendfloat(const char* topic,float value);
extern void mqtt_callback(char* topic, byte* payload, unsigned int length);
extern void mqtt_reconnect();
extern void mqtt_report_current_config();

#endif //HEXCLOCK_MQTT_FUNCTIONS_H
