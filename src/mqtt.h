//
// Created by samuel on 14/09/2020.
//

#ifndef _MQTT_FUNCTIONS_H
#define _MQTT_FUNCTIONS_H

#define DEBUG_HEXCLOCK
#define MSG_BUFFER_SIZE	128

#include <stdint.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include "secret.h"
#include "config.h"

extern const char* mqtt_topics;
extern const char* mqtt_topics_send_temp1;
extern const char* mqtt_topics_send_temp2;
extern const char* mqtt_topics_on_off_back;
extern const char* mqtt_topics_on_off_time;
extern const char* mqtt_topics_on_off_all;
extern const char* mqtt_topics_brightness;
//extern const char* mqtt_topics_huesat;
//extern const char* mqtt_reports_huesat;
extern const char* mqtt_topics_hue;
extern const char* mqtt_topics_sat;
extern const char* mqtt_topics_effect;

extern const char* mqtt_reports_hue;
extern const char* mqtt_reports_sat;

extern const char* mqtt_reports_on_off_all;
extern const char* mqtt_reports_on_off_back;
extern const char* mqtt_reports_on_off_time;
extern const char* mqtt_reports_brightness;
extern const char* mqtt_reports_effect;

extern WiFiClient espClient;
extern PubSubClient client;
extern Config config;

extern void mqtt_begin();
extern void mqtt_loop();

extern void mqtt_reportTemperature(float value);
extern void mqtt_callback(char* topic, byte* payload, unsigned int length);
extern void mqtt_reconnect();
extern void mqtt_reportConfig();

#endif //_MQTT_FUNCTIONS_H
