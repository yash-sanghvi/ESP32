#include <WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const char* server = "httpbin.org";
const int port = 443;

WiFiClientSecure client;


const char* ca_cert = \ 
"-----BEGIN CERTIFICATE-----\n" \
"MIIEDzCCAvegAwIBAgIBADANBgkqhkiG9w0BAQUFADBoMQswCQYDVQQGEwJVUzEl\n"\
"MCMGA1UEChMcU3RhcmZpZWxkIFRlY2hub2xvZ2llcywgSW5jLjEyMDAGA1UECxMp\n"\
"U3RhcmZpZWxkIENsYXNzIDIgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMDQw\n"\
"NjI5MTczOTE2WhcNMzQwNjI5MTczOTE2WjBoMQswCQYDVQQGEwJVUzElMCMGA1UE\n"\
"ChMcU3RhcmZpZWxkIFRlY2hub2xvZ2llcywgSW5jLjEyMDAGA1UECxMpU3RhcmZp\n"\
"ZWxkIENsYXNzIDIgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwggEgMA0GCSqGSIb3\n"\
"DQEBAQUAA4IBDQAwggEIAoIBAQC3Msj+6XGmBIWtDBFk385N78gDGIc/oav7PKaf\n"\
"8MOh2tTYbitTkPskpD6E8J7oX+zlJ0T1KKY/e97gKvDIr1MvnsoFAZMej2YcOadN\n"\
"+lq2cwQlZut3f+dZxkqZJRRU6ybH838Z1TBwj6+wRir/resp7defqgSHo9T5iaU0\n"\
"X9tDkYI22WY8sbi5gv2cOj4QyDvvBmVmepsZGD3/cVE8MC5fvj13c7JdBmzDI1aa\n"\
"K4UmkhynArPkPw2vCHmCuDY96pzTNbO8acr1zJ3o/WSNF4Azbl5KXZnJHoe0nRrA\n"\
"1W4TNSNe35tfPe/W93bC6j67eA0cQmdrBNj41tpvi/JEoAGrAgEDo4HFMIHCMB0G\n"\
"A1UdDgQWBBS/X7fRzt0fhvRbVazc1xDCDqmI5zCBkgYDVR0jBIGKMIGHgBS/X7fR\n"\
"zt0fhvRbVazc1xDCDqmI56FspGowaDELMAkGA1UEBhMCVVMxJTAjBgNVBAoTHFN0\n"\
"YXJmaWVsZCBUZWNobm9sb2dpZXMsIEluYy4xMjAwBgNVBAsTKVN0YXJmaWVsZCBD\n"\
"bGFzcyAyIENlcnRpZmljYXRpb24gQXV0aG9yaXR5ggEAMAwGA1UdEwQFMAMBAf8w\n"\
"DQYJKoZIhvcNAQEFBQADggEBAAWdP4id0ckaVaGsafPzWdqbAYcaT1epoXkJKtv3\n"\
"L7IezMdeatiDh6GX70k1PncGQVhiv45YuApnP+yz3SFmH8lU+nLMPUxA2IGvd56D\n"\
"eruix/U0F47ZEUD0/CwqTRV/p2JdLiXTAAsgGh1o+Re49L2L7ShZ3U0WixeDyLJl\n"\
"xy16paq8U4Zt3VekyvggQQto8PT7dL5WXXp59fkdheMtlb71cZBDzI0fmgAKhynp\n"\
"VSJYACPq4xJDKVtHCN2MQWplBqjlIapBtJUhlbl90TSrE9atvNziPTnNvT51cKEY\n"\
"WQPJIrSPnNVeKtelttQKbfi3QBFGmh95DmK/D5fs4C8fF5Q=\n"\
"-----END CERTIFICATE-----\n";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);                    //The WiFi is in station mode. The other is the softAP mode
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");  Serial.print("WiFi connected to: "); Serial.println(ssid);  Serial.println("IP address: ");  Serial.println(WiFi.localIP());
  client.setCACert(ca_cert);            //Only communicate with the server if the CA certificates match
  delay(2000);
}

//**********************************************
void loop() {

  int  conn;
  int chip_id = ESP.getEfuseMac();;
  Serial.printf("  Flash Chip id = %08X\t", chip_id);
  Serial.println();
  Serial.println();
  String body = "ChipId=" + String(chip_id) + "&SentBy=" + "your_name";
  int body_len = body.length();

  Serial.println(".....");
  Serial.println(); Serial.print("For sending parameters, connecting to "); Serial.println(server);
  conn = client.connect(server, port);

  if (conn == 1)
  {
    Serial.println(); Serial.print("Sending Parameters...");
    //Request
    client.println("POST /post HTTP/1.1");
    //Headers
    client.print("Host: "); client.println(server);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: "); client.println(body_len);
    client.println("Connection: Close");
    client.println();
    //Body
    client.println(body);
    client.println();

    //Wait for server response
    while (client.available() == 0);

    //Print Server Response
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
  }
  else {
    client.stop();
    Serial.println("Connection Failed");
  }


  delay(5000);
}
