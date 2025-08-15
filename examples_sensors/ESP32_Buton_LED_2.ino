int ledPin = 2;
int butonPin = 4;

void setup() {
  pinMode(ledPin, OUTPUT);         // LED-ul este o ieșire
  pinMode(butonPin, INPUT_PULLUP); // Butonul este o intrare cu pull-up

  Serial.begin(115200);            // Pornim comunicarea cu Serial Monitor
  Serial.println("Sistem pornit. Asteptam apasarea butonului...");
}

void loop() {
  int stareButon = digitalRead(butonPin);

  if (stareButon == LOW) {         // LOW inseamna ca butonul este apasat
    digitalWrite(ledPin, HIGH);    // Aprindem LED-ul
    Serial.println("Buton APASAT - LED aprins");
  } else {
    digitalWrite(ledPin, LOW);     // Stingem LED-ul
    Serial.println("Buton NEAPASAT - LED stins");
  }

  delay(200); // un mic delay pentru a nu afisa prea multe mesaje pe secunda
}