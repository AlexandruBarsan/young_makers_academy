#define PIR_PIN 4         // Pin conectat la senzorul PIR (OUT)
#define BUZZER_PIN 23     // Pin conectat la buzzer (activ)

void setup() {
  Serial.begin(115200);              // Monitor serial pentru debugging
  pinMode(PIR_PIN, INPUT);           // Senzor PIR ca intrare
  pinMode(BUZZER_PIN, OUTPUT);       // Buzzer ca ieșire
}

void loop() {
  int motionDetected = digitalRead(PIR_PIN);  // Citește starea senzorului

  if (motionDetected == HIGH) {
    Serial.println("Miscare detectata!");
    digitalWrite(BUZZER_PIN, HIGH);          // Pornește buzzer-ul
    delay(1000);                              // Sună 1 secundă
    digitalWrite(BUZZER_PIN, LOW);           // Oprește buzzer-ul
  } else {
    digitalWrite(BUZZER_PIN, LOW);           // Buzzer oprit
  }

  delay(200);  // Pauză între citiri
}
