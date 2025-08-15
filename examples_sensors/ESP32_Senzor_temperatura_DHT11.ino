#include "DHT.h"

#define DHTPIN 4        // Pinul de semnal al senzorului conectat la ESP32
#define DHTTYPE DHT11     // Tipul senzorului (DHT11 sau DHT22)

DHT dht(DHTPIN, DHTTYPE); // Inițializează senzorul

void setup() {
  Serial.begin(115200);   // Monitor serial
  dht.begin();            // Pornește senzorul
  Serial.println("Pornire senzor DHT11...");
}

void loop() {
  // Citește umiditatea
  float humidity = dht.readHumidity();
  // Citește temperatura în Celsius
  float temperature = dht.readTemperature();

  // Verifică dacă citirea este validă
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Eroare la citirea de la senzorul DHT11!");
    delay(2000);
    return;
  }

  // Afișează valorile
  Serial.print("Umiditate: ");
  Serial.print(humidity);
  Serial.print(" %\t");

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(2000); // Așteaptă 2 secunde între citiri
}
