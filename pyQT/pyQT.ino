#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient client;
PubSubClient mqtt(client);
#define WIFI_STA_NAME "Android BASKUB"
#define WIFI_STA_PASS "22082016"
#define MQTT_SERVER   "electsut.trueddns.com"
#define MQTT_PORT     27860
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME     "B6214197"
#define LED_PIN 23
#define sw 5
DynamicJsonDocument docs1(1024);
DynamicJsonDocument docd(1024);
char output1[256];
char input1[256];
void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Topic = ");
  Serial.println(topic); 
  deserializeJson(docd,payload,length);
  serializeJson(docd,input1);
//  Serial.print(" payload = ");
//  Serial.println(input1);  
  int LED = docd["LED"];
  const char* state = docd["state"];
//  Serial.println(LED);
//  Serial.println(state); 
  std::string s = state;
  if(LED == 1){
//    Serial.println("1on");
      if(s == "on"){
        Serial.println("on1");
        digitalWrite(18,HIGH);
                   }
      else if(s == "off"){
        Serial.println("off1");
        digitalWrite(18,LOW);
                         }
              }
  else if(LED == 2){
//    Serial.println("2on");
      if(s == "on"){
        Serial.println("on2");
        digitalWrite(19,HIGH);
                   }
      else if(s == "off"){
        Serial.println("off2");
        digitalWrite(19,LOW);
                         }
                   }            
      
                                                              }                                                            
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_STA_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt.setCallback(callback);
}
void loop() {
  if (mqtt.connected() == false) {
    Serial.print("MQTT connecting... ");
    if (mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD)) 
    {
      Serial.println("connected");
      mqtt.subscribe("inno/B6222932/lighting");
    } 
    else {
      Serial.println("failed");
      delay(1000);
          }
                                  } 
  else {
          mqtt.loop();
          docs1["temp"] = 24.5;
          docs1["HM"] = 75.0;
          serializeJson(docs1,output1);
          mqtt.publish("B6222932/floor2/room1/point1", output1);
//          mqtt.publish("B6222932/floor1/room1/point1", "{\"temp\":25.5}");
          delay(1000);  
     }
            }
