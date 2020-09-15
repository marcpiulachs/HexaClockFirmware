//#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "stdint.h"
#include <NTPClient.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <OneWire.h>

#include "secret.h"
#include "graphics.h"
#include "sensors.h"
#include "mqtt_functions.h"
#include "eeprom_functions.h"
#include "annimation_manager.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7200, 60000);

#define NUM_LEDS 96
#define DATA_PIN D5

sensors device_sensors(2);

CRGB time_buffer[NUM_LEDS];
CRGB annimation_buffer[NUM_LEDS];
CRGB output_buffer[NUM_LEDS];

/*
ani_startup_sequence animation_startup;
ani_color_fade animation_color_fade(120);
ani_breathing animation_breathing(255,50,false,200);
ani_christmas animation_christmas(50,CRGB(255,0,100),CRGB(200,0,20));
*/
annimation_manager annimations_m;


time_t getNTPTime() {
    return timeClient.getEpochTime();
}
bool forceTimeSync()  {
        Serial.print("Forcing time sync! ");
        timeClient.forceUpdate();
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
void display(bool draw_time) {
    for(int i=0; i<NUM_LEDS; i++) {
        if( (time_buffer[i].r == 0 && time_buffer[i].g == 0 && time_buffer[i].b == 0) || !draw_time) {
            output_buffer[i] = annimation_buffer[i];
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

    timeClient.begin();
    timeClient.update();
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

    EVERY_N_MILLISECONDS( 5000 ) {
        timeClient.update();
        mqtt_sendfloat(mqtt_topics_send_temp1,device_sensors.getSensorTemp1());
        mqtt_sendfloat(mqtt_topics_send_temp2,device_sensors.getSensorTemp2());
    }

    EVERY_N_MILLISECONDS( 1000 ) {
        timeClient.update();
    }

    EVERY_N_MILLISECONDS( 13 ) {
        annimations_m.setAnnimation(config_read_annimation());
        annimations_m.updateColorForCurrentAnimation(CHSV(config_read_color_hue(),config_read_color_saturation(),config_read_brightness()));

        if(config_read_background_on()) {
            annimations_m.run(annimation_buffer);
        } else {
            fill_solid(annimation_buffer,NUM_LEDS,CRGB::Black);
        }
        if(config_read_time_on()) {
            time_t time = now();
            //display_time( hour(time), minute(time), CRGB::Green, CRGB::Green, CRGB::Blue, CRGB::Blue);
            CRGB color = CRGB(150,120,170);
            display_time( hour(time), minute(time), color, color, color, color);
        }

        display(config_read_time_on());
        FastLED.setBrightness(config_read_brightness());
    }
}
