//#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include "stdint.h"
#include <NTPClient.h>
#include <TimeLib.h>
#include <WiFiUdp.h>

#include "secret.h"
#include "graphics.h"
#include "animations/ani_startup_sequence.h"
#include <animations/ani_color_fade.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7200, 60000);

#define NUM_LEDS 96
#define DATA_PIN D5

CRGB time_buffer[NUM_LEDS];
CRGB annimation_buffer[NUM_LEDS];
CRGB output_buffer[NUM_LEDS];

ani_startup_sequence animation_startup;
ani_color_fade animation_color_fade(120);

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
void display() {
    time_t time = now();
    display_time( hour(time), minute(time), CRGB::Green, CRGB::Green, CRGB::Blue, CRGB::Blue);

    for(int i=0; i<NUM_LEDS; i++) {
        if(time_buffer[i].r == 0 && time_buffer[i].g == 0 && time_buffer[i].b == 0) {
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

    for (int i = 0; i < 10; ++i) {
        EVERY_N_MILLISECONDS( 30 ) {
            animation_startup.run(output_buffer);
            FastLED.show();
        }
    }
    animation_startup.setState(ani_startup_state::WIFI);


    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        animation_startup.run(output_buffer);
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
            animation_startup.run(output_buffer);
            FastLED.show();
        }
    }

    if (MDNS.begin("HexClock")) {
        Serial.println("MDNS responder started");
    }

    animation_color_fade.set_speed(10);
}

void loop() {
    EVERY_N_MILLISECONDS( 1000 ) {
        timeClient.update();
    }

    EVERY_N_MILLISECONDS( 13 ) {
        animation_color_fade.run(annimation_buffer);
        display();
    }
}
