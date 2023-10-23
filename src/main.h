#include "stdint.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <OneWire.h>

#include "secret.h"
#include "graphics.h"
#include "sensors.h"
#include "usb.h"
#include "mqtt.h"
#include "config.h"
#include "display.h"
#include "network.h"
#include "config.h"

enum ani_startup_state {
    NORMAL,
    WIFI_SETUP,
    BLUETOOTH_SETUP
} typedef ani_startup_state;

ani_startup_state state = ani_startup_state::NORMAL;

bool wifi_connected = false;
bool time_set = false;
bool mqtt_connected = false;

Config config;
Network network;
UsbPower usbPower;
WiFiUDP ntpUDP;
Display display;

NTPClient ntpClient(ntpUDP, "europe.pool.ntp.org", 7200, 60000);

Sensors sensors(1);

/* WiFi credentials */
const char* ssid;
const char* password;

/* MQTT connection */
const char* mqtt_user;
const char* mqtt_pass;
const char* mqtt_host;
