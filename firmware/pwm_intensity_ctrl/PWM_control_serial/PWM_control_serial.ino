#include <Adafruit_PWMServoDriver.h>
int state_1=0;
int state_2 =0;
int Intensity =100;
int mode = -1;
int Freq;
int incomingByte;

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);

void setup() {
  Serial.begin(19200);
  pwm0.begin();
  pwm0.setPWMFreq(Freq);  // 1600 is the max, use lower value to prevent "singing"
  Freq = 100;
  pwm1.begin();
  pwm1.setPWMFreq(Freq);
  for (int pin=0; pin<16; pin++){
    pwm0.setPWM(pin,0,0);
    pwm1.setPWM(pin,0,0);}
  

}

void loop() {
  if (Serial.available()){
    incomingByte = Serial.read();
  }
  if(state_1==0 and incomingByte =='y'){
    for (int pin=0; pin<16; pin++){
    pwm0.setPWM(pin,0,Intensity*40.95);
    pwm1.setPWM(pin,0,Intensity*40.95);
    state_1=1;
    }
  }
  else if(state_1==1 and incomingByte =='n'){
    for (int pin=0; pin<16; pin++){
    pwm0.setPWM(pin,0,0);
    pwm1.setPWM(pin,0,0);
    state_1=0;
  }
  }    
  }
  // put your main code here, to run repeatedly:
