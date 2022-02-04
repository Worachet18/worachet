long randnum ;
float randfloat ;
float rhrand=50;
void setup() {
  Serial.begin(115200);
  randomSeed(50);

}

void loop() {
  randnum = random(-100,100);
  randfloat= randnum/100.0;
  rhrand=rhrand+randfloat;

  if(rhrand>100){
    rhrand=100;
    }
   else if (rhrand<0){
    rhrand=0;
    }
  Serial.println(rhrand);
  delay(10);

}
