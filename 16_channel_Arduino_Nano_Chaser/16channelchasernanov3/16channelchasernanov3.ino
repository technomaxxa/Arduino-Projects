/*****************************************************************************************
*   Project Name : 16 Channel Chaser with Nano (v3.0)
*   Filename     : 16channelchasernanov3.ino
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
*   - Includes 100 unique chasing effects
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
// Forward declarations for new patterns
void pattern51_alternateEnds(uint8_t repeats);
void pattern52_rippleDoubleOut(uint8_t repeats);
void pattern53_rollingPairs(uint8_t repeats);
void pattern54_snakeSkip(uint8_t repeats);
void pattern55_snakeDoubleSkip(uint8_t repeats);
void pattern56_sparkleMirror(uint8_t repeats);
void pattern57_trioGap(uint8_t repeats);
void pattern58_insideOutWipe(uint8_t repeats);
void pattern59_outsideInWipe(uint8_t repeats);
void pattern60_randomCluster(uint8_t repeats);
void pattern61_strobeAll(uint8_t repeats);
void pattern62_quarterSweep(uint8_t repeats);
void pattern63_quarterSweepBack(uint8_t repeats);
void pattern64_fillEmpty(uint8_t repeats);
void pattern65_bounceEndsIn(uint8_t repeats);
void pattern66_bounceCenterOut(uint8_t repeats);
void pattern67_rollingWindow4(uint8_t repeats);
void pattern68_rollingWindow5(uint8_t repeats);
void pattern69_sparkleHalf(uint8_t repeats);
void pattern70_alternateHalves(uint8_t repeats);
void pattern71_dualOpposite(uint8_t repeats);
void pattern72_dualSame(uint8_t repeats);
void pattern73_tripleSpread(uint8_t repeats);
void pattern74_centerBarGrow(uint8_t repeats);
void pattern75_centerBarShrink(uint8_t repeats);
void pattern76_alternateThirds(uint8_t repeats);
void pattern77_sparkleCascade(uint8_t repeats);
void pattern78_dualBars(uint8_t repeats);
void pattern79_evenOdd(uint8_t repeats);
void pattern80_randomGroups(uint8_t repeats);
void pattern81_diagonalRippleLR(uint8_t repeats);
void pattern82_diagonalRippleRL(uint8_t repeats);
void pattern83_twoStepWalker(uint8_t repeats);
void pattern84_threeStepWalker(uint8_t repeats);
void pattern85_fillCenterClearEnds(uint8_t repeats);
void pattern86_quarterBlink(uint8_t repeats);
void pattern87_flashingEdges(uint8_t repeats);
void pattern88_chasingGaps(uint8_t repeats);
void pattern89_symmetricPairs(uint8_t repeats);
void pattern90_fullBlinkFade(uint8_t repeats);
void pattern91_splitWipeIn(uint8_t repeats);
void pattern92_splitWipeOut(uint8_t repeats);
void pattern93_snakeWrap(uint8_t repeats);
void pattern94_dualSnakeWrap(uint8_t repeats);
void pattern95_zigzagFill(uint8_t repeats);
void pattern96_blinkQuarters(uint8_t repeats);
void pattern97_sparkleRain(uint8_t repeats);
void pattern98_tripletSeq(uint8_t repeats);
void pattern99_expandingFlash(uint8_t repeats);
void pattern100_contractFlash(uint8_t repeats);


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
  pattern50_checkerboardFlicker,
  // === New patterns 51–100 ===
pattern51_alternateEnds,
pattern52_rippleDoubleOut,
pattern53_rollingPairs,
pattern54_snakeSkip,
pattern55_snakeDoubleSkip,
pattern56_sparkleMirror,
pattern57_trioGap,
pattern58_insideOutWipe,
pattern59_outsideInWipe,
pattern60_randomCluster,
pattern61_strobeAll,
pattern62_quarterSweep,
pattern63_quarterSweepBack,
pattern64_fillEmpty,
pattern65_bounceEndsIn,
pattern66_bounceCenterOut,
pattern67_rollingWindow4,
pattern68_rollingWindow5,
pattern69_sparkleHalf,
pattern70_alternateHalves,
pattern71_dualOpposite,
pattern72_dualSame,
pattern73_tripleSpread,
pattern74_centerBarGrow,
pattern75_centerBarShrink,
pattern76_alternateThirds,
pattern77_sparkleCascade,
pattern78_dualBars,
pattern79_evenOdd,
pattern80_randomGroups,
pattern81_diagonalRippleLR,
pattern82_diagonalRippleRL,
pattern83_twoStepWalker,
pattern84_threeStepWalker,
pattern85_fillCenterClearEnds,
pattern86_quarterBlink,
pattern87_flashingEdges,
pattern88_chasingGaps,
pattern89_symmetricPairs,
pattern90_fullBlinkFade,
pattern91_splitWipeIn,
pattern92_splitWipeOut,
pattern93_snakeWrap,
pattern94_dualSnakeWrap,
pattern95_zigzagFill,
pattern96_blinkQuarters,
pattern97_sparkleRain,
pattern98_tripletSeq,
pattern99_expandingFlash,
pattern100_contractFlash
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
// 51. Alternate flashing ends
void pattern51_alternateEnds(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*6; r++) {
    allOff();
    if (r % 2 == 0) {
      ledOn(0);
      ledOn(NUM_LEDS-1);
    } else {
      ledOn(1);
      ledOn(NUM_LEDS-2);
    }
    delay(250);
  }
}

// 52. Ripple double outward
void pattern52_rippleDoubleOut(uint8_t repeats) {
  uint8_t center1 = NUM_LEDS/2 - 1;
  uint8_t center2 = NUM_LEDS/2;
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t offset=0; offset<=center1; offset++) {
      allOff();
      ledOn(center1-offset);
      ledOn(center2+offset);
      if (offset>0) {
        ledOn(center1-offset+1);
        ledOn(center2+offset-1);
      }
      delay(100);
    }
  }
}

// 53. Rolling blink pairs
void pattern53_rollingPairs(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*2; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i+=2) {
      allOff();
      ledOn(i);
      if (i+1<NUM_LEDS) ledOn(i+1);
      delay(150);
    }
  }
}

// 54. Snake single LED skipping
void pattern54_snakeSkip(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i+=2) {
      allOff();
      ledOn(i);
      delay(120);
    }
  }
}

// 55. Snake double LED skipping
void pattern55_snakeDoubleSkip(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i+=2) {
      allOff();
      ledOn(i);
      if (i+1<NUM_LEDS) ledOn(i+1);
      delay(120);
    }
  }
}

// 56. Sparkle mirrored
void pattern56_sparkleMirror(uint8_t repeats) {
  for (uint16_t r=0; r<repeats*25; r++) {
    allOff();
    uint8_t idx = random(NUM_LEDS/2);
    ledOn(idx);
    ledOn(NUM_LEDS-1-idx);
    delay(120);
  }
}

// 57. Rolling triple with gap
void pattern57_trioGap(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn((i+2)%NUM_LEDS);
      ledOn((i+4)%NUM_LEDS);
      delay(100);
    }
  }
}

// 58. Inside-out wipe
void pattern58_insideOutWipe(uint8_t repeats) {
  uint8_t c1=NUM_LEDS/2-1, c2=NUM_LEDS/2;
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t offset=0; offset<=c1; offset++) {
      allOff();
      for (int j=c1-offset; j<=c2+offset; j++) ledOn(j);
      delay(120);
    }
    allOff();
  }
}

// 59. Outside-in wipe
void pattern59_outsideInWipe(uint8_t repeats) {
  uint8_t c1=NUM_LEDS/2-1, c2=NUM_LEDS/2;
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t offset=0; offset<=c1; offset++) {
      allOff();
      for (int j=0; j<=offset; j++) {
        ledOn(j);
        ledOn(NUM_LEDS-1-j);
      }
      delay(120);
    }
    allOff();
  }
}

// 60. Random sparkle clusters
void pattern60_randomCluster(uint8_t repeats) {
  for (uint16_t r=0; r<repeats*15; r++) {
    allOff();
    uint8_t base=random(NUM_LEDS);
    for (uint8_t j=0; j<3; j++) ledOn((base+j)%NUM_LEDS);
    delay(200);
  }
}
// 61. Strobe all LEDs
void pattern61_strobeAll(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*5; r++) {
    allOff();
    delay(80);
    for (uint8_t i=0; i<NUM_LEDS; i++) ledOn(i);
    delay(80);
  }
}

// 62. Quarter sweep forward
void pattern62_quarterSweep(uint8_t repeats) {
  uint8_t quarter = NUM_LEDS/4;
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t q=0; q<4; q++) {
      allOff();
      for (uint8_t i=0; i<quarter; i++) ledOn(q*quarter+i);
      delay(200);
    }
  }
}

// 63. Quarter sweep backward
void pattern63_quarterSweepBack(uint8_t repeats) {
  uint8_t quarter = NUM_LEDS/4;
  for (uint8_t r=0; r<repeats; r++) {
    for (int q=3; q>=0; q--) {
      allOff();
      for (uint8_t i=0; i<quarter; i++) ledOn(q*quarter+i);
      delay(200);
    }
  }
}

// 64. Fill then empty
void pattern64_fillEmpty(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      ledOn(i);
      delay(80);
    }
    delay(200);
    for (int i=NUM_LEDS-1; i>=0; i--) {
      ledOff(i);
      delay(80);
    }
  }
}

// 65. Bounce ends inward
void pattern65_bounceEndsIn(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<=NUM_LEDS/2; i++) {
      allOff();
      ledOn(i);
      ledOn(NUM_LEDS-1-i);
      delay(120);
    }
  }
}

// 66. Bounce center outward
void pattern66_bounceCenterOut(uint8_t repeats) {
  uint8_t c1 = NUM_LEDS/2-1, c2 = NUM_LEDS/2;
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t offset=0; offset<=c1; offset++) {
      allOff();
      ledOn(c1-offset);
      ledOn(c2+offset);
      delay(120);
    }
    for (int offset=c1; offset>=0; offset--) {
      allOff();
      ledOn(c1-offset);
      ledOn(c2+offset);
      delay(120);
    }
  }
}

// 67. Rolling window of 4
void pattern67_rollingWindow4(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      for (uint8_t j=0; j<4; j++) ledOn((i+j)%NUM_LEDS);
      delay(100);
    }
  }
}

// 68. Rolling window of 5
void pattern68_rollingWindow5(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      for (uint8_t j=0; j<5; j++) ledOn((i+j)%NUM_LEDS);
      delay(100);
    }
  }
}

// 69. Sparkle random half
void pattern69_sparkleHalf(uint8_t repeats) {
  for (uint16_t r=0; r<repeats*20; r++) {
    allOff();
    uint8_t half = (random(2)==0)?0:NUM_LEDS/2;
    uint8_t idx = half+random(NUM_LEDS/2);
    ledOn(idx);
    delay(120);
  }
}

// 70. Alternate halves blink
void pattern70_alternateHalves(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*6; r++) {
    allOff();
    if (r%2==0) {
      for (uint8_t i=0; i<NUM_LEDS/2; i++) ledOn(i);
    } else {
      for (uint8_t i=NUM_LEDS/2; i<NUM_LEDS; i++) ledOn(i);
    }
    delay(300);
  }
}
// 71. Two chasing points opposite
void pattern71_dualOpposite(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn(NUM_LEDS-1-i);
      delay(120);
    }
  }
}

// 72. Two chasing points same direction
void pattern72_dualSame(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i+=2) {
      allOff();
      ledOn(i);
      if (i+1<NUM_LEDS) ledOn(i+1);
      delay(120);
    }
  }
}

// 73. Three chasing points spread
void pattern73_tripleSpread(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn((i+NUM_LEDS/3)%NUM_LEDS);
      ledOn((i+2*NUM_LEDS/3)%NUM_LEDS);
      delay(120);
    }
  }
}

// 74. Center bar growing
void pattern74_centerBarGrow(uint8_t repeats) {
  uint8_t c1=NUM_LEDS/2-1, c2=NUM_LEDS/2;
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t offset=0; offset<=c1; offset++) {
      allOff();
      for (int j=c1-offset; j<=c2+offset; j++) ledOn(j);
      delay(100);
    }
  }
}

// 75. Center bar shrinking
void pattern75_centerBarShrink(uint8_t repeats) {
  uint8_t c1=NUM_LEDS/2-1, c2=NUM_LEDS/2;
  for (uint8_t r=0; r<repeats; r++) {
    for (int offset=c1; offset>=0; offset--) {
      allOff();
      for (int j=c1-offset; j<=c2+offset; j++) ledOn(j);
      delay(100);
    }
  }
}

// 76. Alternating thirds
void pattern76_alternateThirds(uint8_t repeats) {
  uint8_t third=NUM_LEDS/3;
  for (uint8_t r=0; r<repeats*6; r++) {
    allOff();
    uint8_t sel=r%3;
    for (uint8_t i=sel*third; i<(sel+1)*third; i++) ledOn(i);
    delay(200);
  }
}

// 77. Sparkle cascade
void pattern77_sparkleCascade(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      delay(60);
    }
    for (int i=NUM_LEDS-1; i>=0; i--) {
      allOff();
      ledOn(i);
      delay(60);
    }
  }
}

// 78. Dual moving bars
void pattern78_dualBars(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS/2; i++) {
      allOff();
      ledOn(i);
      ledOn(NUM_LEDS/2+i);
      delay(100);
    }
  }
}

// 79. Even odd blink
void pattern79_evenOdd(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*6; r++) {
    allOff();
    if (r%2==0) {
      for (uint8_t i=0; i<NUM_LEDS; i+=2) ledOn(i);
    } else {
      for (uint8_t i=1; i<NUM_LEDS; i+=2) ledOn(i);
    }
    delay(250);
  }
}

// 80. Random flash groups
void pattern80_randomGroups(uint8_t repeats) {
  for (uint16_t r=0; r<repeats*10; r++) {
    allOff();
    uint8_t count=random(3,6);
    for (uint8_t j=0; j<count; j++) ledOn(random(NUM_LEDS));
    delay(200);
  }
}
// 81. Diagonal ripple left-to-right
void pattern81_diagonalRippleLR(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t shift=0; shift<NUM_LEDS; shift++) {
      allOff();
      for (uint8_t i=0; i<NUM_LEDS; i+=3) {
        ledOn((i+shift)%NUM_LEDS);
      }
      delay(100);
    }
  }
}

// 82. Diagonal ripple right-to-left
void pattern82_diagonalRippleRL(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (int shift=NUM_LEDS-1; shift>=0; shift--) {
      allOff();
      for (uint8_t i=0; i<NUM_LEDS; i+=3) {
        ledOn((i+shift)%NUM_LEDS);
      }
      delay(100);
    }
  }
}

// 83. Two-step walker
void pattern83_twoStepWalker(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i+=2) {
      allOff();
      ledOn(i);
      if (i+1<NUM_LEDS) ledOn(i+1);
      delay(120);
    }
  }
}

// 84. Three-step walker
void pattern84_threeStepWalker(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i+=3) {
      allOff();
      ledOn(i);
      if (i+1<NUM_LEDS) ledOn(i+1);
      if (i+2<NUM_LEDS) ledOn(i+2);
      delay(120);
    }
  }
}

// 85. Fill center out, clear outside in
void pattern85_fillCenterClearEnds(uint8_t repeats) {
  uint8_t c1=NUM_LEDS/2-1, c2=NUM_LEDS/2;
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t offset=0; offset<=c1; offset++) {
      for (int j=c1-offset; j<=c2+offset; j++) ledOn(j);
      delay(100);
    }
    for (uint8_t offset=0; offset<=c1; offset++) {
      ledOff(offset);
      ledOff(NUM_LEDS-1-offset);
      delay(100);
    }
  }
}

// 86. Alternate quarter blink
void pattern86_quarterBlink(uint8_t repeats) {
  uint8_t q=NUM_LEDS/4;
  for (uint8_t r=0; r<repeats*4; r++) {
    allOff();
    uint8_t sel=r%4;
    for (uint8_t i=sel*q; i<(sel+1)*q; i++) ledOn(i);
    delay(250);
  }
}

// 87. Flashing edges
void pattern87_flashingEdges(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*8; r++) {
    allOff();
    if (r%2==0) {
      ledOn(0);
      ledOn(NUM_LEDS-1);
    } else {
      ledOn(1);
      ledOn(NUM_LEDS-2);
    }
    delay(200);
  }
}

// 88. Chasing gaps
void pattern88_chasingGaps(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn((i+2)%NUM_LEDS);
      delay(120);
    }
  }
}

// 89. Symmetric double pairs
void pattern89_symmetricPairs(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS/2; i++) {
      allOff();
      ledOn(i);
      ledOn(i+1);
      ledOn(NUM_LEDS-1-i);
      ledOn(NUM_LEDS-2-i);
      delay(120);
    }
  }
}

// 90. Full blink with fade effect
void pattern90_fullBlinkFade(uint8_t repeats) {
  for (uint8_t r=0; r<repeats*5; r++) {
    for (uint8_t k=0; k<NUM_LEDS; k++) ledOn(k);
    delay(150);
    for (uint8_t k=0; k<NUM_LEDS; k++) ledOff(k);
    delay(150);
  }
}
// 91. Split wipe inward
void pattern91_splitWipeIn(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS/2; i++) {
      allOff();
      ledOn(i);
      ledOn(NUM_LEDS-1-i);
      delay(100);
    }
  }
}

// 92. Split wipe outward
void pattern92_splitWipeOut(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (int i=NUM_LEDS/2-1; i>=0; i--) {
      allOff();
      ledOn(i);
      ledOn(NUM_LEDS-1-i);
      delay(100);
    }
  }
}

// 93. Snake wraparound
void pattern93_snakeWrap(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS*2; i++) {
      allOff();
      ledOn(i%NUM_LEDS);
      delay(90);
    }
  }
}

// 94. Dual snake wraparound
void pattern94_dualSnakeWrap(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      allOff();
      ledOn(i);
      ledOn((i+NUM_LEDS/2)%NUM_LEDS);
      delay(100);
    }
  }
}

// 95. Zigzag fill
void pattern95_zigzagFill(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      ledOn(i);
      delay(70);
    }
    for (int i=NUM_LEDS-1; i>=0; i--) {
      ledOff(i);
      delay(70);
    }
  }
}

// 96. Blink quarters in sequence
void pattern96_blinkQuarters(uint8_t repeats) {
  uint8_t q=NUM_LEDS/4;
  for (uint8_t r=0; r<repeats*4; r++) {
    allOff();
    uint8_t sel=r%4;
    for (uint8_t i=sel*q; i<(sel+1)*q; i++) ledOn(i);
    delay(200);
  }
}

// 97. Sparkle rain
void pattern97_sparkleRain(uint8_t repeats) {
  for (uint16_t r=0; r<repeats*25; r++) {
    allOff();
    for (uint8_t j=0; j<5; j++) ledOn(random(NUM_LEDS));
    delay(100);
  }
}

// 98. Sequential triplets
void pattern98_tripletSeq(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<NUM_LEDS; i+=3) {
      allOff();
      for (uint8_t j=0; j<3; j++) {
        if (i+j<NUM_LEDS) ledOn(i+j);
      }
      delay(150);
    }
  }
}

// 99. Expanding flashes
void pattern99_expandingFlash(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (uint8_t i=0; i<=NUM_LEDS/2; i++) {
      allOff();
      for (uint8_t j=i; j<NUM_LEDS-i; j++) ledOn(j);
      delay(120);
    }
  }
}

// 100. Contracting flashes
void pattern100_contractFlash(uint8_t repeats) {
  for (uint8_t r=0; r<repeats; r++) {
    for (int i=NUM_LEDS/2; i>=0; i--) {
      allOff();
      for (int j=i; j<NUM_LEDS-i; j++) ledOn(j);
      delay(120);
    }
  }
}
