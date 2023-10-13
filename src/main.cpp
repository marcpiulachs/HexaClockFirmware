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

#define NUM_LEDS 96
#define DATA_PIN 27

Sensors sensors(1);

CRGB time_buffer        [NUM_LEDS];
CRGB animation_buffer   [NUM_LEDS];
CRGB output_buffer      [NUM_LEDS];

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

void display_time(int hour, int minutes, const CRGB& color_minutes_a, const CRGB& color_minutes_b, const CRGB& color_hours_a, const CRGB& color_hours_b) {
    uint16_t digitHour0 = font[hour/10];
    uint16_t digitHour1 = font[hour%10];
    uint16_t digitMinutes0 = font[minutes/10];
    uint16_t digitMinutes1 = font[minutes%10];

    for(uint8_t i=0; i<10; i++) 
    {
        if((digitHour0 >> (15-i)) & 0x01)
            time_buffer[ font_position[0][i] ] = color_hours_a;
        else
            time_buffer[ font_position[0][i] ] = CRGB::Black;

        if((digitHour1 >> (15-i)) & 0x01)
            time_buffer[ font_position[1][i] ] = color_hours_b;
        else
            time_buffer[ font_position[1][i] ] = CRGB::Black;


        if((digitMinutes0 >> (15-i)) & 0x01)
            time_buffer[ font_position[2][i] ] = color_minutes_a;
        else
            time_buffer[ font_position[2][i] ] = CRGB::Black;

        if((digitMinutes1 >> (15-i)) & 0x01)
            time_buffer[ font_position[3][i] ] = color_minutes_b;
        else
            time_buffer[ font_position[3][i] ] = CRGB::Black;
    }
}

void display2(bool draw_time) 
{
    for(int i=0; i<NUM_LEDS; i++) {
        if( (time_buffer[i].r == 0 && time_buffer[i].g == 0 && time_buffer[i].b == 0) || !draw_time) {
            output_buffer[i] = animation_buffer[i];
        } else {
            output_buffer[i] = time_buffer[i];
        }
    }
}

void setup() {
    
    pinMode(32, OUTPUT);    // sets the digital pin 32 as output
    pinMode(33, OUTPUT);    // sets the digital pin 33 as output

    digitalWrite(32, HIGH);
    digitalWrite(33, HIGH);

    pinMode(26, OUTPUT);    // sets the digital pin 26 as output
    pinMode(12, OUTPUT);    // sets the digital pin 12 as output
  
    // Enable 1.5A current to charge up the capacitances.
    digitalWrite(26, HIGH);

    delay(50 /* milliseconds */);

    // Enable the second 1.5A switch to reduce switch resistance
    // even if we only have 1.5A total, because we can limit it in
    // firmware instead.
    digitalWrite(12, HIGH);

    // Make sure data pin is low so we don't latch up the LEDs.
    digitalWrite(DATA_PIN, LOW);

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(output_buffer, NUM_LEDS);
    FastLED.setBrightness(20);
    FastLED.clear(true);
    
    Serial.begin(9600);
    sensors.begin();

    config.begin(true);
    usbPower.begin();

    mqtt_begin();
    
    display.setAnnimation(annimations::STARTUP_START);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin("HDO_IoT", "Twister123");
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
        Serial.print('.');
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
            display.setAnnimation(annimations::WOPR);
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

    EVERY_N_MILLISECONDS((config.config.speed * 10)) 
    {
       // Serial.println("RenderFrame");
        //Serial.println(config.config.speed * 10);
        //Serial.println();

        uint8_t hue = config.getColorHue();
        uint8_t sat = config.getColorSat();
        uint8_t brightness = config.getBrightness();

        CHSV color = CHSV(hue, sat, brightness);

        if (config.getBackgroundOn())
        {
            display.run(animation_buffer);
        }
        else
        {
            // Turn off clock backgound
            fill_solid(animation_buffer, NUM_LEDS, CRGB::Black);
        }

        if (config.getTimeOn() && complete)
        {
            time_t time = now();
            CRGB color = CRGB(150, 120, 170);
            display_time(hour(time) % 24, minute(time), color, color, color, color);
        }

        display2(true);
        
        FastLED.show();
        FastLED.setBrightness(config.config.brightness);
    } 
}
