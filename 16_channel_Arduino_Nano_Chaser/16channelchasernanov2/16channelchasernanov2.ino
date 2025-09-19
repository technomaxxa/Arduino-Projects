/*****************************************************************************************
*   Project Name : 16 Channel Chaser with Nano (v2.0)
*   Filename     : 16channelchasernanov2.ino
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
*   - Includes 50 unique chasing effects
*   - Adjustable chase speed/delay
*
******************************************************************************************/
//this is a active low chaser (+are ground)



// LED pins as per your setup
const uint8_t leds[] = {2,3,4,5,6,7,8,9,10,11,12,A3,A2,A1,A0,13};
const uint8_t NUM_LEDS = sizeof(leds)/sizeof(leds[0]);

// Forward declarations of pattern functions
typedef void (*PatternFunc)(uint8_t repeats);
void pattern1_simpleLeftToRight(uint8_t repeats);
void pattern2_simpleRightToLeft(uint8_t repeats);
void pattern3_bounce(uint8_t repeats);
void pattern4_doubleBounce(uint8_t repeats);
void pattern5_tripleBounce(uint8_t repeats);
void pattern6_centerOutward(uint8_t repeats);
void pattern7_outwardInwardRepeat(uint8_t repeats);
void pattern8_evenLEDs(uint8_t repeats);
void pattern9_oddLEDs(uint8_t repeats);
void pattern10_runningPairSideBySide(uint8_t repeats);
void pattern11_runningPairSpaced1(uint8_t repeats);
void pattern12_runningPairSpaced2(uint8_t repeats);
void pattern13_runningTrio(uint8_t repeats);
void pattern14_running4WideBlock(uint8_t repeats);
void pattern15_expandingBarLeftToRight(uint8_t repeats);
void pattern16_expandingBarRightToLeft(uint8_t repeats);
void pattern17_compressingBarLeftToRight(uint8_t repeats);
void pattern18_compressingBarRightToLeft(uint8_t repeats);
void pattern19_fillLeftToRightThenClear(uint8_t repeats);
void pattern20_fillRightToLeftThenClear(uint8_t repeats);
void pattern21_blinkAllTogether(uint8_t repeats);
void pattern22_alternateBlinkHalves(uint8_t repeats);
void pattern23_alternateBlinkOddsEvens(uint8_t repeats);
void pattern24_alternateBlinkThirds(uint8_t repeats);
void pattern25_blinkQuarters(uint8_t repeats);
void pattern26_randomSingleBlink(uint8_t repeats);
void pattern27_randomPairBlink(uint8_t repeats);
void pattern28_randomTrioBlink(uint8_t repeats);
void pattern29_sparkleFast(uint8_t repeats);
void pattern30_fireflySlow(uint8_t repeats);
void pattern31_twoGroupsOpposite(uint8_t repeats);
void pattern32_fourGroupsMeetCenter(uint8_t repeats);
void pattern33_fourGroupsOutwardCenter(uint8_t repeats);
void pattern34_chaseWithMirror(uint8_t repeats);
void pattern35_dualParallelChases(uint8_t repeats);
void pattern36_spiralSimulated(uint8_t repeats);
void pattern37_stepWave(uint8_t repeats);
void pattern38_ladderFill(uint8_t repeats);
void pattern39_staircaseRise(uint8_t repeats);
void pattern40_staircaseFall(uint8_t repeats);
void pattern41_rippleOutwardSingle(uint8_t repeats);
void pattern42_rippleInwardSingle(uint8_t repeats);
void pattern43_knightRider1Tail(uint8_t repeats);
void pattern44_knightRider2TailFade(uint8_t repeats);
void pattern45_knightRider3TailFade(uint8_t repeats);
void pattern46_cometFadingTrailLeftToRight(uint8_t repeats);
void pattern47_cometFadingTrailRightToLeft(uint8_t repeats);
void pattern48_blinkBorderLEDs(uint8_t repeats);
void pattern49_blinkCenterLEDs(uint8_t repeats);
void pattern50_checkerboardFlicker(uint8_t repeats);

// Array of pattern functions
PatternFunc patterns[] = {
  pattern1_simpleLeftToRight,
  pattern2_simpleRightToLeft,
  pattern3_bounce,
  pattern4_doubleBounce,
  pattern5_tripleBounce,
  pattern6_centerOutward,
  pattern7_outwardInwardRepeat,
  pattern8_evenLEDs,
  pattern9_oddLEDs,
  pattern10_runningPairSideBySide,
  pattern11_runningPairSpaced1,
  pattern12_runningPairSpaced2,
  pattern13_runningTrio,
  pattern14_running4WideBlock,
  pattern15_expandingBarLeftToRight,
  pattern16_expandingBarRightToLeft,
  pattern17_compressingBarLeftToRight,
  pattern18_compressingBarRightToLeft,
  pattern19_fillLeftToRightThenClear,
  pattern20_fillRightToLeftThenClear,
  pattern21_blinkAllTogether,
  pattern22_alternateBlinkHalves,
  pattern23_alternateBlinkOddsEvens,
  pattern24_alternateBlinkThirds,
  pattern25_blinkQuarters,
  pattern26_randomSingleBlink,
  pattern27_randomPairBlink,
  pattern28_randomTrioBlink,
  pattern29_sparkleFast,
  pattern30_fireflySlow,
  pattern31_twoGroupsOpposite,
  pattern32_fourGroupsMeetCenter,
  pattern33_fourGroupsOutwardCenter,
  pattern34_chaseWithMirror,
  pattern35_dualParallelChases,
  pattern36_spiralSimulated,
  pattern37_stepWave,
  pattern38_ladderFill,
  pattern39_staircaseRise,
  pattern40_staircaseFall,
  pattern41_rippleOutwardSingle,
  pattern42_rippleInwardSingle,
  pattern43_knightRider1Tail,
  pattern44_knightRider2TailFade,
  pattern45_knightRider3TailFade,
  pattern46_cometFadingTrailLeftToRight,
  pattern47_cometFadingTrailRightToLeft,
  pattern48_blinkBorderLEDs,
  pattern49_blinkCenterLEDs,
  pattern50_checkerboardFlicker
};

const uint8_t NUM_PATTERNS = sizeof(patterns)/sizeof(patterns[0]);

void setup() {
  for (uint8_t i=0; i<NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH); // active low off
  }
  randomSeed(analogRead(A5));
}

void loop() {
  for (uint8_t p=0; p<NUM_PATTERNS; p++) {
    for (uint8_t r=0; r<3; r++) {
      patterns[p](1);
    }
  }
}

// Helper functions
void ledOn(uint8_t i) { digitalWrite(leds[i], LOW); }
void ledOff(uint8_t i) { digitalWrite(leds[i], HIGH); }
void allOff() { for(uint8_t i=0; i<NUM_LEDS; i++) ledOff(i); }
void allOn() { for(uint8_t i=0; i<NUM_LEDS; i++) ledOn(i); }

// ========== Pattern Implementations ==========

// 1. Simple left to right
void pattern1_simpleLeftToRight(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      delay(100);
    }
  }
}

// 2. Simple right to left
void pattern2_simpleRightToLeft(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (int i=NUM_LEDS-1; i>=0; i--) {
      allOff();
      ledOn(i);
      delay(100);
    }
  }
}

// 3. Bounce (ping-pong)
void pattern3_bounce(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      delay(80);
    }
    for (int i=NUM_LEDS-2; i>0; i--) {
      allOff();
      ledOn(i);
      delay(80);
    }
  }
}

// 4. Double bounce (two LEDs opposite ends)
void pattern4_doubleBounce(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn(NUM_LEDS - 1 - i);
      delay(100);
    }
    for (int i=NUM_LEDS-2; i>0; i--) {
      allOff();
      ledOn(i);
      ledOn(NUM_LEDS - 1 - i);
      delay(100);
    }
  }
}

// 5. Triple bounce (left, center, right)
void pattern5_tripleBounce(uint8_t repeats) {
  uint8_t center = NUM_LEDS / 2;
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<=center; i++) {
      allOff();
      ledOn(i);
      ledOn(center);
      ledOn(NUM_LEDS - 1 - i);
      delay(100);
    }
    for (int i=center-1; i>=0; i--) {
      allOff();
      ledOn(i);
      ledOn(center);
      ledOn(NUM_LEDS - 1 - i);
      delay(100);
    }
  }
}

// 6. Center outward
void pattern6_centerOutward(uint8_t repeats) {
  uint8_t center1 = NUM_LEDS/2 - 1;
  uint8_t center2 = NUM_LEDS/2;
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t offset=0; offset<=center1; offset++) {
      allOff();
      ledOn(center1 - offset);
      ledOn(center2 + offset);
      delay(120);
    }
  }
}

// 7. Outward inward repeat
void pattern7_outwardInwardRepeat(uint8_t repeats) {
  uint8_t center1 = NUM_LEDS/2 - 1;
  uint8_t center2 = NUM_LEDS/2;
  for (uint8_t r=0; r<repeats; r++) {
    // Outward
    for (uint8_t offset=0; offset<=center1; offset++) {
      allOff();
      ledOn(center1 - offset);
      ledOn(center2 + offset);
      delay(100);
    }
    // Inward
    for (int offset=center1-1; offset>=0; offset--) {
      allOff();
      ledOn(center1 - offset);
      ledOn(center2 + offset);
      delay(100);
    }
  }
}

// 8. Every second LED (even only)
void pattern8_evenLEDs(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    allOff();
    for (uint8_t i=0; i<NUM_LEDS; i+=2) ledOn(i);
    delay(300);
  }
}

// 9. Every second LED (odd only)
void pattern9_oddLEDs(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    allOff();
    for (uint8_t i=1; i<NUM_LEDS; i+=2) ledOn(i);
    delay(300);
  }
}

// 10. Running pair side by side
void pattern10_runningPairSideBySide(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn((i+1) % NUM_LEDS);
      delay(150);
    }
  }
}

// 11. Running pair spaced by 1 gap
void pattern11_runningPairSpaced1(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn((i+2) % NUM_LEDS);
      delay(150);
    }
  }
}

// 12. Running pair spaced by 2 gaps
void pattern12_runningPairSpaced2(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn((i+3) % NUM_LEDS);
      delay(150);
    }
  }
}

// 13. Running trio (3 wide block)
void pattern13_runningTrio(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn((i+1) % NUM_LEDS);
      ledOn((i+2) % NUM_LEDS);
      delay(150);
    }
  }
}

// 14. Running 4-wide block
void pattern14_running4WideBlock(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      for (uint8_t j=0; j<4; j++) {
        ledOn((i+j) % NUM_LEDS);
      }
      delay(150);
    }
  }
}

// 15. Expanding bar left to right
void pattern15_expandingBarLeftToRight(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    allOff();
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      ledOn(i);
      delay(100);
    }
    allOff();
  }
}

// 16. Expanding bar right to left
void pattern16_expandingBarRightToLeft(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    allOff();
    for (int i=NUM_LEDS-1; i>=0; i--) {
      ledOn(i);
      delay(100);
    }
    allOff();
  }
}

// 17. Compressing bar left to right
void pattern17_compressingBarLeftToRight(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=NUM_LEDS; i>0; i--) {
      allOff();
      for (uint8_t j=0; j<i; j++) {
        ledOn(j);
      }
      delay(100);
    }
    allOff();
  }
}

// 18. Compressing bar right to left
void pattern18_compressingBarRightToLeft(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (int i=NUM_LEDS; i>0; i--) {
      allOff();
      for (int j=NUM_LEDS-1; j>=NUM_LEDS - i; j--) {
        ledOn(j);
      }
      delay(100);
    }
    allOff();
  }
}

// 19. Fill left to right then clear
void pattern19_fillLeftToRightThenClear(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    allOff();
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      ledOn(i);
      delay(80);
    }
    delay(300);
    allOff();
  }
}

// 20. Fill right to left then clear
void pattern20_fillRightToLeftThenClear(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    allOff();
    for (int i=NUM_LEDS-1; i>=0; i--) {
      ledOn(i);
      delay(80);
    }
    delay(300);
    allOff();
  }
}

// 21. Blink all together
void pattern21_blinkAllTogether(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*2; r++) {
    if (r % 2 == 0) allOn();
    else allOff();
    delay(250);
  }
}

// 22. Alternate blink halves (left vs right)
void pattern22_alternateBlinkHalves(uint8_t repeats) {
  uint8_t half = NUM_LEDS / 2;
  for (uint8_t r=0; r<repeats*4; r++) {
    allOff();
    if (r % 2 == 0) {
      for (uint8_t i=0; i<half; i++) ledOn(i);
    } else {
      for (uint8_t i=half; i<NUM_LEDS; i++) ledOn(i);
    }
    delay(250);
  }
}

// 23. Alternate blink odds vs evens
void pattern23_alternateBlinkOddsEvens(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*4; r++) {
    allOff();
    if (r % 2 == 0) {
      for (uint8_t i=0; i<NUM_LEDS; i+=2) ledOn(i);
    } else {
      for (uint8_t i=1; i<NUM_LEDS; i+=2) ledOn(i);
    }
    delay(250);
  }
}

// 24. Alternate blink thirds (group of 5-5-6)
void pattern24_alternateBlinkThirds(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*6; r++) {
    allOff();
    uint8_t group = r % 3;
    if (group == 0) {
      for (uint8_t i=0; i<5; i++) ledOn(i);
    } else if (group == 1) {
      for (uint8_t i=5; i<10; i++) ledOn(i);
    } else {
      for (uint8_t i=10; i<NUM_LEDS; i++) ledOn(i);
    }
    delay(250);
  }
  }
  // 25. Blink quarters (4 LEDs each group)
void pattern25_blinkQuarters(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats * 8; r++) {
    allOff();
    uint8_t group = r % 4;
    for (uint8_t i = group * 4; i < (group + 1) * 4 && i < NUM_LEDS; i++) {
      ledOn(i);
    }
    delay(250);
  }
}

// 26. Random single blink
void pattern26_randomSingleBlink(uint8_t repeats) {
  for (uint16_t r = 0; r < repeats * 20; r++) {
    allOff();
    ledOn(random(NUM_LEDS));
    delay(100);
  }
  allOff();
}

// 27. Random pair blink
void pattern27_randomPairBlink(uint8_t repeats) {
  for (uint16_t r = 0; r < repeats * 15; r++) {
    allOff();
    uint8_t first = random(NUM_LEDS);
    ledOn(first);
    ledOn((first + 1) % NUM_LEDS);
    delay(150);
  }
  allOff();
}

// 28. Random trio blink
void pattern28_randomTrioBlink(uint8_t repeats) {
  for (uint16_t r = 0; r < repeats * 12; r++) {
    allOff();
    uint8_t first = random(NUM_LEDS);
    ledOn(first);
    ledOn((first + 1) % NUM_LEDS);
    ledOn((first + 2) % NUM_LEDS);
    delay(180);
  }
  allOff();
}

// 29. Sparkle effect (fast random)
void pattern29_sparkleFast(uint8_t repeats) {
  for (uint16_t r = 0; r < repeats * 50; r++) {
    uint8_t idx = random(NUM_LEDS);
    ledOn(idx);
    delay(30);
    ledOff(idx);
  }
  allOff();
}

// 30. Firefly blink (slow random hold)
void pattern30_fireflySlow(uint8_t repeats) {
  for (uint16_t r = 0; r < repeats * 20; r++) {
    uint8_t idx = random(NUM_LEDS);
    ledOn(idx);
    delay(random(200, 600));
    ledOff(idx);
    delay(random(100, 300));
  }
  allOff();
}

// 31. Two groups opposite directions
void pattern31_twoGroupsOpposite(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn(NUM_LEDS - 1 - i);
      delay(100);
    }
  }
}

// 32. Four groups meet in center
void pattern32_fourGroupsMeetCenter(uint8_t repeats) {
  uint8_t quarter = NUM_LEDS / 4;
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t i = 0; i <= quarter; i++) {
      allOff();
      ledOn(i);
      ledOn(quarter * 2 - i);
      ledOn(quarter * 2 + i);
      ledOn(NUM_LEDS - 1 - i);
      delay(120);
    }
  }
}

// 33. Four groups outward from center
void pattern33_fourGroupsOutwardCenter(uint8_t repeats) {
  uint8_t quarter = NUM_LEDS / 4;
  for (uint8_t r = 0; r < repeats; r++) {
    for (int i = quarter; i >= 0; i--) {
      allOff();
      ledOn(i);
      ledOn(quarter * 2 - i);
      ledOn(quarter * 2 + i);
      ledOn(NUM_LEDS - 1 - i);
      delay(120);
    }
  }
}

// 34. Chase with mirror (left→right, right→left)
void pattern34_chaseWithMirror(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t i = 0; i < NUM_LEDS / 2; i++) {
      allOff();
      ledOn(i);
      ledOn(NUM_LEDS - 1 - i);
      delay(100);
    }
  }
}

// 35. Dual parallel chases (even vs odd)
void pattern35_dualParallelChases(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      allOff();
      ledOn(i % 2 == 0 ? i : (i + 1) % NUM_LEDS);
      ledOn(i % 2 == 1 ? i : (i + 1) % NUM_LEDS);
      delay(100);
    }
  }
}

// 36. Spiral (simulated: left→center→right)
void pattern36_spiralSimulated(uint8_t repeats) {
  uint8_t center = NUM_LEDS / 2;
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t i = 0; i <= center; i++) {
      allOff();
      ledOn(i);
      ledOn(center);
      ledOn(NUM_LEDS - 1 - i);
      delay(120);
    }
  }
}

// 37. Step wave (1-3-5-7… then 2-4-6…)
void pattern37_stepWave(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t step = 1; step <= 7; step += 2) {
      allOff();
      for (uint8_t i = 0; i < NUM_LEDS; i += step) {
        ledOn(i);
      }
      delay(200);
    }
    for (uint8_t step = 2; step <= 6; step += 2) {
      allOff();
      for (uint8_t i = 0; i < NUM_LEDS; i += step) {
        ledOn(i);
      }
      delay(200);
    }
  }
}

// 38. Ladder fill (stacking from one side)
void pattern38_ladderFill(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    allOff();
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      ledOn(i);
      delay(100);
    }
    allOff();
  }
}

// 39. Staircase rise (1 stays on, add 2, add 3, etc.)
void pattern39_staircaseRise(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    allOff();
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      for (uint8_t j = 0; j <= i; j++) {
        ledOn(j);
      }
      delay(150);
    }
    allOff();
  }
}

// 40. Staircase fall (all on, one by one off)
void pattern40_staircaseFall(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    allOn();
    for (int i = NUM_LEDS - 1; i >= 0; i--) {
      ledOff(i);
      delay(150);
    }
    allOff();
  }
}

// 41. Ripple outward single LED
void pattern41_rippleOutwardSingle(uint8_t repeats) {
  uint8_t center1 = NUM_LEDS / 2 - 1;
  uint8_t center2 = NUM_LEDS / 2;
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t offset = 0; offset <= center1; offset++) {
      allOff();
      ledOn(center1 - offset);
      ledOn(center2 + offset);
      delay(100);
    }
  }
}

// 42. Ripple inward single LED
void pattern42_rippleInwardSingle(uint8_t repeats) {
  uint8_t center1 = NUM_LEDS / 2 - 1;
  uint8_t center2 = NUM_LEDS / 2;
  for (uint8_t r = 0; r < repeats; r++) {
    for (int offset = center1; offset >= 0; offset--) {
      allOff();
      ledOn(center1 - offset);
      ledOn(center2 + offset);
      delay(100);
    }
  }
}

// 43. Knight Rider (1 tail)
void pattern43_knightRider1Tail(uint8_t repeats) {
  const uint8_t tailLength = 1;
  for (uint8_t r = 0; r < repeats; r++) {
    for (int i = 0; i < NUM_LEDS * 2; i++) {
      allOff();
      int pos = i % NUM_LEDS;
      ledOn(pos);
      if (pos > 0) ledOn(pos - 1);
      delay(80);
    }
  }
}

// 44. Knight Rider (2 tail fade)
void pattern44_knightRider2TailFade(uint8_t repeats) {
  const uint8_t tailLength = 2;
  for (uint8_t r = 0; r < repeats; r++) {
    for (int i = 0; i < NUM_LEDS * 2; i++) {
      allOff();
      for (uint8_t t = 0; t <= tailLength; t++) {
        int pos = i - t;
        if (pos < 0) pos += NUM_LEDS;
        ledOn(pos);
      }
      delay(80);
    }
  }
}

// 45. Knight Rider (3 tail fade)
void pattern45_knightRider3TailFade(uint8_t repeats) {
  const uint8_t tailLength = 3;
  for (uint8_t r = 0; r < repeats; r++) {
    for (int i = 0; i < NUM_LEDS * 2; i++) {
      allOff();
      for (uint8_t t = 0; t <= tailLength; t++) {
        int pos = i - t;
        if (pos < 0) pos += NUM_LEDS;
        ledOn(pos);
      }
      delay(80);
    }
  }
}

// 46. Comet with fading trail (left→right)
void pattern46_cometFadingTrailLeftToRight(uint8_t repeats) {
  const uint8_t tailLength = 4;
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t i = 0; i < NUM_LEDS * 2; i++) {
      allOff();
      for (uint8_t t = 0; t < tailLength; t++) {
        int pos = i - t;
        if (pos < 0) pos += NUM_LEDS;
        ledOn(pos);
      }
      delay(80);
    }
  }
}

// 47. Comet with fading trail (right→left)
void pattern47_cometFadingTrailRightToLeft(uint8_t repeats) {
  const uint8_t tailLength = 4;
  for (uint8_t r = 0; r < repeats; r++) {
    for (int i = NUM_LEDS * 2; i >= 0; i--) {
      allOff();
      for (uint8_t t = 0; t < tailLength; t++) {
        int pos = i + t;
        if (pos >= NUM_LEDS) pos -= NUM_LEDS;
        ledOn(pos);
      }
      delay(80);
    }
  }
}

// 48. Blink border LEDs only
void pattern48_blinkBorderLEDs(uint8_t repeats) {
  for (uint8_t r = 0; r < repeats * 4; r++) {
    allOff();
    if (r % 2 == 0) {
      ledOn(0);
      ledOn(NUM_LEDS - 1);
    }
    delay(300);
  }
}

// 49. Blink center LEDs only
void pattern49_blinkCenterLEDs(uint8_t repeats) {
  uint8_t center1 = NUM_LEDS / 2 - 1;
  uint8_t center2 = NUM_LEDS / 2;
  for (uint8_t r = 0; r < repeats * 4; r++) {
    allOff();
    if (r % 2 == 0) {
      ledOn(center1);
      ledOn(center2);
    }
    delay(300);
  }
}

// 50. Checkerboard flicker
void pattern50_checkerboardFlicker(uint8_t repeats) {
  for (uint16_t r = 0; r < repeats * 40; r++) {
    allOff();
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if ((i + r) % 2 == 0) ledOn(i);
    }
    delay(100);
  }
}
