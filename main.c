#include <Wire.h>
#include <VL6180X.h>
#include <Servo.h>

VL6180X sensor1, sensor2, sensor3; // Déclaration des 3 capteurs
Servo servo1, servo2; // Déclaration des 2 servomoteurs
unsigned char distance1, distance2, distance3; // Déclaration des 3 variables de distance

void setup() {
  // Initialiser la communication Serial et I2C
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();
  Wire.setClock(400000); // 400 kHz

  // Passer les lignes D2, D3 et D4 en état bas
  for (unsigned char i = 2; i < 5; i++) {
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
  sensor1.startRangeContinuous();

  // Initialiser le deuxième capteur en changeant l'adresse (0x21)
  digitalWrite(3, HIGH);
  delay(10);
  sensor2.init();
  sensor2.configureDefault();
  sensor2.setTimeout(500);
  sensor2.setAddress(0x21);
  sensor2.startRangeContinuous();

  // Initialiser le troisième capteur en changeant l'adresse (0x22)
  digitalWrite(4, HIGH);
  delay(10);
  sensor3.init();
  sensor3.configureDefault();
  sensor3.setTimeout(500);
  sensor3.setAddress(0x22);
  sensor3.startRangeContinuous();

  // Attribuer les servomoteurs aux broches A1 et A2
  servo1.attach(A1);
  servo2.attach(A2);
}

void loop() {
  // Obtenir la valeur des capteurs de distance
  distance1 = sensor1.readRangeContinuous();
  distance2 = sensor2.readRangeContinuous();
  distance3 = sensor3.readRangeContinuous();

  // Contrôler les moteurs en fonction des obstacles
  if (distance1 < 100 && distance2 < 100 && distance3 < 100) {
    servo1.write(90); // de 91 à 180 -> marche arrière, réciproque vraie ;; 90 = arrêt
    servo2.write(90);  
  } else {
    servo1.write(0);
    servo2.write(0);
  }

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
