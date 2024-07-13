/*
DC motor interfacing using ROS serial
July 9, 2024
*/

/*
STEPS
1. Include the required header files
2. Declare the arduino pins connected to motor, PWM pins
3. Instantiate a ROS node handler 
4. Define the functions for moving the bot : forward, backward, turn left, turn right, stopping
5. Define the cmd velocity call back function
6. Instantiate a ROS subscriber that subscribes to the topic cmd_vel 
7. Within the Arduino setup function : set the pin modes, initialize the baud rate, initialize the node, 
   initialize the subscriber
8. Within the Arduino loop function : process the subcriber callback (nh.spinOnce()) , add a small delay
*/

// 1. Include the required header files
#include <Arduino.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

// 2. Declare the Arduino pins connected to motor, PWM pins

int LMotorBackward = 4;
int LMotorForward = 5;
int LeftMotorPwm = 9;
int RMotorBackward = 6;
int RMotorForward = 7;
int RightMotorPwm = 10;

// 3. Instantiate a ROS node handler 
ros::NodeHandle nh;

// 4. Define the functions for moving the bot : forward, backward, turn left, turn right, stopping
void bot_stop(){
  digitalWrite(LMotorBackward, 0);
  digitalWrite(LMotorForward, 0);
  digitalWrite(RMotorBackward, 0);
  digitalWrite(RMotorForward, 0);
}

void bot_forward(){
  digitalWrite(LMotorForward, 1);
  digitalWrite(LMotorBackward, 0);
  digitalWrite(RMotorForward, 1);
  digitalWrite(RMotorBackward, 0);
  delay(20);
}

void bot_backward(){
  digitalWrite(LMotorForward, 0);
  digitalWrite(LMotorBackward, 1);
  digitalWrite(RMotorForward, 0);
  digitalWrite(RMotorBackward, 1);
  delay(20);
}

void bot_left(){
  digitalWrite(LMotorBackward, 1);
  digitalWrite(LMotorForward, 0);
  digitalWrite(RMotorBackward, 0);
  digitalWrite(RMotorForward, 1);
  delay(20);
}

void bot_right(){
  digitalWrite(LMotorBackward, 0);
  digitalWrite(LMotorForward, 1);
  digitalWrite(RMotorBackward, 1);
  digitalWrite(RMotorForward, 0);
  delay(20);
}

// 5. Define the cmd velocity call back function
void command_vel_Callback(const geometry_msgs::Twist &cmd_msg){ 
  if (cmd_msg.linear.x == 0){
    bot_stop();
  } else{
    analogWrite(LeftMotorPwm, (abs(int(cmd_msg.linear.x)))%256);
    analogWrite(RightMotorPwm, (abs(int(cmd_msg.linear.x)))%256);
    if ((cmd_msg.linear.x != 0) and (cmd_msg.angular.z != 0)){
    } else if (cmd_msg.linear.x > 0){
      bot_forward();
    } else if (cmd_msg.linear.x < 0) {
      bot_backward();
    } else if (cmd_msg.angular.z > 0){
      bot_left();
    } else if (cmd_msg.angular.z < 0){
      bot_right();
    } 
  } 
} 

// 6. Instantiate a ROS subscriber that subscribes to the topic cmd_vel 
ros::Subscriber<geometry_msgs::Twist> vel_sub("cmd_vel", &command_vel_Callback);

/*7. Within the Arduino setup function : set the pin modes, initialize the baud rate, initialize the node, 
   initialize the subscriber*/ 
void setup(){
  pinMode(LMotorBackward, OUTPUT);
  pinMode(LMotorForward, OUTPUT);
  pinMode(RMotorBackward, OUTPUT);
  pinMode(RMotorForward, OUTPUT);
  pinMode(LeftMotorPwm, OUTPUT);
  pinMode(RightMotorPwm, OUTPUT);

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(vel_sub);
}

//  8. Within the Arduino loop function : process the subcriber callback (nh.spinOnce()) , add a small delay
void loop(){
  nh.spinOnce();
  delay(10);
}