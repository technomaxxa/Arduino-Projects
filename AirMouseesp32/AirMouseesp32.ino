//Esp32 version 2.0.17

#include <BleMouse.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

BleMouse bleMouse("AiR Mouse by @realmagix_");
Adafruit_MPU6050 mpu;

// Button pins
#define LEFT_CLICK_PIN   18
#define RIGHT_CLICK_PIN  19
#define SCROLL_UP_PIN    14
#define SCROLL_DOWN_PIN  27
#define BACK_BUTTON_PIN  26  

// Base sensitivity and threshold
float baseSensitivity = 10.0;  // Adjust for overall speed
float threshold       = 0.01;  // Deadzone to avoid jitter

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE Mouse with MPU6050 (Simple Version)");

  // Start BLE
  bleMouse.begin();

  // Start MPU
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found, check wiring!");
    while (1) delay(10);
  }

  // Configure MPU ranges
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Buttons as input with pullups
  pinMode(LEFT_CLICK_PIN, INPUT_PULLUP);
  pinMode(RIGHT_CLICK_PIN, INPUT_PULLUP);
  pinMode(SCROLL_UP_PIN, INPUT_PULLUP);
  pinMode(SCROLL_DOWN_PIN, INPUT_PULLUP);
  pinMode(BACK_BUTTON_PIN, INPUT_PULLUP);  

  Serial.println("Setup complete, waiting for BLE connection...");
}

void loop() {
  if (bleMouse.isConnected()) {
    // --- MPU6050 Gyro Movement ---
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float gyroX = g.gyro.x; // Roll
    float gyroY = g.gyro.y; // Pitch
    float gyroZ = g.gyro.z; // Yaw

    float moveX = gyroZ; // horizontal
    float moveY = gyroY; // vertical

    // Deadzone filter
    if (fabs(moveX) < threshold) moveX = 0;
    if (fabs(moveY) < threshold) moveY = 0;

    // Dynamic sensitivity scaling
    float speed = sqrt(moveX * moveX + moveY * moveY);
    float dynamicSensitivity = baseSensitivity * (1 + speed * 0.2);

    moveX *= dynamicSensitivity;
    moveY *= dynamicSensitivity + 2;

    if ((int)moveX != 0 || (int)moveY != 0) {
      bleMouse.move((int)-moveX, (int)moveY); // invert X for natural feel
    }

    // --- Button Actions ---
    if (digitalRead(LEFT_CLICK_PIN) == LOW) {
      bleMouse.press(MOUSE_LEFT);
    } else {
      bleMouse.release(MOUSE_LEFT);
    }

    if (digitalRead(RIGHT_CLICK_PIN) == LOW) {
      bleMouse.press(MOUSE_RIGHT);
    } else {
      bleMouse.release(MOUSE_RIGHT);
    }

    if (digitalRead(SCROLL_UP_PIN) == LOW) {
      bleMouse.move(0, 0, 1);
      delay(150);
    }

    if (digitalRead(SCROLL_DOWN_PIN) == LOW) {
      bleMouse.move(0, 0, -1);
      delay(150);
    }

    if (digitalRead(BACK_BUTTON_PIN) == LOW) {
      bleMouse.press(MOUSE_BACK);
    } else {
      bleMouse.release(MOUSE_BACK);
    }
  }

  delay(5); // small delay for smoother control
}
