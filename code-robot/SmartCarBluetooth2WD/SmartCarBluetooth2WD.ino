//Coding Smart Car Bluetooth Robonesia
#include <SoftwareSerial.h>
#include <AFMotor.h>

//initial motors pin
AF_DCMotor motor1(3, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

//initial bluetooth
SoftwareSerial mySerial(9, 10); //RX berada di pin 9, TX berada di pin 10

char command;

void setup()
{
  mySerial.begin(9600);  //Set the baud rate to your Bluetooth module.
}

void loop() {
  if (mySerial.available() > 0)
  {
    command = mySerial.read();
    delay(2);
    Stop();

    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
    }
  }
}

void forward()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
}

void left()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(RELEASE); //rotate the motor anti-clockwise
}

void right()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(RELEASE); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}

void Stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
}
