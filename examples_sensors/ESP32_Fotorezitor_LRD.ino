#define LDR_PIN 4   // Pinul analogic conectat la ieșirea modulului LDR

void setup() {
  Serial.begin(115200); // Deschide comunicarea serială
  pinMode(LDR_PIN, INPUT); // Pinul este intrare
  Serial.println("Pornire senzor LDR...");
}

void loop() {
  int valoareLDR = analogRead(LDR_PIN); // Citește lumina (valoare între 0 și 4095)
  
  Serial.print("Luminozitate (LDR): ");
  Serial.println(valoareLDR);

  delay(1000); // Așteaptă 1 sec. între citiri
}
