#ifndef _MQTT_H
#define _MQTT_H

#define DEBUG_HEXCLOCK
#define MSG_BUFFER_SIZE	128

#include <stdint.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include "secret.h"
#include "config.h"
#include "sensors.h"
#include "sound.h"

#define def_mqtt_all_topic              "%s/#"
#define def_mqtt_topics_on_off_power    "%s/power"
#define def_mqtt_topics_on_off_back     "%s/background"
#define def_mqtt_topics_on_off_time     "%s/clock"
#define def_mqtt_topics_on_off_temp     "%s/temp"
#define def_mqtt_topics_on_off_alarm    "%s/alarm"
#define def_mqtt_topics_brightness      "%s/brightness"
//#define def_mqtt_topics_invert = "/invert";
//#define def_mqtt_topics_hue = "/hue";
//#define def_mqtt_topics_sat = "/sat";
#define def_mqtt_topics_effect          "%s/effect"
#define def_mqtt_topics_speed           "%s/speed"
#define def_mqtt_topics_temp            "%s/temp"
//#define def_mqtt_topics_alarm_hour = "/alarm/hour";
//#define def_mqtt_topics_alarm_minute = "/alarm/minute";
#define def_mqtt_topics_time_hour       "%s/time/hour"
#define def_mqtt_topics_time_minute     "%s/time/minute"
//#define def_mqtt_topics_time_sync = "/time/sync";

#define def_mqtt_reports_on_off_power   "%s/reports/onoff/power"
#define def_mqtt_reports_on_off_back    "%s/reports/onoff/background"
#define def_mqtt_reports_on_off_time    "%s/reports/onoff/time"
#define def_mqtt_reports_on_off_temp    "%s/reports/onoff/temp"
#define def_mqtt_reports_on_off_alarm   "%s/reports/onoff/alarm"
#define def_mqtt_reports_brightness     "%s/reports/brightness"
#define def_mqtt_reports_temp           "%s/reports/temp"
#define def_mqtt_reports_time           "%s/reports/time"
//#define def_mqtt_reports_hue = "/reports/hue";
//#define def_mqtt_reports_sat = "/reports/sat";
#define def_mqtt_reports_effect         "%s/reports/effect"
#define def_mqtt_reports_speed          "%s/reports/speed"

extern WiFiClient espClient;
extern PubSubClient mqtt_client;
extern Config config;
extern Sensors sensors;
extern Sound sound;

extern void mqtt_begin();
extern void mqtt_loop();

void create_mqtt_client_id();
void create_mqtt_topics();

extern void mqtt_reportTemperature(float value);
extern void mqtt_callback(char* topic, byte* payload, unsigned int length);
extern void mqtt_reconnect();
extern void mqtt_report_config();

void mqtt_report_temp();
void mqtt_report_speed();
void mqtt_report_alarm_on();
void mqtt_report_temp_on();
void mqtt_report_on();
void mqtt_report_brightness();
void mqtt_report_time_on();
void mqtt_report_background_on();
void mqtt_report_animation();

#endif //_MQTT_H
