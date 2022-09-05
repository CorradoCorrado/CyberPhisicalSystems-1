int valPWM;
const int interm = 200;
const int led = 13;
const int out = 9;

int minPWM = 350;  //0 BITS
int maxPWM = 1023; //10 BITS
int delayTime = 5000;

void setup() {
  // put your setup code here, to run once:
pinMode(out,OUTPUT);
pinMode(led,OUTPUT);
Serial.begin(1200);
}

void loop() {
  // put your main code here, to run repeatedly:
valPWM = random(minPWM,maxPWM);
Serial.print("PWM ACTUAL: ");
Serial.println(valPWM);
digitalWrite(led,LOW);
analogWrite(9,valPWM);
delay(delayTime);

analogWrite(9,interm);
digitalWrite(led,HIGH);
delay(1000);




}
