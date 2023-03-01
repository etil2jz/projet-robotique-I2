#include <Wire.h>
#include <VL6180X.h>
#include <Servo.h>

VL6180X sensor1;
Servo servo1;

void setup() {
  Serial.begin(9600);

  Wire.begin();

  sensor1.init();
  servo1.attach(A1);

  sensor1.configureDefault();
  sensor1.setTimeout(500);
  sensor1.setAddress(0x29);
}

void loop() {
  // measure distance with sensor
  int distance = sensor1.readRangeSingle();

  // check if there is an obstacle within a certain distance
  if (distance < 100) {
    servo1.write(180);
  } else {
    servo1.write(0);
  }

  // print sensor reading to serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // wait a short amount of time before measuring again
  delay(50);
}
