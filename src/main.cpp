#include "stdint.h"

#include <FastLED.h>
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

NTPClient ntpClient(ntpUDP, "europe.pool.ntp.org", 7200, 60000);

Sensors sensors(1);

/* WiFi credentials */
const char* ssid;
const char* password;

/* MQTT connection */
const char* mqtt_user;
const char* mqtt_pass;
const char* mqtt_host;

Display display;

time_t getNTPTime() {
    return ntpClient.getEpochTime();
}

bool forceTimeSync()  {
        Serial.print("Forcing time sync! ");
        ntpClient.forceUpdate();
        setSyncInterval(0);
        time_t time = now();
        setSyncInterval(300);
        const bool success = year(time) > 2019;
        Serial.println(success ? "Successful" : "Failed");
        return success;
}

void setup() {
    
    pinMode(32, OUTPUT);    // sets the digital pin 32 as output
    pinMode(33, OUTPUT);    // sets the digital pin 33 as output

    digitalWrite(32, HIGH);
    digitalWrite(33, HIGH);

    delay(100);

    pinMode(26, OUTPUT);    // sets the digital pin 26 as output
    pinMode(12, OUTPUT);    // sets the digital pin 12 as output
  
    // Enable 1.5A current to charge up the capacitances.
    digitalWrite(26, HIGH);

    delay(50 /* milliseconds */);

    // Enable the second 1.5A switch to reduce switch resistance
    // even if we only have 1.5A total, because we can limit it in
    // firmware instead.
    digitalWrite(12, HIGH);

    // Setup serial port
    Serial.begin(9600);
    Serial.println("HexaClock started");
    Serial.println();
    
    // Setup LED display
    display.setup();
    display.setAnnimation(annimations::STARTUP_START);
    display.setBrightness(config.config.brightness);

    //sensors.begin();

    config.begin(true);
    //usbPower.begin();

    mqtt_begin();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    //WiFi.begin("HDO_IoT", "Twister123");
    WiFi.begin("MiFibra-2D81", "jJAML2Mc");
    Serial.println("Conecting to WIFI:");

    /*
    while(!forceTimeSync()) {
        EVERY_N_MILLISECONDS( 30 ) {
            display.run(output_buffer);
            FastLED.show();
        }
    }
    */
}

void loop()
{   
    bool complete = wifi_connected && time_set && mqtt_connected;
    
    EVERY_N_SECONDS(1) 
    {
        // if condition checks if push button is pressed    
        int wifi_provisioning = digitalRead(0);

        // if pressed user wants to setup WiFi
        if ( wifi_provisioning == LOW )
        {
            switch(state)
            {
                case NORMAL:
                    state = ani_startup_state::WIFI_SETUP;
                    break;
                case WIFI_SETUP:
                    state = ani_startup_state::BLUETOOTH_SETUP;
                    break;
                case BLUETOOTH_SETUP:
                    state = ani_startup_state::NORMAL;
                    break;
            }

            Serial.print("Button Press");
            Serial.println();
            // Starts the wifi provisioning routine
            //network.WiFiSetup();
        }
    }

    // Wait for connection
    if (WiFi.status() != WL_CONNECTED)
    {
        // Wifi is not connected
        wifi_connected = false;

        // Wifi connecting
        //Serial.print('.');
    }
    else
    {
        if (!wifi_connected)
        {
            Serial.println("");
            Serial.print("Connected to ");
            Serial.println(ssid);
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            wifi_connected = true;
        }

        if (!time_set)
        {    
            ntpClient.begin();
            ntpClient.update();
            setSyncProvider(getNTPTime);
            time_set = true;
        }

        if (!mqtt_client.connected())
        {
            mqtt_connected = false;
            EVERY_N_SECONDS(10) {
                mqtt_reconnect();
            }
        }
        else
        {
            if (!mqtt_connected)
            {
                Serial.print("MQTT Connected");
                mqtt_connected = true;
            }

            mqtt_client.loop();
        }
    }

    if (time_set)
    {
        EVERY_N_MINUTES(60) {
            ntpClient.update();
        }
    }

    if(state == ani_startup_state::NORMAL)
    {
        if (complete)
        {
            display.setAnnimation((annimations)config.config.animation);
            display.setSpeed(config.config.speed);
            display.setTime(config.config.time);
            display.setBrightness(config.config.brightness);
            display.setBackground(config.config.background);
            display.setInvert(config.config.invert);
        }
        else
        {
            display.setAnnimation(annimations::STARTUP_START);
        }
    }
    else if (state == ani_startup_state::WIFI_SETUP)
    {
        display.setAnnimation(annimations::SETUP_WIFI);
    }
    else if (state == ani_startup_state::BLUETOOTH_SETUP)
    {
        display.setAnnimation(annimations::SETUP_BLUETOOTH);
    }
    
    display.draw();
}
