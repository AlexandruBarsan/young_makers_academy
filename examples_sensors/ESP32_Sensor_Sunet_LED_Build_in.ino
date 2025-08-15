#define SOUND_SENSOR_PIN 4     // Pinul D0 de la KY-037
#define LED_BUILTIN 2           // LED-ul onboard ESP32

bool ledState = false;
bool lastSoundState = LOW;

void setup() {
  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  // Inițial stins
  Serial.begin(115200);
}

void loop() {
  // Citim starea senzorului de sunet
  bool currentSound = digitalRead(SOUND_SENSOR_PIN);

  // Detectăm o tranziție de la LOW la HIGH (adică o bătaie din palme)
  if (currentSound == HIGH && lastSoundState == LOW) {
    // Schimbăm starea LED-ului
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);

    Serial.print("Detectat sunet! LED ");
    Serial.println(ledState ? "APRINS" : "STINS");

    delay(300); // Debounce: ignoră alte bătăi apropiate
  }

  // Memorăm ultima stare a sunetului
  lastSoundState = currentSound;
}
