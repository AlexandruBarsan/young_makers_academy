const int trigPin = 5;
const int echoPin = 18;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Pornim masurarea distantei...");
}

void loop() {
  long duratie;
  float distanta;

  // Trimitem un puls ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Masuram timpul pana la intoarcerea ecoului
  duratie = pulseIn(echoPin, HIGH);

  // Calculam distanta in cm
  distanta = duratie * 0.034 / 2;

  Serial.print("Distanta masurata: ");
  Serial.print(distanta);
  Serial.println(" cm");

  delay(500);
}