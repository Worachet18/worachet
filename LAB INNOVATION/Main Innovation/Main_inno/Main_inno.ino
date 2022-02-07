#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient client;
PubSubClient mqtt(client);
#define WIFI_STA_NAME "Rungtiwa"
#define WIFI_STA_PASS "0818774251"
#define MQTT_SERVER "electsut.trueddns.com"
#define MQTT_PORT 27860
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME "B6214197"
#define LED_PIN 23
#define sw 5
void callback(char* topic, byte* payload, unsigned int length){
Serial.print("Topic = ");
Serial.print(topic);
for(int i=0;i< length;i++){
Serial.print((char)payload[i]);
}
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
}
else {
Serial.println("failed");
delay(1000);
}
}
else {
mqtt.loop();
}
}
