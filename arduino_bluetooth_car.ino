#include <Arduino.h>
#include <PS4Controller.h>

// Motor A pins
const int motorA_IN1 = 14;
const int motorA_IN2 = 27;
const int motorA_EN = 26;

// Motor B pins
const int motorB_IN3 = 25;
const int motorB_IN4 = 33;
const int motorB_EN = 32;

// The Attack Button
const int attack = 22;

// PWM channels
const int motorA_PWM_channel = 0;
const int motorB_PWM_channel = 1;

// Variables for toggle logic of attack weapon
bool attackState = false;
bool lastXButtonState = false;

// PWM properties
const int freq = 5000;
const int pwm_resolution = 8;

// Deadzone
const int joystickDeadZone = 10;

void motorForward(int speed);
void motorBackward(int speed);
void motorTurnRight(int speed);
void motorTurnLeft(int speed);
void motorStop();

void setup() {
  Serial.begin(115200);

  // Motor pin setup
  pinMode(motorA_IN1, OUTPUT);
  pinMode(motorA_IN2, OUTPUT);
  pinMode(motorB_IN3, OUTPUT);
  pinMode(motorB_IN4, OUTPUT);
  pinMode(attack, OUTPUT);

  // PWM setup
  ledcSetup(motorA_PWM_channel, freq, pwm_resolution);
  ledcAttachPin(motorA_EN, motorA_PWM_channel);

  ledcSetup(motorB_PWM_channel, freq, pwm_resolution);
  ledcAttachPin(motorB_EN, motorB_PWM_channel);

  motorStop();  // Motors off initially

  if (!PS4.begin("94:54:C5:76:B2:84")) {
    Serial.println("❌ Failed to start PS4 Bluetooth");
    while (1);
  }

  Serial.println("✅ PS4 Bluetooth started. Waiting for controller...");
}

void loop() {
  if (PS4.isConnected()) {
    int16_t joystickY = PS4.LStickY();  // Forward/backward
    int16_t joystickX = PS4.LStickX();  // Left/right

    if (abs(joystickY) > joystickDeadZone) {
      int speed = map(abs(joystickY), joystickDeadZone, 127, 0, 255);
      speed = constrain(speed, 0, 255);
      if (joystickY < 0) {
        motorBackward(speed);
        Serial.print("⬆ Moving forward, speed: ");
        Serial.println(speed);
      } else {
        motorForward(speed);
        Serial.print("⬇ Moving backward, speed: ");
        Serial.println(speed);
      }
    } else if (abs(joystickX) > joystickDeadZone) {
      int speed = map(abs(joystickX), joystickDeadZone, 127, 0, 255);
      speed = constrain(speed, 0, 255);
      if (joystickX < 0) {
        motorTurnLeft(speed);
        Serial.print("⬅ Turning left, speed: ");
        Serial.println(speed);
      } else {
        motorTurnRight(speed);
        Serial.print("➡ Turning right, speed: ");
        Serial.println(speed);
      }
    } else {
      motorStop();
      Serial.println("🛑 Motors stopped (in deadzone)");
    }

    // Attack weapon toggle with X button (Cross)
    bool currentXButtonState = PS4.Cross();
    if (currentXButtonState && !lastXButtonState) {
      attackState = !attackState;
      digitalWrite(attack, attackState ? HIGH : LOW);
      Serial.print("🔘 Attack Weapon ");
      Serial.println(attackState ? "ON" : "OFF");
    }
    lastXButtonState = currentXButtonState;

  } else {
    motorStop();
    digitalWrite(attack, LOW);
    Serial.println("🔌 No controller connected");
  }

  delay(50);
}

// Motor control functions
void motorForward(int speed) {
  digitalWrite(motorA_IN1, HIGH);
  digitalWrite(motorA_IN2, LOW);
  digitalWrite(motorB_IN3, HIGH);
  digitalWrite(motorB_IN4, LOW);
  ledcWrite(motorA_PWM_channel, speed);
  ledcWrite(motorB_PWM_channel, speed);
}

void motorBackward(int speed) {
  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, HIGH);
  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, HIGH);
  ledcWrite(motorA_PWM_channel, speed);
  ledcWrite(motorB_PWM_channel, speed);
}

void motorTurnLeft(int speed) {
  digitalWrite(motorA_IN1, HIGH);
  digitalWrite(motorA_IN2, LOW);
  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, HIGH);
  ledcWrite(motorA_PWM_channel, speed);
  ledcWrite(motorB_PWM_channel, speed);
}

void motorTurnRight(int speed) {
  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, HIGH);
  digitalWrite(motorB_IN3, HIGH);
  digitalWrite(motorB_IN4, LOW);
  ledcWrite(motorA_PWM_channel, speed);
  ledcWrite(motorB_PWM_channel, speed);
}

void motorStop() {
  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, LOW);
  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, LOW);
  ledcWrite(motorA_PWM_channel, 0);
  ledcWrite(motorB_PWM_channel, 0);
}