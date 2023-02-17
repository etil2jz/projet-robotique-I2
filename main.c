#include <Wire.h>
#include <VL6180X.h>

VL6180X sensor;
int distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);
  sensor.setAddress(0x29);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = sensor.readRangeSingle();
  Serial.println(distance);
  delay(100);
}
