#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266NetBIOS.h>
#include <ESP8266SSDP.h>

ESP8266WiFiMulti network;
bool connection = false;

void setHostname(){
    MDNS.begin(name);
    MDNS.addService("http","tcp", 80);
    NBNS.begin(name);
    Serial.print("--> Name: ");
    Serial.println(name);
}

bool checkSSID(){
  int n = WiFi.scanNetworks();
  if (n == 0){
    return false;
  }
  for (int i = 0; i < n; i++){
    if(WiFi.SSID(i) == ssid1)
      return true;
    if(WiFi.SSID(i) == ssid2)
      return true;
    if(WiFi.SSID(i) == ssid3)
      return true;
    if(WiFi.SSID(i) == ssid4)
      return true;
  }
  return false;
}

//Try to connect to ssid, if fail connect to AP.
void connect(){
  Serial.println("... [WIFI] Connection ...");
    if(checkSSID()){
      WiFi.mode(WIFI_STA);
      network.addAP(ssid1,pass1);
      network.addAP(ssid2,pass2);
      network.addAP(ssid3,pass3);
      network.addAP(ssid4,pass4);
      while (network.run() != WL_CONNECTED){
      }
      Serial.print("--> SSID : ");
      Serial.println(WiFi.SSID());
      Serial.print("--> IP : ");
      Serial.println(WiFi.localIP());
    } else {
      WiFi.mode(WIFI_AP);
      WiFi.softAP(ap_ssid,ap_pass);
      Serial.print("--> SSID : ");
      Serial.println(WiFi.softAPIP());
      Serial.println("--> IP : 192.168.4.1");
    }
    setHostname();
}
