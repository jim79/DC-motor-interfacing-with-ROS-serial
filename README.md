# DC motor interfacing using ROS serial Arduino
In
##### Project has been built for Arduino Nano

### Steps
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

