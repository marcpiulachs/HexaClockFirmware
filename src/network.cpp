
#include "network.h"

void Network::WiFiSetup()
{
  bool provisioning = true;

  // Turn off WiFi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Start the Bluetooth device
  SerialBT.begin("HexaClock");

  while(provisioning)
  {
    if (SerialBT.available()) {
      char c = SerialBT.read();
      if (c == '\n') {
        if (bufferReceive == "SCAN") {
          Serial.println("Starting WiFi scan");
          int nets = WiFi.scanNetworks();
          Serial.println("WiFi scan completed");
          SerialBT.println("WIFI_LIST_START");
          if (nets > 0) {
            for (int net = 0; net < nets; net++) {
              SerialBT.print(WiFi.SSID(net));
              SerialBT.print(',');
              delay(0); // nop
            }
          }
          SerialBT.println("WIFI_LIST_END");
          SerialBT.print('\n');
        }
        bufferReceive = "";
      } else {
        bufferReceive += c;
      }
      
      if (bufferReceive == "CONNECT:") {
        String parameter[10];
        int i = 0;
        while(1) {
          if (SerialBT.available()) {
            char input = SerialBT.read();
            Serial.printf("Received: %c\n", input);
            if (input == ',') {
              i++;
            } else if (input == '\n') {
              break;
            } else {
              parameter[i] += input;
            }
          }
          delay(0); // nop
        }

        String ssid = parameter[0];
        String pass = parameter[1];
        Serial.println("SSID: " + ssid);
        Serial.println("PASS: " + pass);
        SerialBT.print("OK\n");
        bufferReceive = "";
        provisioning = false;
      }
    }
  }
}