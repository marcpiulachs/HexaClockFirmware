#ifndef HEXCLOCK_USBPOWER_H
#define HEXCLOCK_USBPOWER_H
#define DEBUG_HEXCLOCK

#include <Arduino.h>

enum class UsbCurrentAvailable {
  // USB-C host and we can draw 3A.
  k3A,
 
  // USB-C host and we can draw 1.5A.
  k1_5A,
 
  // We have either a USB-C host with no high current
  // capability or a legacy host / 1.5A (BCS) power supply. We do
  // not have the hardware to tell them apart, so we
  // can't make any assumptions on current available
  // beyond 100mA (though most hosts will be fine with 500mA).
  kUsbStd,
};

constexpr int kUsbCc1Pin = 36;
constexpr int kUsbCc2Pin = 39;

// These are enable lines for the matrix power switch.
// If only Pin0 is high, the matrix is current-limited to 1.5A.
// If both are high, the matrix is current-limited to 3A.
// The switch resistance is lower with both enabled, so we always
// enable Pin0 first to charge up the capacitances (since we may
// only be allowed 1.5A), then enable Pin1 even if we only have
// 1.5A available to improve switch efficiency, and apply current
// limit in firmware instead (not setting LEDs too bright).
constexpr int kLedMatrixPowerPin0 = 12;
constexpr int kLedMatrixPowerPin1 = 26;

constexpr int kOnboardLed0Pin = 32;
constexpr int kOnboardLed1Pin = 33;

constexpr int kMatrixSize = 96;

constexpr float kMatrixMaxCurrent = kMatrixSize * 0.06f; // WS2812B: 60mA/LED
constexpr float kMaxIdleCurrent = 0.5f; // Matrix + ESP32 idle

constexpr int kLedMatrixDataPin = 27;

//static UsbCurrentAvailable current_available = UsbCurrentAvailable::kUsbStd;

class UsbPower {
    public:
        UsbPower() = default;
        void begin();
        void loop();

        uint8_t getMaxBrightness();
        float AnalogReadV(int pin);
        UsbCurrentAvailable DetermineMaxCurrent();
    private:        
      void EnableLEDPower();
      void DisableLEDPower();
      uint8_t brightness;
};


#endif //HEXCLOCK_USBPOWER_H
