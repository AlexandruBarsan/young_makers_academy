#include <ESP32Servo.h>
#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// Motor pin definitions
#define ENA_FL 12  // Front Left
#define ENA_FR 27  // Front Right
#define ENA_BL 13  // Back Left
#define ENA_BR 26  // Back Right

#define IN1_FL 2
#define IN2_FL 15
#define IN1_FR 19
#define IN2_FR 18
#define IN1_BL 16
#define IN2_BL 4
#define IN1_BR 5
#define IN2_BR 17
// De schimbat intre ele 

// 17 5 18 19  // 15 2 4 16


#define SERVOMIN_X 0 // Puls minims
#define SERVOMAX_X 50 // Puls maxim
#define SERVOMIN_Y 0 // Puls minim
#define SERVOMAX_Y 50 // Puls maxim
#define SERVOMIN_Z 0 // Puls minim
#define SERVOMAX_Z 50 // Puls maxim

#define SERVO_PIN_X 25
#define SERVO_PIN_Y 33
#define SERVO_PIN_Z 32

int servo_pos_X = 0;  // Poziția inițială a primului servo
int servo_pos_Y = 0;  // Poziția inițială a celui de-al doilea servo
int servo_pos_Z = 0;  // Poziția inițială a celui de-al treilea servo


#define DEADZONE 120

Servo myServo_X;
Servo myServo_Y;
Servo myServo_Z;

void setMotor(int en, int in1, int in2, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  analogWrite(en, abs(speed));
}

void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
      ControllerProperties properties = ctl->getProperties();
      Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id, properties.product_id);
      myControllers[i] = ctl;
      foundEmptySlot = true;
      break;
    }
  }

  if (!foundEmptySlot) {
    Serial.println("CALLBACK: Controller connected, but could not found empty slot");
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  bool foundController = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
      myControllers[i] = nullptr;
      foundController = true;
      break;
    }
  }

  if (!foundController) {
    Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
  }
}

void dumpGamepad(ControllerPtr ctl) {
  Serial.printf(
    "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
    "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
    ctl->index(),
    ctl->dpad(),
    ctl->buttons(),
    ctl->axisX(),
    ctl->axisY(),
    ctl->axisRX(),
    ctl->axisRY(),
    ctl->brake(),
    ctl->throttle(),
    ctl->miscButtons(),
    ctl->gyroX(),
    ctl->gyroY(),
    ctl->gyroZ(),
    ctl->accelX(),
    ctl->accelY(),
    ctl->accelZ()
  );
}

void processGamepad(ControllerPtr ctl) {
  int x = ctl->axisX(); // Left joystick X
  int y = ctl->axisY(); // Left joystick Y
  int servo_X = ctl->axisRX(); // Left joystick X
  int servo_Y = ctl->axisRY(); // Left joystick Y
  int servo_Z = ctl->throttle(); // Left joystick Y
  int butoane_dreapta = ctl->buttons();
  int speedFL, speedFR, speedBL, speedBR;

  // Deadzone
  if (abs(x) < DEADZONE) x = 0;
  if (abs(y) < DEADZONE) y = 0;

  // Calculați vitezele pentru roțile mecanum
  speedFL = y - x;
  speedFR = y + x;
  speedBL = y - x;
  speedBR = y + x;


  // Mișcare la stânga cu butonul PĂTRAT (square)
  if (butoane_dreapta & 0x0004) {
    // Translatie laterala la stanga (exemplu pentru mecanum wheels)
    speedFL = 250;
    speedFR = -250;
    speedBL = -250;
    speedBR = 250;
  }

  // Mișcare la dreapta cu butonul CERC (circle)
  else if (butoane_dreapta & 0x0002) {
    // Translatie laterala la dreapta (exemplu pentru mecanum wheels)
    speedFL = -250;
    speedFR = 250;
    speedBL = 250;
    speedBR = -250;
  }

  // Apply speeds to motors
  setMotor(ENA_FL, IN1_FL, IN2_FL, speedFL);
  setMotor(ENA_FR, IN1_FR, IN2_FR, speedFR);
  setMotor(ENA_BL, IN1_BL, IN2_BL, speedBL);
  setMotor(ENA_BR, IN1_BR, IN2_BR, speedBR);


  if (servo_X > DEADZONE) {
    servo_pos_X += 3;  // Crește poziția încet
  }
  // Dacă axa X a joystick-ului este mai mică decât -DEADZONE
  else if (servo_X < -DEADZONE) {
    servo_pos_X -= 3;  // Scade poziția încet
  }

  // Dacă axa Y a joystick-ului este mai mare decât DEADZONE
  if (servo_Y > DEADZONE) {
    servo_pos_Y += 3;  // Crește poziția încet
  }
  // Dacă axa Y a joystick-ului este mai mică decât -DEADZONE
  else if (servo_Y < -DEADZONE) {
    servo_pos_Y -= 3;  // Scade poziția încet
  }
  if (servo_Z > DEADZONE) {
    servo_pos_Z += 15;  // Crește poziția încet
  }
  // Dacă axa Y a joystick-ului este mai mică decât -DEADZONE
  else if (servo_Z < DEADZONE) {
    servo_pos_Z -= 15;  // Scade poziția încet
  }

  servo_pos_X = constrain(servo_pos_X, SERVOMIN_X, SERVOMAX_X);
  servo_pos_Y = constrain(servo_pos_Y, SERVOMIN_Y, SERVOMAX_Y);
  servo_pos_Z = constrain(servo_pos_Z, SERVOMIN_Z, SERVOMAX_X);

  myServo_X.write(servo_pos_X);
  myServo_Y.write(servo_pos_Y);
  myServo_Z.write(servo_pos_Z);

  delay(15);

  dumpGamepad(ctl);
}

void processControllers() {
  for (auto myController : myControllers) {
    if (myController && myController->isConnected()) {
      if (myController->isGamepad()) {
        processGamepad(myController);
      }
      else {
        Serial.println("Unsupported controller");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Motor pin setup
  pinMode(ENA_FL, OUTPUT);
  pinMode(ENA_FR, OUTPUT);
  pinMode(ENA_BL, OUTPUT);
  pinMode(ENA_BR, OUTPUT);

  pinMode(IN1_FL, OUTPUT);
  pinMode(IN2_FL, OUTPUT);
  pinMode(IN1_FR, OUTPUT);
  pinMode(IN2_FR, OUTPUT);
  pinMode(IN1_BL, OUTPUT);
  pinMode(IN2_BL, OUTPUT);
  pinMode(IN1_BR, OUTPUT);
  pinMode(IN2_BR, OUTPUT);

  myServo_X.attach(SERVO_PIN_X);
  myServo_Y.attach(SERVO_PIN_Y);
  myServo_Z.attach(SERVO_PIN_Z);
  delay(10); 

  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t* addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  // Set up Bluepad32 callbacks
  BP32.setup(&onConnectedController, &onDisconnectedController);

  BP32.forgetBluetoothKeys();
  BP32.enableVirtualDevice(false);
}

void loop() {
  bool dataUpdated = BP32.update();
  if (dataUpdated)
    processControllers();


  delay(20);
}