//#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "stdint.h"
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
#include "annimation_manager.h"

UsbPower usbPower;
WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP, "europe.pool.ntp.org", 7200, 60000);

#define NUM_LEDS 96
#define DATA_PIN 5

sensors device_sensors(1);

CRGB time_buffer        [NUM_LEDS];
CRGB animation_buffer   [NUM_LEDS];
CRGB output_buffer      [NUM_LEDS];

const char* ssid;
const char* password;

const char* mqtt_user;
const char* mqtt_password;
const char* mqtt_host;

/*
ani_startup_sequence animation_startup;
ani_color_fade animation_color_fade(120);
ani_breathing animation_breathing(255,50,false,200);
ani_christmas animation_christmas(50,CRGB(255,0,100),CRGB(200,0,20));
*/
annimation_manager annimations_m;


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

    for(uint8_t i=0; i<10; i++) {
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

void display(bool draw_time) 
{
    for(int i=0; i<NUM_LEDS; i++) {
        if( (time_buffer[i].r == 0 && time_buffer[i].g == 0 && time_buffer[i].b == 0) || !draw_time) {
            output_buffer[i] = animation_buffer[i];
        } else {
            output_buffer[i] = time_buffer[i];
        }
    }
    FastLED.show();
}

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(output_buffer, NUM_LEDS);
    FastLED.setBrightness(255);
    //FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);

    delay(1000);

    device_sensors.begin();
    mqtt_begin();
    config_begin(true);
    usbPower.begin();

    for (int i = 0; i < 10; ++i) {
        EVERY_N_MILLISECONDS( 30 ) {
            annimations_m.run(output_buffer);
            FastLED.show();
        }
    }
    
    annimations_m.setAnnimation(annimations::STARTUP_WIFI);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        annimations_m.run(output_buffer);
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
            annimations_m.run(output_buffer);
            FastLED.show();
        }
    }

    if (MDNS.begin("HexClock")) {
        Serial.println("MDNS responder started");
    }

    annimations_m.setAnnimation(annimations::BREATHING);
}


void loop() {
    mqtt_loop();

    usbPower.loop();

    EVERY_N_MINUTES(60) {
        ntpClient.update();
    }

    //EVERY_N_MILLISECONDS( 5000 ) {
        //mqtt_sendfloat(mqtt_topics_send_temp1,device_sensors.getSensorTemp());
        //mqtt_sendfloat(mqtt_topics_send_temp2,device_sensors.getSensorTemp2());
    //}

    EVERY_N_MILLISECONDS( 1000 ) {
        ntpClient.update();
    }

    EVERY_N_MILLISECONDS( 13 ) {

        uint8_t hue = config_read_color_hue();
        uint8_t sat = config_read_color_sat();
        uint8_t brightness = config_read_brightness();

        CHSV color = CHSV(hue, sat, brightness);

        annimations_m.setAnnimation(config_read_annimation());
        annimations_m.updateColor(color);

        if (config_read_background_on())
        {
            annimations_m.run(animation_buffer);
        }
        else
        {
            // Turn off clock backgound
            fill_solid(animation_buffer, NUM_LEDS, CRGB::Black);
        }

        if (config_read_time_on())
        {
            time_t time = now();
            // display_time( hour(time), minute(time), CRGB::Green, CRGB::Green, CRGB::Blue, CRGB::Blue);
            CRGB color = CRGB(150, 120, 170);
            display_time((hour(time) - 1) % 24, minute(time), color, color, color, color);
        }

        display(config_read_time_on());
        FastLED.setBrightness(config_read_brightness());
    }
}
