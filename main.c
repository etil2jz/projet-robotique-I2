#include <Wire.h>
#include <VL6180X.h>
#include <Servo.h>

VL6180X sensor;
int distance;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(A1);
  
  Wire.begin();
  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);
  sensor.setAddress(0x29);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = sensor.readRangeSingle();
  int position = map(distance, 10, 200, 0, 180);
  servo.write(position);
  int speed = map(distance, 10, 200, 10, 100);
  servo.writeMicroseconds(1500);
  servo.writeMicroseconds(1500 + speed);
  Serial.println(distance);
  delay(100);
}
