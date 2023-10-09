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
    
      pinMode(25, OUTPUT);    // sets the digital pin 13 as output
  pinMode(33, OUTPUT);    // sets the digital pin 13 as output
  pinMode(26, OUTPUT);    // sets the digital pin 13 as output
  pinMode(12, OUTPUT);    // sets the digital pin 13 as output


    digitalWrite(25, HIGH);
        digitalWrite(33, HIGH);
      
    // Enable 1.5A current to charge up the capacitances.
    digitalWrite(26, HIGH);

    delay(50 /* milliseconds */);

    // Enable the second 1.5A switch to reduce switch resistance
    // even if we only have 1.5A total, because we can limit it in
    // firmware instead.
    digitalWrite(12, HIGH);

    // Make sure data pin is low so we don't latch up the LEDs.
    digitalWrite(DATA_PIN, LOW);

    Serial.begin(9600);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(output_buffer, NUM_LEDS);
    FastLED.setBrightness(20);
    //FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);

    
    // Enable 1.5A current to charge up the capacitances.
    digitalWrite(26, HIGH);

    delay(50 /* milliseconds */);

    // Enable the second 1.5A switch to reduce switch resistance
    // even if we only have 1.5A total, because we can limit it in
    // firmware instead.
    digitalWrite(12, HIGH);
    
    delay(1000);

    sensors.begin();
    mqtt_begin();
    config.begin(true);
    usbPower.begin();

    for (int i = 0; i < 10; ++i) {
        EVERY_N_MILLISECONDS( 30 ) {
            display.run(output_buffer);
            FastLED.show();
        }
    }

//        display.setAnnimation(annimations::STARTUP_START);
  //  delay(1000);
    display.setAnnimation(annimations::PROTON);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        display.run(output_buffer);
        FastLED.show();
        delay(30);
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    ntpClient.begin();
    ntpClient.update();
    setSyncProvider(getNTPTime);
    while(!forceTimeSync()) {
        EVERY_N_MILLISECONDS( 30 ) {
            display.run(output_buffer);
            FastLED.show();
        }
    }

    if (MDNS.begin("HexaClock")) {
        Serial.println("MDNS responder started");
    }

    display.setAnnimation(annimations::FISH);
}

void loop()
{
    /*
    // if condition checks if push button is pressed    
    int wifi_provisioning = digitalRead(0);

    // if pressed user wants to setup WiFi
    if ( wifi_provisioning == HIGH )
    {
        // Starts the wifi provisioning routine
        network.WiFiSetup();
    }*/

 Serial.println("running");

    //mqtt_loop();

    //usbPower.loop();

    EVERY_N_MINUTES(60) {
        ntpClient.update();
    }

/*
    EVERY_N_MINUTES(5) {
        mqtt_reportTemperature(sensors.getSensorTemp());
    }
*/
    EVERY_N_MILLISECONDS( 1000 ) {
        ntpClient.update();
    }

    EVERY_N_MILLISECONDS( 13 ) {

        uint8_t hue = config.getColorHue();
        uint8_t sat = config.getColorSat();
        uint8_t brightness = config.getBrightness();

        CHSV color = CHSV(hue, sat, brightness);

        display.setAnnimation(config.getAnimation());
        display.updateColor(color);

        if (config.getBackgroundOn())
        {
            display.run(animation_buffer);
        }
        else
        {
            // Turn off clock backgound
            fill_solid(animation_buffer, NUM_LEDS, CRGB::Black);
        }

        if (config.getTimeOn())
        {
            time_t time = now();
            // display_time( hour(time), minute(time), CRGB::Green, CRGB::Green, CRGB::Blue, CRGB::Blue);
            CRGB color = CRGB(150, 120, 170);
            display_time((hour(time) - 1) % 24, minute(time), color, color, color, color);
        }

        display2(config.getTimeOn());

        FastLED.show();
        FastLED.setBrightness(config.getBrightness());
    }
}
