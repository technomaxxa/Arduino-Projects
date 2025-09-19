/*****************************************************************************************
*   Project Name : 16 Channel Chaser with Nano (v1.0)
*   Filename     : 16channelchasernanov1.ino
*   Created      : 25/08/2025
*   Last Modified: 29/08/2025
*   Author       : @technomaxxa
*
*   --------------------------------------------------------------------------------------
*   License Notice:
*
*   This software is provided "a chaser made with arduino nano microcontroller", without warranty of any kind, express or implied.
*   Permission is granted to use, copy, modify, and distribute this software for personal,
*   educational, or commercial purposes, provided that this header and license notice are
*   retained in all copies.
*
*   The author @technomaxxa assumes no responsibility or liability for any damages or
*   issues arising from the use of this software, either directly or indirectly.
*
*   --------------------------------------------------------------------------------------
*   Features:
*   - Designed for Arduino Nano
*   - Supports 16 channel LED outputs
*   - Includes 20 unique chasing effects
*   - Adjustable chase speed/delay
*
******************************************************************************************/
//this is a active low chaser (+are ground)

const uint8_t leds[] = {
  2, 3, 4, 5, 6, 7, 8, 9,
  10, 11, 12, A3, A2, A1, A0, 13
};
const uint8_t NUM_LEDS = sizeof(leds) / sizeof(leds[0]);

void setup() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH); // turn off all LEDs initially (active low)
  }
  randomSeed(analogRead(A5)); // seed random with floating analog pin
}

void loop() {
  uint8_t pattern = random(1, 21); // random pattern 1 to 20
  uint8_t repeats = random(5, 8);  // repeat 5 to 7 times

  switch (pattern) {
    case 1: pattern1_simpleLeftToRight(repeats); break;
    case 2: pattern2_rightToLeft(repeats); break;
    case 3: pattern3_bounce(repeats); break;
    case 6: pattern6_centerOutward(repeats); break;
    case 7: pattern7_everySecondLED(repeats); break;
    case 8: pattern8_runningPairSpacedBy2(repeats); break;
    case 9: pattern9_fillLeftToRight(repeats); break;
    case 10: pattern10_fillRightToLeft(repeats); break;
    case 11: pattern11_alternateBlink(repeats); break;
    case 12: pattern12_blinkAll(repeats); break;
    case 13: pattern13_moving3WideBar(repeats); break;
    case 14: pattern14_knightRider(repeats); break;
    case 15: pattern15_randomLED(repeats); break;
    case 16: pattern16_randomFill(repeats); break;
    case 17: pattern17_rippleOutwardFromCenter(repeats); break;
    case 18: pattern18_rippleInwardToCenter(repeats); break;
    case 19: pattern19_tripleStepper(repeats); break;
    case 20: pattern20_flashHalves(repeats); break;
    default: break;
  }
}

// Helper functions to turn LEDs on/off
void ledOn(uint8_t index) {
  digitalWrite(leds[index], LOW);
}
void ledOff(uint8_t index) {
  digitalWrite(leds[index], HIGH);
}
void allOff() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) ledOff(i);
}
void allOn() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) ledOn(i);
}

// Pattern 1: simple left-to-right
void pattern1_simpleLeftToRight(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      delay(100);
    }
  }
}

// Pattern 2: right-to-left
void pattern2_rightToLeft(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (int i = NUM_LEDS - 1; i >= 0; i--) {
      allOff();
      ledOn(i);
      delay(100);
    }
  }
}

// Pattern 3: bounce
void pattern3_bounce(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      delay(80);
    }
    for (int i = NUM_LEDS - 2; i > 0; i--) {
      allOff();
      ledOn(i);
      delay(80);
    }
  }
}

// Pattern 6: center outward
void pattern6_centerOutward(uint8_t repeats) {
  uint8_t center1 = NUM_LEDS / 2 - 1;
  uint8_t center2 = NUM_LEDS / 2;
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t offset = 0; offset <= center1; offset++) {
      allOff();
      if (center1 - offset < NUM_LEDS) ledOn(center1 - offset);
      if (center2 + offset < NUM_LEDS) ledOn(center2 + offset);
      delay(120);
    }
  }
}

// Pattern 7: every second LED
void pattern7_everySecondLED(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    allOff();
    for (uint8_t i = 0; i < NUM_LEDS; i += 2) {
      ledOn(i);
    }
    delay(300);
    allOff();
    for (uint8_t i = 1; i < NUM_LEDS; i += 2) {
      ledOn(i);
    }
    delay(300);
  }
}

// Pattern 8: running pair spaced by 2
void pattern8_runningPairSpacedBy2(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      uint8_t second = (i + 3) % NUM_LEDS; // spaced by 2 means gap of 2 LEDs, so +3
      ledOn(second);
      delay(150);
    }
  }
}

// Pattern 9: fill left to right
void pattern9_fillLeftToRight(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    allOff();
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      ledOn(i);
      delay(100);
    }
    delay(300);
    allOff();
  }
}

// Pattern 10: fill right to left
void pattern10_fillRightToLeft(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    allOff();
    for (int i = NUM_LEDS - 1; i >= 0; i--) {
      ledOn(i);
      delay(100);
    }
    delay(300);
    allOff();
  }
}

// Pattern 11: alternate blink
void pattern11_alternateBlink(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    allOff();
    for (uint8_t i = 0; i < NUM_LEDS; i += 2) ledOn(i);
    delay(300);
    allOff();
    for (uint8_t i = 1; i < NUM_LEDS; i += 2) ledOn(i);
    delay(300);
  }
}

// Pattern 12: blink all
void pattern12_blinkAll(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats * 2; r++) {
    if (r % 2 == 0) allOn();
    else allOff();
    delay(250);
  }
}

// Pattern 13: moving 3-wide bar
void pattern13_moving3WideBar(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn((i + 1) % NUM_LEDS);
      ledOn((i + 2) % NUM_LEDS);
      delay(120);
    }
  }
}

// Pattern 14: Knight Rider (comet with tail)
void pattern14_knightRider(uint8_t repeats) {
  const uint8_t tailLength = 4;
  for (uint8_t r = 0; r < repeats; r++) {
    for (int i = 0; i < NUM_LEDS * 2; i++) {
      allOff();
      for (uint8_t t = 0; t < tailLength; t++) {
        int pos = i - t;
        if (pos < 0) pos += NUM_LEDS;
        if (pos < NUM_LEDS) {
          // dim tail by turning on/off quickly (simulate brightness)
          if (t == 0) ledOn(pos);
          else if (t == 1 && (millis() / 100) % 2 == 0) ledOn(pos);
          else if (t == 2 && (millis() / 200) % 2 == 0) ledOn(pos);
          else if (t == 3 && (millis() / 300) % 2 == 0) ledOn(pos);
        }
      }
      delay(80);
    }
  }
}

// Pattern 15: random LED
void pattern15_randomLED(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats * 5; r++) {
    allOff();
    ledOn(random(NUM_LEDS));
    delay(100);
  }
  allOff();
}

// Pattern 16: random fill
void pattern16_randomFill(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    allOff();
    uint8_t count = 0;
    while (count < NUM_LEDS) {
      uint8_t idx = random(NUM_LEDS);
      if (digitalRead(leds[idx]) == HIGH) { // off
        ledOn(idx);
        count++;
        delay(80);
      }
    }
    delay(300);
    allOff();
  }
}

// Pattern 17: ripple outward from center
void pattern17_rippleOutwardFromCenter(uint8_t repeats) {
  uint8_t center1 = NUM_LEDS / 2 - 1;
  uint8_t center2 = NUM_LEDS / 2;
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t offset = 0; offset <= center1; offset++) {
      allOff();
      if (center1 - offset < NUM_LEDS) ledOn(center1 - offset);
      if (center2 + offset < NUM_LEDS) ledOn(center2 + offset);
      delay(100);
    }
    for (int offset = center1 - 1; offset >= 0; offset--) {
      allOff();
      if (center1 - offset < NUM_LEDS) ledOn(center1 - offset);
      if (center2 + offset < NUM_LEDS) ledOn(center2 + offset);
      delay(100);
    }
  }
}

// Pattern 18: ripple inward to center
void pattern18_rippleInwardToCenter(uint8_t repeats) {
  uint8_t center1 = NUM_LEDS / 2 - 1;
  uint8_t center2 = NUM_LEDS / 2;
  for (uint8_t r = 0; r < repeats; r++) {
    for (int offset = center1; offset >= 0; offset--) {
      allOff();
      if (center1 - offset < NUM_LEDS) ledOn(center1 - offset);
      if (center2 + offset < NUM_LEDS) ledOn(center2 + offset);
      delay(100);
    }
    for (uint8_t offset = 1; offset <= center1; offset++) {
      allOff();
      if (center1 - offset < NUM_LEDS) ledOn(center1 - offset);
      if (center2 + offset < NUM_LEDS) ledOn(center2 + offset);
      delay(100);
    }
  }
}

// Pattern 19: triple stepper
void pattern19_tripleStepper(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t step = 0; step < 3; step++) {
      allOff();
      for (uint8_t i = step; i < NUM_LEDS; i += 3) {
        ledOn(i);
      }
      delay(200);
    }
  }
}

// Pattern 20: flash halves
void pattern20_flashHalves(uint8_t repeats) {
  uint8_t half = NUM_LEDS / 2;
  for (uint8_t r = 0; r < repeats * 4; r++) {
    allOff();
    if (r % 2 == 0) {
      for (uint8_t i = 0; i < half; i++) ledOn(i);
    } else {
      for (uint8_t i = half; i < NUM_LEDS; i++) ledOn(i);
    }
    delay(250);
  }
}
