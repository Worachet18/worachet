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
#define LED_PIN 23
#define sw 5

DynamicJsonDocument docd(1024);  //รับมาจาก mqtt
DynamicJsonDocument docs(1024);   //ส่งไปหา mqtt
DynamicJsonDocument docs1(1024);   //ส่งไปหา mqtt
char out1[256];
char out2[256];
char out3[256];
char out4[256];

void callback(char* topic, byte* payload, unsigned int length){
Serial.print("Topic = ");
Serial.print(topic);
deserializeJson(docd,payload,length);
serializeJson(docd,out3);
Serial.print(out3);
Serial.println();

/****************LED*****************/////////////////////////////////
/*int LED1 = docd["LED"];
const char* state = docd["state"];
std::string s =state;
if (LED1 == 1){
  if (s=="on"){
    digitalWrite(18,1);}
  else if(s=="off"){
    digitalWrite(18,0);}
              }
else if (LED1 == 2){
  if (s=="on"){
    digitalWrite(19,1);}
  else if(s=="off"){
    digitalWrite(19,0);}
              }*/
/************************PWM*////////////////////////////////////////

/*int pwm = docd["PWM"];
int val = docd["val"];
if (pwm == 1){
  ledcWrite(1,val);
  Serial.print("pwm=1");
             }
  
else if (pwm == 2){
  Serial.print("pwm=2");
  ledcWrite(2,val);
                  }*/
                  
/****************************Swich*////////////////////////////////////////
const char* swstate = docd["sw_status"];
int valsw = !digitalRead(4);
Serial.print(valsw);
if (valsw == 1){
  docs1["SW1"]="on";
  serializeJson(docs1,out4);
  mqtt.publish("B6214197/lab02/swst",out4);

  }
else if (valsw == 0){
  docs1["SW1"]="off";
  serializeJson(docs1,out4);
  mqtt.publish("B6214197/lab02/swst",out4);

  }
}



void setup() {

pinMode(18,OUTPUT);
pinMode(19,OUTPUT);
pinMode(12,OUTPUT);
pinMode(14,OUTPUT);
pinMode(4,INPUT_PULLUP);
ledcSetup(1,5000,8); 
ledcAttachPin(12,1);
ledcSetup(2,5000,8); 
ledcAttachPin(14,2);
 
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
mqtt.subscribe("B6214197/lab02/swst");
}
else {
Serial.println("failed");
delay(1000);
}
}
else {
mqtt.loop();
docs["emeter"]= "meter01" ;
docs["energy"]=250;
docs["freq"]=60;
docs["wmeter"]= "water_usage" ;
docs["water"]=125;
serializeJson(docs,out1);
mqtt.publish("B6214197/lab02/ex2_2_1",out1);
/*mqtt.publish("B6214197/lab02/ext2_2_1","{\"emeter\":\"meter01\",\"energy\":250,\"freq\":60}");
mqtt.publish("B6214197/lab02/ext2_2_2","{\"wmeter\":\"water_usage\",\"water\":125}"); */
delay(1000);
}
}
