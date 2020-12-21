#include <ros.h>
//can change data type
#include <std_msgs/Int32MultiArray.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
ros::NodeHandle nh;

// these are variables for what ever you want to send from ros (can be changed)
int Mode;
int Intensity;
int Freq;

//This is initializing the boards all will follow this patter and need to be soldered to make them unique
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
//Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
//Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42);

//set up for collecting data from ros (can change data type)
void messageCb(const std_msgs::Int32MultiArray& cdm_msg)
{
cdm_msg.data;

//assining ros dat to usable variable 
Mode=cdm_msg.data[0];
Intensity=cdm_msg.data[1];
}

//set up subscriber. mathch data type and match topic referanced in ros
ros::Subscriber<std_msgs::Int32MultiArray> sub("pwm_intensity_ctrl", &messageCb);

// set up
void setup() {
  Mode = -1;
  Intensity = 0;
  Freq = 100;
  
  nh.initNode();
  nh.subscribe(sub);
  
  Serial.begin(57600);

  //  seting up all boards. needs to be done if more boards are added
  pwm1.begin();
  pwm1.setPWMFreq(Freq);  // 1600 is the max, use lower value to prevent "singing"
 
  //pwm2.begin();
  //pwm2.setPWMFreq(Freq);
  
  //pwm3.begin();
  //pwm3.setPWMFreq(Freq);
 
}



void loop() {

//where you do stuff with your inputs

//general set up is...

// what is your mode? laminar? turb? pulse? flash?
////then do something based on that mode

//    this is the structure for how to send the signal to one board
//Example
//    pwm1.setPWM(2,0,Intensity*40.95);
//    pwm1---> board 1
//    2---> pin 2
//    0---> always zero
//    Intensity---> PWM frequency from 0 to 100
//    *40.95---> scaling factor for PWM
  
// control everything together
if (Mode == -1){
  for (int pin=0; pin<16; pin++){
    pwm1.setPWM(pin,0,Intensity*40.95);
    //pwm2.setPWM(pin,0,Intensity*40.95);
    //pwm3.setPWM(pin,0,Intensity*40.95);
  }
}

// control individual LEDs
else if (Mode >= 0 and Mode < 16) {
  pwm1.setPWM(Mode,0,Intensity*40.95);
}



delay(25);


 nh.spinOnce(); 
}
