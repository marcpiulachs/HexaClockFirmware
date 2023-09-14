#include "usb_power.h"

void UsbPower::begin()
{
}

float AnalogReadV(int pin)
{
    // By default we have 11db (1/3.6) attenuation with 1.1V reference,
    // so full scale voltage range is 1.1*3.6 = 3.96. In reality it's
    // clamped to Vdd (3.3V) so we will never get a reading above that,
    // but we need to the calculations using 3.96.
    return analogRead(pin) * 3.96f / 4096;
}

UsbCurrentAvailable DetermineMaxCurrent()
{
    // This function implements USB-C current advertisement detection.
    // Universal Serial Bus Type-C Cable and Connector Specification
    // Depending on cable orientation, either CC1 or CC2 will be >0V,
    // and that tells us how much current we can draw.
    // Voltage thresholds from Table 4-36:
    // >0.2V = connected, >0.66V = 1.5A, >1.23V = 3A.
    float cc1 = AnalogReadV(kUsbCc1Pin);
    float cc2 = AnalogReadV(kUsbCc2Pin);
    float cc = max(cc1, cc2);
    if (cc > 1.23f)
    {
        return UsbCurrentAvailable::k3A;
    }
    else if (cc > 0.66f)
    {
        return UsbCurrentAvailable::k1_5A;
    }
    else
    {
        return UsbCurrentAvailable::kUsbStd;
    }
}

void UsbPower::loop()
{
    static UsbCurrentAvailable current_available =
        UsbCurrentAvailable::kUsbStd;
    UsbCurrentAvailable current_advertisement = DetermineMaxCurrent();
    if (current_available != current_advertisement)
    {
        // Wait 15ms and read again to make sure it's stable (not a PD message). See comment below
        // for more details.
        delay(15);
        if (DetermineMaxCurrent() == current_advertisement)
        {
            switch (current_advertisement)
            {
            case UsbCurrentAvailable::k3A:
                digitalWrite(kOnboardLed0Pin, HIGH);
                digitalWrite(kOnboardLed1Pin, HIGH);
                brightness = (255 * (3.0f - kMaxIdleCurrent) / kMatrixMaxCurrent);
                EnableLEDPower();
                break;
            case UsbCurrentAvailable::k1_5A:
                digitalWrite(kOnboardLed0Pin, LOW);
                digitalWrite(kOnboardLed1Pin, HIGH);
                brightness = (255 * (1.5f - kMaxIdleCurrent) / kMatrixMaxCurrent);
                EnableLEDPower();
                break;
            default:
                digitalWrite(kOnboardLed0Pin, LOW);
                digitalWrite(kOnboardLed1Pin, LOW);
                DisableLEDPower();
            }
            current_available = current_advertisement;
        }
    }
}

void UsbPower::EnableLEDPower()
{
    // Make sure data pin is low so we don't latch up the LEDs.
    digitalWrite(kLedMatrixDataPin, LOW);

    // Enable 1.5A current to charge up the capacitances.
    digitalWrite(kLedMatrixPowerPin0, HIGH);

    delay(50 /* milliseconds */);

    // Enable the second 1.5A switch to reduce switch resistance
    // even if we only have 1.5A total, because we can limit it in
    // firmware instead.
    digitalWrite(kLedMatrixPowerPin1, HIGH);
}

void UsbPower::DisableLEDPower()
{
    digitalWrite(kLedMatrixDataPin, LOW);
    digitalWrite(kLedMatrixPowerPin1, LOW);
    digitalWrite(kLedMatrixPowerPin0, LOW);
}

uint8_t UsbPower::getBrightness()
{
    return this->brightness;
}