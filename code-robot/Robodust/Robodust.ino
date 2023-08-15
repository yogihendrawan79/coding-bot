#include <Servo.h>

const int trigPin = 2;
const int echoPin = 3;
Servo myservo;
long duration;
int distance;
int previousDistance = 0;

void setup() {
  myservo.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myservo.write(2);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Jarak= ");
  Serial.println(distance);

  if (distance < 10 && previousDistance >= 10) {
    myservo.write(75);
    delay(3000);
    myservo.write(2);
    delay(3000);
  }

  //  if (distance > 10 && previousDistance <= 10) {
  //    myservo.write(0);
  //    delay(3000);
  //    myservo.write(75);
  //  }

  previousDistance = distance;

  delay(200);
}
