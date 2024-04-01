#include <Servo.h>

#define TRIGGER_PIN_1 2  // Pin trigger sensor ultrasonik tempat sampah 1
#define ECHO_PIN_1 3     // Pin echo sensor ultrasonik tempat sampah 1
#define TRIGGER_PIN_2 4  // Pin trigger sensor ultrasonik tempat sampah 2
#define ECHO_PIN_2 5     // Pin echo sensor ultrasonik tempat sampah 2
#define TRIGGER_PIN_3 6  // Pin trigger sensor ultrasonik tempat sampah 3
#define ECHO_PIN_3 7     // Pin echo sensor ultrasonik tempat sampah 3

#define SERVO_PIN_1 8    // Pin kontrol motor servo tempat sampah 1
#define SERVO_PIN_2 9    // Pin kontrol motor servo tempat sampah 2
#define SERVO_PIN_3 10   // Pin kontrol motor servo tempat sampah 3

Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIGGER_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);

  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);

  Serial.begin(9600);
}

void loop() {
  int distance1 = getDistance(TRIGGER_PIN_1, ECHO_PIN_1);
  int distance2 = getDistance(TRIGGER_PIN_2, ECHO_PIN_2);
  int distance3 = getDistance(TRIGGER_PIN_3, ECHO_PIN_3);

  if (distance1 < 20) {  // Adjust the threshold according to your requirement
    openLid(servo1);
  } else {
    closeLid(servo1);
  }

  if (distance2 < 20) {  // Adjust the threshold according to your requirement
    openLid(servo2);
  } else {
    closeLid(servo2);
  }

  if (distance3 < 20) {  // Adjust the threshold according to your requirement
    openLid(servo3);
  } else {
    closeLid(servo3);
  }

  delay(1000);  // Delay between sensor readings
}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;  // Convert pulse width to distance in cm
}

void openLid(Servo servo) {
  servo.write(90);  // Open the lid
}

void closeLid(Servo servo) {
  servo.write(0);   // Close the lid
}
