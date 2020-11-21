#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "chetan_2.4g";
const char* password = "9819085461";
char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

WiFiClient client;
PubSubClient mqttClient(client);
 

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received from: "); Serial.println(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);                    //The WiFi is in station mode. The other is the softAP mode
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");  Serial.print("WiFi connected to: "); Serial.println(ssid);  Serial.println("IP address: ");  Serial.println(WiFi.localIP());
  delay(2000);
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!mqttClient.connected()){
      while (!mqttClient.connected()){
        if(mqttClient.connect("ESPYS2111")){
          Serial.println("MQTT Connected!");
          mqttClient.subscribe("/ys/testsub");
          }
         else{
          Serial.print(".");
          }
      }
    }

  mqttClient.publish("/ys/testpub", "TestMsg");
  mqttClient.loop();
  Serial.println("Message published");
  delay(5000);

}
