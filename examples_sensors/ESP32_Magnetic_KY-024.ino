#define HALL_ANALOG_PIN 4  // Pinul ESP32 conectat la A0 de la KY-024

void setup() {
  Serial.begin(115200);     // Deschide comunicarea serială
  pinMode(HALL_ANALOG_PIN, INPUT);  // Pin ca intrare
  Serial.println("Pornire citire senzor KY-024 (analog)...");
}

void loop() {
  int valoare = analogRead(HALL_ANALOG_PIN); // Citește valoarea analogică (0-4095)
  
  Serial.print("Valoare camp magnetic: ");
  Serial.println(valoare);

  delay(500); // Așteaptă jumătate de secundă
}
