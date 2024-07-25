# DC motor interfacing using ROS serial Arduino

##### Project has been built for Arduino Nano

### Equipment required
1. Arduino Uno or Nano  - 1 nos
2. BO motor (DC toy) - 1 nos
3. L298 or L293 motor driver - 1 nos

### Steps to code 
1. Include the required header files
2. Declare the arduino pins connected to motor, PWM pins
3. Instantiate a ROS node handler 
4. Define the functions for moving the bot : forward, backward, turn left, turn right, stopping
5. Define the cmd velocity call back function
6. Instantiate a ROS subscriber that subscribes to the topic cmd_vel 
7. Within the Arduino setup function : 
    - Set the pin modes
    - Initialize the baud rate
    - Initialize the node
    - Initialize the subscriber
8. Within the Arduino loop function : 
    - Process the subcriber callback (nh.spinOnce())
    - Add a small delay

### Additional Resources
- [Configure VS Code for rosserial_arduino](https://jim79.github.io/rosserial-arduino-vscode/)
- [Video tutorial - Configure VS Code for rosserial_arduino](https://youtu.be/RZAXBMoWJcE)

### Steps to run the code
1. Launch ```roscore``` in a terminal \\
```roscore```

2. In another terminal type in following to launch a rosserial connection with Arduino \\
```rosrun rosserial_arduino serial_node.py _baud:=115200
```
3. In yet another terminal run ```teleop_twist_keyboard``` to control the motor. Since we have interfaced only one motor we can verify the following functionalities - bot_forward, bot_backward and bot_stop. The bot_left and bot_right functionalities can be verified by interfacing one more motor. \\
```rosrun teleop_twist_keyboard teleop_twist_keyboard.py```