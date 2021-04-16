#include <ros.h>
//can change data type
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/UInt16MultiArray.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
ros::NodeHandle nh;

// these are variables for what ever you want to send from ros (can be changed)
int Mode;
int Intensity;
int Freq;
int frame_current;
int frame_prior;
int flash_dur;
std_msgs::UInt16MultiArray msg_arr;
//int msg_arr[2];
//This is initializing the boards all will follow this patter and need to be soldered to make them unique
Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
//Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42);

//set up for collecting data from ros (can change data type)
//may get upset for some modes if they dont have a data[2]
void messageCb(const std_msgs::Int32MultiArray& cdm_msg)
{
cdm_msg.data;

//assigning ros dat to usable variable 
Mode=cdm_msg.data[0];
Intensity=cdm_msg.data[1];
flash_dur =cdm_msg.data[2];
frame_current =cdm_msg.data[3];

}

//set up subscriber. mathch data type and match topic referanced in ros
ros::Subscriber<std_msgs::Int32MultiArray> sub("pwm_intensity_ctrl", &messageCb);
ros::Publisher ard_time("ard_time", &msg_arr);

// set up
void setup() {
  Mode = -1;
  Intensity = 0;
  Freq = 100;
  
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(ard_time);
  
  
  Serial.begin(57600);

  //  seting up all boards. needs to be done if more boards are added
  pwm0.begin();
  pwm0.setPWMFreq(Freq);  // 1600 is the max, use lower value to prevent "singing"
 
  pwm1.begin();
  pwm1.setPWMFreq(Freq);
  msg_arr.data=(std_msgs::UInt16MultiArray::_data_type*) malloc(2 * sizeof(std_msgs::UInt16MultiArray::_data_type));
  msg_arr.data_length = 2;
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
//    pwm0.setPWM(2,0,Intensity*40.95);
//    pwm0---> board 1
//    2---> pin 2
//    0---> always zero
//    Intensity---> PWM frequency from 0 to 100
//    *40.95 ---> scaling factor for PWM
  
// control everything together
if (Mode == -1){
  for (int pin=0; pin<16; pin++){
    pwm0.setPWM(pin,0,Intensity*40.95);
    pwm1.setPWM(pin,0,Intensity*40.95);
    //pwm3.setPWM(pin,0,Intensity*40.95);
  }
}

// control individual LEDs
else if (Mode >= 0 and Mode < 16) {
  pwm0.setPWM(Mode,0,Intensity*40.95);
}
else if (Mode >= 16 and Mode < 32) {
  pwm1.setPWM(Mode-16,0,Intensity*40.95);
}
//will need to publish something that notifies when that has been signalled individually otherwise will loop continuously
else if (Mode == -2 and frame_current != frame_prior){
 ard_time.publish(&msg_arr);
 int time1;
 int time2;
 int net_time;
 
 for (int pin=0; pin<16; pin++){
 pwm0.setPWM(pin,0,Intensity*40.95);
 pwm1.setPWM(pin,0,Intensity*40.95);
 time1= millis();   
 //pwm3.setPWM(pin,0,Intensity*40.95);
  }
 delay(flash_dur);
 for (int pin=0; pin<16; pin++){
   pwm0.setPWM(pin,0,0);
   pwm1.setPWM(pin,0,0);
   time2 = millis();
    
    //pwm3.setPWM(pin,0,Intensity*40.95);
  }
  //Serial.println(time1-time2);
  frame_prior =frame_current;
  int time_f =time2-time1;
  msg_arr.data[0]=time_f;
  msg_arr.data[1] = frame_current;
  
  //Serial.println(time_f);
  //Serial.println(frame_current);
  //pub.publish();

}

delay(25);

 
 nh.spinOnce(); 

}
