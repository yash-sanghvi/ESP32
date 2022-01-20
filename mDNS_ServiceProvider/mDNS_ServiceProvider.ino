#include "ESPmDNS.h"
#include <WiFi.h>
    
const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPassword";

#define MDNS_DEVICE_NAME "my-esp32"
#define SERVICE_NAME "my-service"
#define SERVICE_PROTOCOL "udp"
#define SERVICE_PORT 5600
       
void setup(){
  Serial.begin(115200);
    
  WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
   
  if(!MDNS.begin(MDNS_DEVICE_NAME)) {
     Serial.println("Error encountered while starting mDNS");
     return;
  }
  
  MDNS.addService(SERVICE_NAME, SERVICE_PROTOCOL, SERVICE_PORT);
 
  Serial.println(WiFi.localIP());
    
}
    
void loop(){}
