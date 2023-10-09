#ifndef _NETWORK_H
#define _NETWORK_H

#define DEBUG_HEXCLOCK

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <WiFi.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

class Network {
    public:
        Network () = default;
        void WiFiSetup();
    private:
        String bufferReceive = "";
        BluetoothSerial SerialBT;
};


#endif //_NETWORK_H
