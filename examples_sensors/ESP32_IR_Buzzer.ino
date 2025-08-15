#define IR_SENSOR_PIN 4       // Pin de semnal de la senzorul IR (digital)
#define BUZZER_PIN 23         // Pin conectat la buzzer

void setup() {
  Serial.begin(115200);              // Monitor serial pentru debugging
  pinMode(IR_SENSOR_PIN, INPUT);     // Senzor IR ca intrare
  pinMode(BUZZER_PIN, OUTPUT);       // Buzzer ca ieșire
}

void loop() {
  int obstacleDetected = digitalRead(IR_SENSOR_PIN);  // Citește senzorul IR

  if (obstacleDetected == LOW) { // LOW = obstacol detectat (la majoritatea modulelor IR)
    Serial.println("Obstacol detectat!");
    digitalWrite(BUZZER_PIN, HIGH);  // Pornește buzzer-ul
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Oprește buzzer-ul
  }

  delay(100); // Mică pauză pentru stabilitate
}