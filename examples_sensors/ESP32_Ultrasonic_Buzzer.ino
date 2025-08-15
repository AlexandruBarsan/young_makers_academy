// Definirea pinilor conectați la senzorul ultrasonic și buzzer
#define TRIG_PIN 5       // Pinul de TRIGGER al senzorului ultrasonic
#define ECHO_PIN 18      // Pinul de ECHO al senzorului ultrasonic
#define BUZZER_PIN 23    // Pinul conectat la buzzer (pasiv)

long duration;           // Durata semnalului ultrasonic (în microsecunde)
float distance;          // Distanța calculată (în centimetri)

void setup() {
  Serial.begin(115200);              // Inițializează comunicarea serială pentru debugging
  pinMode(TRIG_PIN, OUTPUT);         // Setează TRIG ca ieșire
  pinMode(ECHO_PIN, INPUT);          // Setează ECHO ca intrare
  pinMode(BUZZER_PIN, OUTPUT);       // Setează pinul buzzerului ca ieșire
}

void loop() {
  // Trimite un impuls scurt de 10 microsecunde către TRIG pentru a porni măsurătoarea
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);             // Pauză scurtă pentru siguranță
  digitalWrite(TRIG_PIN, HIGH);     // Trimite semnalul TRIG
  delayMicroseconds(10);            // Menține semnalul 10 μs
  digitalWrite(TRIG_PIN, LOW);      // Oprește TRIG

  // Citește durata semnalului de ecou reflectat
  duration = pulseIn(ECHO_PIN, HIGH);       // Măsoară cât timp semnalul ECHO rămâne HIGH

  // Conversie din microsecunde în centimetri
  // Formula: viteza sunetului (0.034 cm/μs), împărțit la 2 (dus-întors)
  distance = duration * 0.034 / 2;

  // Afișează distanța în consolă pentru monitorizare
  Serial.print("Distanta: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Verifică dacă obiectul este la mai puțin de 30 cm
  if (distance <= 30.0 && distance > 0) {
    // Cu cât obiectul este mai aproape, cu atât sunetele sunt mai dese
    // 'map' transformă distanța între 0–30 cm într-un delay între 50–500 ms
    int delayTime = map(distance, 0, 30, 50, 500);

    // Generează un sunet la 2000 Hz timp de 50 ms
    tone(BUZZER_PIN, 2000);
    delay(50);  // Durata sunetului

    // Oprește sunetul
    noTone(BUZZER_PIN);

    // Pauză variabilă în funcție de distanță
    delay(delayTime);
  } else {
    // Dacă distanța e mai mare de 30 cm, nu face nimic (buzzer oprit)
    noTone(BUZZER_PIN);
    delay(200); // Pauză generală de 200 ms
  }
}