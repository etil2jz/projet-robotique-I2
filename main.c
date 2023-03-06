#include <Wire.h>
#include <VL6180X.h>
#include <Servo.h>

VL6180X sensor1, sensor2, sensor3; // Déclaration des 3 capteurs
Servo servo1, servo2; // Déclaration des 2 servomoteurs

void setup() {
  // Initialiser la communication Serial et I2C
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();

  // Passer les lignes D2, D3 et D4 en état bas
  for (int i = 2; i < 5; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
    delay(10);
  }

  // Initialiser le premier capteur avec l'adresse par défaut (0x20)
  digitalWrite(2, HIGH);
  delay(10);
  sensor1.init();
  sensor1.configureDefault();
  sensor1.setTimeout(500);
  sensor1.setAddress(0x20);

  // Initialiser le deuxième capteur en changeant l'adresse (0x21)
  digitalWrite(3, HIGH);
  delay(10);
  sensor2.init();
  sensor2.configureDefault();
  sensor2.setTimeout(500);
  sensor2.setAddress(0x21);

  // Initialiser le troisième capteur en changeant l'adresse (0x22)
  digitalWrite(4, HIGH);
  delay(10);
  sensor3.init();
  sensor3.configureDefault();
  sensor3.setTimeout(500);
  sensor3.setAddress(0x22);

  // Attribuer les servomoteurs aux broches A1 et A2
  servo1.attach(A1);
  servo2.attach(A2);
}

void loop() {
  // Obtenir la valeur des capteurs de distance
  int distance1 = sensor1.readRangeSingle(), distance2 = sensor2.readRangeSingle(), distance3 = sensor3.readRangeSingle();

  // check if there is an obstacle within a certain distance
  //if (distance1 < 100 && distance2 < 100) {
  //  servo1.write(180);
  //  servo2.write(0);  
  //} else {
  //  servo1.write(90);
  //  servo2.write(90);
  //}

  // Débuggage capteurs de distance
  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" - Distance2: ");
  Serial.print(distance2);
  Serial.print(" - Distance3: ");
  Serial.println(distance3);

  // petit délai
  delay(50);
}
