#include <Wire.h>
#include <VL6180X.h>
#include <Servo.h>

VL6180X capteurG, capteurF, capteurD; // Déclaration des 3 capteurs
Servo servoG, servoD; // Déclaration des 2 servomoteurs
unsigned char distanceG, distanceF, distanceD; // Déclaration des 3 variables de distance

void setup() {
  // Initialiser la communication --Serial et-- I2C
  //Serial.begin(9600);
  //while (!Serial);
  Wire.begin();
  Wire.setClock(400000); // 400 kHz

  // Passer les lignes D2, D3 et D4 en état bas
  for (unsigned char i = 2; i < 5; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
    delay(10);
  }

  // Initialiser le premier capteur en changeant l'adresse (0x20)
  digitalWrite(2, HIGH);
  delay(10);
  capteurG.init();
  capteurG.configureDefault();
  capteurG.setTimeout(500);
  capteurG.setAddress(0x20);
  capteurG.startRangeContinuous();

  // Initialiser le deuxième capteur en changeant l'adresse (0x21)
  digitalWrite(3, HIGH);
  delay(10);
  capteurF.init();
  capteurF.configureDefault();
  capteurF.setTimeout(500);
  capteurF.setAddress(0x21);
  capteurF.startRangeContinuous();

  // Initialiser le troisième capteur en changeant l'adresse (0x22)
  digitalWrite(4, HIGH);
  delay(10);
  capteurD.init();
  capteurD.configureDefault();
  capteurD.setTimeout(500);
  capteurD.setAddress(0x22);
  capteurD.startRangeContinuous();

  // Attribuer les servomoteurs aux broches A1 et A2
  servoG.attach(A1);
  servoD.attach(A2);
}

void loop() {
  // Obtenir la valeur des capteurs de distance
  distanceG = capteurG.readRangeContinuous();
  distanceF = capteurF.readRangeContinuous();
  distanceD = capteurD.readRangeContinuous();

  // Contrôler les moteurs en fonction des obstacles
  if (distanceF < 60 && distanceG < 60 && distanceD < 60) {
    servoG.write(0);
    servoD.write(135);
    delay(500);
  } else if (distanceF < distanceD && distanceG + 25 < distanceD) {
    servoG.write(180);
    servoD.write(90);
  } else if (distanceF < distanceG && distanceD + 25 < distanceG) {
    servoG.write(90);
    servoD.write(0);
  } else {
    servoG.write(180);
    servoD.write(0);
  }

  // Débuggage capteurs de distance
  /*
  Serial.print("DistanceG: ");
  Serial.print(distanceG);
  Serial.print(" - DistanceF: ");
  Serial.print(distanceF);
  Serial.print(" - DistanceD: ");
  Serial.println(distanceD);
  */
}
