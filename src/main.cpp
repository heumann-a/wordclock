#include <Arduino.h>
//Wifi
#include <ESP8266WiFi.h> 
// NTP Wifi Connection
#include <NTPClient.h>
#include <WiFiUdp.h>


const char *ssid     = "KabelBox-2AA8";
const char *password = "15123592243022716685";

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600);

void scanNetworks(){
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  Serial.print("SSID List:");
  Serial.println(numSsid);
  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") Network: ");
    Serial.println(WiFi.SSID(thisNet));
  }
}

void connectNTP(){
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectNTP();
}

void loop() {
  // put your main code here, to run repeatedly:
  scanNetworks();

  timeClient.forceUpdate();
  Serial.println(timeClient.getFormattedTime());
  delay(3000);
}
