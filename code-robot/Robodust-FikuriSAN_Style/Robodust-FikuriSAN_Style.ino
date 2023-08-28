#include <Servo.h>

#define echoPin 3
#define trigPin 2
Servo myservo;
long duration;
int distance;

void setup() {
  myservo.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myservo.write(0);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Jarak= ");
  Serial.println(distance);

  if (distance > 10 || distance == 0) {
    myservo.write(0);
  } else {
    myservo.write(45);
    delay(3000);
  }
}
