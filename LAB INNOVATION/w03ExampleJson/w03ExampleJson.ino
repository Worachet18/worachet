#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
DynamicJsonDocument docd(1024);
DynamicJsonDocument docs(1024);
WiFiClient client;
PubSubClient mqtt(client);
#define WIFI_STA_NAME "105/712"
#define WIFI_STA_PASS "0934649179"
#define MQTT_SERVER   "electsut.trueddns.com"
#define MQTT_PORT     27860
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME     "B6214197"
#define LED_PIN 23
#define sw 5

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Topic = ");
  Serial.print(topic);
  deserializeJson(docd, payload, length);
  float temp = docd["temp"];
  float humid = docd["humid"];
  Serial.print("Temp = ");
  Serial.print(temp);
  Serial.print("Humid = ");
  Serial.println(humid);
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
      mqtt.subscribe("B6214197/room1/point1");
      mqtt.subscribe("B6214197/room1/point2");
    } 
    else {
      Serial.println("failed");
      delay(1000);
          }
                                  } 
  else {
          mqtt.loop();
          float pressure=50.5;
          float lux=40.1;
          docs["pressure"]=pressure;
          docs["lux"]=lux;
          char output[256];
          serializeJson(docs,output);
          mqtt.publish("B6214197/floor2/room1/point1",output);
         // mqtt.publish("B6214197/floor1/room1/point1", "{\"temp\":23.5}");
          delay(1000);  
     }
            }
