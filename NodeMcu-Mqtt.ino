#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//Pengaturan Koneksi 
const char* ssid = "abc";
const char* password =  "22223333";
const char* mqttServer = "postman.cloudmqtt.com";
const int mqttPort =  13889;
const char* mqttUser = "***fhoer";
const char* mqttPassword = "****X69NZBrS";

unsigned long lastSend;
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("kirim", "Hello from ESP8266");
  client.subscribe("terima");
  lastSend=0;
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
  Serial.print("Message:");
  String msg="";
  for (unsigned int i = 0; i < length; i++) {
 //   Serial.print((char)payload[i]);
    msg+=(String)((char)payload[i]);
  }

  Serial.println(msg);
  if(msg.indexOf("1") >= 0){
   //lakukan sesuatu di sini
  }
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
    client.publish("kirim", "Hello from ESP8266");
    lastSend = millis();
  }

  client.loop();
}
