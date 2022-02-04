#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient client;
PubSubClient mqtt(client);
#define WIFI_STA_NAME "105/712"
#define WIFI_STA_PASS "0934649179"
#define MQTT_SERVER "electsut.trueddns.com"
#define MQTT_PORT 27860
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME "B6214197"


DynamicJsonDocument docd(1024);  //รับมาจาก mqtt ใช้ตัวเดียว
DynamicJsonDocument docs(1024);   //ส่งไปหา mqtt ใช้เยอะ

char out1[256];  //ใช้ในการส่งออก
char out3[256];


void callback(char* topic, byte* payload, unsigned int length){
Serial.print("Topic = ");
Serial.print(topic);
deserializeJson(docd,payload,length);
serializeJson(docd,out3);
Serial.print(out3);
Serial.println();
std::string tp =topic;
///ล่าง ใส่ if else

}


void setup() {
Serial.begin(115200);
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
//ล่าง subscribe ex mqtt.subscribe("inno/b6214197/lab03/lighting");

}
else {
Serial.println("failed");
delay(1000);
}
}
else {
mqtt.loop();
//random ex float randtemp  = random(-100,101)/100.0;

///แพ็คข้อมูล ex  docs1["sensor"] = "temp";

///serializeJson(docs1,out4);

///mqtt.publish("inno/b6214197/lab03/sensor",out4);
///delay(1000);  


}
}
