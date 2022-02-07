#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient client;
PubSubClient mqtt(client);
#define WIFI_STA_NAME "worachet"
#define WIFI_STA_PASS "12345678"
#define MQTT_SERVER "electsut.trueddns.com"
#define MQTT_PORT 27860
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME "B6214197"
float temp =50;
float rh=50;


DynamicJsonDocument docd(1024);  //รับมาจาก mqtt ใช้ตัวเดียว
DynamicJsonDocument docs(1024);   //ส่งไปหา mqtt ใช้เยอะ
DynamicJsonDocument docs1(1024);
DynamicJsonDocument docs2(1024);

char out1[256];  //ใช้ในการส่งออก
char out3[256];
char out4[256];
char out5[256];


void callback(char* topic, byte* payload, unsigned int length){
Serial.print("Topic = ");
Serial.print(topic);
deserializeJson(docd,payload,length);
serializeJson(docd,out3);
Serial.print(out3);
Serial.println();
std::string tp = topic;
if (tp=="inno/b6214197/lab03/pwm"){
  int pwm = docd["PWM"];
  int a = docd["val"];
  if (pwm==1){
    Serial.print("pwm1");
    ledcWrite(1,a);
             }
  else if (pwm==2){
    ledcWrite(2,a);
    Serial.print("pwm2");
                  }
                                  }
if (tp=="inno/b6214197/lab03/lighting"){
  int LED1 = docd["LED"];
  const char* st = docd["state"];
  std::string s = st;
  if (LED1==1){
    if(s=="on"){
      digitalWrite(18,1);
               }
    else if(s=="off"){
      digitalWrite(18,0);
                     }
              }
  else if (LED1==2){
    if(s=="on"){
      digitalWrite(19,1);
      ledcWrite(2,10);
               }
    else if(s=="off"){
      digitalWrite(19,0);
                     }
                   }
                                        } 
}


void setup() {
ledcSetup(1,5000,8);
ledcAttachPin(12,1);
ledcSetup(2,5000,8);
ledcAttachPin(14,2);
//ledcWrite(1,255);
pinMode(12,OUTPUT);
pinMode(14,OUTPUT);
pinMode(18,OUTPUT);
pinMode(19,OUTPUT);
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

mqtt.subscribe("inno/b6214197/lab03/lighting");
mqtt.subscribe("inno/b6214197/lab03/pwm");

}
else {
Serial.println("failed");
delay(1000);
}
}
else {
mqtt.loop();

float randtemp = random(-100,101)/100.0;
temp = temp+randtemp;
if (temp > 100){
  temp = 100 ;
  }
else if (temp < 0){
  temp = 0 ;
  }
float randrh = random(-100,101)/100.0;
rh = rh+randrh;
if (rh > 100){
  rh = 100 ;
  }
else if (rh < 0){
  rh = 0 ;
  }

docs1["sensor"] = "temp";
docs1["val"] = temp ;
docs2["sensor"] = "humid";
docs2["val"] = rh ;


serializeJson(docs1,out4);
serializeJson(docs2,out5);

mqtt.publish("inno/b6214197/lab03/sensor",out4);
mqtt.publish("inno/b6214197/lab03/sensor",out5);

delay(1000);


}
}
