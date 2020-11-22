#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

//The broker and port are provided by http://www.mqtt-dashboard.com/
char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

const char* mqtt_client_name = "ESPYS2111";
const char* mqtt_pub_topic = "/ys/testpub"; //The topic to which our client will publish
const char* mqtt_sub_topic = "/ys/testsub"; //The topic to which our client will subscribe

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
  WiFi.mode(WIFI_STA);                    //The WiFi is in station mode
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
        if(mqttClient.connect(mqtt_client_name)){
          Serial.println("MQTT Connected!");
          mqttClient.subscribe(mqtt_sub_topic);
          }
         else{
          Serial.print(".");
          }
      }
    }

  mqttClient.publish(mqtt_pub_topic, "TestMsg");
  Serial.println("Message published");
  mqttClient.loop();
  delay(5000);

}
