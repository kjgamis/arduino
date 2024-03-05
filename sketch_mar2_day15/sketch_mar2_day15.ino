/*
 * 30 Days - Lost in Space
 * Day 16 - A Fancy New Display
 *
 * Learn more at https://learn.inventr.io/adventure
 *
 * Sound and light gives us some good feedback from our HERO, but what about
 * when we need numbers and the Serial Console isn't available?  Today we
 * introduce a 4-digit 7-segment display (TM1637).  This is mostly for numbers,
 * like a counter or perhaps a clock display, but with some imagination we can
 * also show some characters.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - Binary notation (0b00000001)
 * - logical OR
 * - 
 *
 * Parts and electronics concepts introduced in this lesson.
 * - TM1637 4-digit 7-segment display
 */

// Explicitly include Arduino.h
#include "Arduino.h"

/*
 * Please refer to the lesson and lesson videos for instructions on how to
 * load the TM1637 library into your Arduino IDE before you use it for the
 * first time.
 *
 * In order to use the TM1637 library we include the file "TM1637Display.h".
 */
#include <TM1637Display.h>

// all_on pins connected to the TM1637 display
const byte CLK_PIN = 6;
const byte DIO_PIN = 5;

// Create display object of type TM1637Display:
TM1637Display lander_display = TM1637Display(CLK_PIN, DIO_PIN);

/*
 * The TM1637 library takes an array of 4 bytes to represent each of the 4 display
 * digits.  Within each byte, bit 0 is segment A, bit 1 is segment B etc.  A zero
 * indicates the segment is off, a 1 bit indicates the segment is on.
 *
 * NOTE: To show the individual bits in each byte we will use BINARY number notation
 *       consisting of a "0b" followed by eight bits that can be either 0 or 1 (ex.
 *       0b01010101).
 */

// Create array that turns all segments on:
const byte all_on[] = { 0b11111111,
                        0b11111111,
                        0b11111111,
                        0b11111111 };

/*
 * A 7-segment display is shaped like an "8" and has 7 segments (A through G) that can be
 * lit up. The diagram below shows the placement of each of the segments.
 *
 *   A
 * F   B
 *   G
 * E   C
 *   D
 *
 * You can set the individual segments per digit to spell words or create other symbols.
 * The TM1637 library provides constants for each segment on the display.  If you hover
 * your mouse over each of these constants you can see that each defines a byte with only
 * one bit set to 1.  SEG_A = 0b00000001, SEG_B = 0b00000010, etc.
 *
 * The Arduino C++ language uses the '|' operator to do a "bitwise or" between values.  It
 * takes each corresponding bits in two values and the output is 1 if *either* or both of the
 * corresponding bits is 1.  If both corresponding bits are 0 then the corresponding bit is
 * set to 0.
 *
 * In other words:
 * 0  0  1  1    operand1
 * 0  1  0  1    operand2
 * ----------
 * 0  1  1  1    (operand1 | operand2) - returned result
 */

 // By turning on selected segments we can display *some* alphabetic characters.
 // Here we spell out the word "dOnE".
const byte done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           // E
};

const byte fred[] = { // FrEd
  SEG_A | SEG_E | SEG_F | SEG_G | SEG_E,
  SEG_E | SEG_G,
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,
};
const byte love[] = { // KAGE
  SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
};
const byte kage[] = { LOVE
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
};

void setup() {
  lander_display.setBrightness(1);  // Configure the display brightness (0-7):
}

void loop() {
  // Clear the display (all segments off)
  lander_display.clear();
  delay(1000);


  // Clear the display (all segments off)
  lander_display.clear();
  // delay(1000);

  lander_display.setSegments(fred);
  delay(1500);
  lander_display.setSegments(love);
  delay(1500);
  lander_display.setSegments(kage);
  delay(1500);
}
