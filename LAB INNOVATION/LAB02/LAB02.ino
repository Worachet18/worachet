#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
DynamicJsonDocument docd(1024);
DynamicJsonDocument docs(1024);
DynamicJsonDocument docs1(1024);

WiFiClient client;
PubSubClient mqtt(client);
#define WIFI_STA_NAME "Rungtiwa"
#define WIFI_STA_PASS "0818774251"
#define MQTT_SERVER   "electsut.trueddns.com"
#define MQTT_PORT     27860
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME     "B6214197"
#define LED_PIN 23
#define sw 5
char out1[256];
char out2[256];
char out3[256];



void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Topic = ");
  Serial.print(topic);
  deserializeJson(docd,payload,length);
  serializeJson(docd,out3);
  Serial.print(out3);
  Serial.println();
 
                                                              }
                                                        
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
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
      mqtt.subscribe("B6214197/lab02/lighting");
      mqtt.subscribe("B6214197/lab02/pwm");
    }
    else {
      Serial.println("failed");
      delay(1000);
          }
                                  } 
  else {
          mqtt.loop();
          docs["emeter"]="meter01";
          docs["energy"]=250;
          docs["freq"]=60;
          serializeJson(docs,out1);
          mqtt.publish("B6214197/lab02/ext2_2_1",out1);
          docs1["wmeter"]="water_usage";
          docs1["water"]=125;
          serializeJson(docs1,out2);
          mqtt.publish("B6214197/lab02/ext2_2_2",out2);
//          mqtt.publish("B6214197/lab02/ext2_2_1","{\"emeter\":\"meter01\",\"energy\":250,\"freq\":60}");
//          mqtt.publish("B6214197/lab02/ext2_2_2","{\"wmeter\":\"water_usage\",\"water\":125}");
          delay(1000);  
     }
            }
