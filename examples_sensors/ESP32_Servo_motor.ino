#include <ESP32Servo.h>

Servo myServo;

const int servoPin = 4;  // Poți alege orice pin PWM-capabil (ex: 2, 4, 5, 12, 13, 14, 15, 18, 19, 21, 22, 23)

void setup() {
  myServo.setPeriodHertz(50); // Frecvență pentru servo: 50 Hz
  myServo.attach(servoPin, 500, 2400); // Min și Max pulsuri (poate varia ușor de la un servo la altul)
}

void loop() {
  // Mișcare fluidă 0 → 180
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(10); // mișcare lină
  }

  delay(1000); // pauză

  // Mișcare înapoi 180 → 0 în pași de 30°
  for (int angle = 180; angle >= 0; angle -= 30) {
    myServo.write(angle);
    delay(500);
  }

  delay(1000); // pauză înainte de a repeta
}
