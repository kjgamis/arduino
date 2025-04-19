/*
 * 30 Days - Lost in Space
 * Day 21 - Hello New World!
 *
 * For safe liftoff we're going to need to see and react to more information than
 * can be displayed on our 4 digit display or with LEDs.  Luckily our repair kit
 * contains just the thing, a small monochrome Organic LED display.
 *
 * This display has 8,128 tiny LEDs arranged in 64 rows of 128 pixels each.  Now, as
 * I'm sure you've noticed, we do NOT have 8,128 pins on our HERO board, but never
 * fear Explorer, people back in the 2020's were pretty clever and came up with a
 * solution.
 *
 * Instead of having one pin for every LED, The HERO will use two pins to send and
 * receive messages with our OLED display and will instruct the display which pixels
 * to light up using a special "language" (or "protocol") named I2C ("eye-squared-see").
 *
 * The HERO board uses pins A5 and A4 for I2C communications so we will wire those two
 * pins to our display along with power and ground, giving us a four wire connection
 * for displaying messages or pictures on our new display.
 *
 * Learn more at https://learn.inventr.io/adventure
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - I2C communications.
 * - Computer character fonts
 * - U8g2 graphics library for monochrome displays
 * - Logical Not operator ('!')
 * - clearBuffer()/sendBuffer() method for OLED display updates
 *
 * Parts and electronics concepts introduced in this lesson.
 * - SH1106 monochrome 128x64 pixel OLED display.
 * - HERO I2C pins (A5 and A4)
 */

// Explicitly include Arduino.h
#include "Arduino.h"

/*
 * Refer to the Day 21 lesson for instructions on how to install the U8g2
 * library into the Arduino IDE.  We will use this library to display messages
 * on our OLED display.
 *
 * Extensive documentation for this library can be found at https://github.com/olikraus/u8g2
 * for those wanting to dive deeper, but we will explain all of the functions
 * used in these lessons.
 */
#include <U8g2lib.h>  // Include file for the U8g2 library.

/*
 * The U8g2 library supports many different types of display.  It does this by
 * having a different "constructor" for each.  A constructor is used to create
 * the "handle" that we use to access the library code.  In this case, our handle
 * will be named "lander_display".
 *
 * The documentation for this library lists all of the displays supported along
 * with the corresponding constructors and options.  This constructor is for our
 * SH1106, 128x64 pixel generic display.  The "_F_" indicates that we will use
 * a full-sized graphics buffer and the clearBuffer()/sendBuffer() methods to
 * update the entire display at once. The "HW_I2C" indicates that we will be using
 * I2C communications with this display.
 */
U8G2_SH1106_128X64_NONAME_F_HW_I2C lander_display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void setup(void) {
  Serial.begin(9600);
  delay(1000);
  lander_display.begin();  // Initialize our display

  // Select a font to use for character display
  // The library supports hundreds of different fonts which can be found at
  // https://github.com/olikraus/u8g2/wiki/fntlistall
  // lander_display.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
  lander_display.setFont(u8g2_font_rosencrantz_nbp_tf);  // choose a suitable font

  // Uncomment the next line if your display shows the text upside down.
  // lander_display.setDisplayRotation(U8G2_R2);
}

void loop(void) {
  // Save the number of vertical pixels required for the tallest character
  // in the current font.  This is used later to properly position text on
  // our display.
  byte font_height = lander_display.getMaxCharHeight();

  lander_display.clearBuffer();  // clear the internal memory

  lander_display.setFontPosTop();

  // static bool blink_on = true;
  // if (blink_on) {
    byte centered_y = (lander_display.getDisplayHeight() / 2);

    // This statement instructs the graphics library that the Y coordinate used to position
    // the text will be halfway between the top and bottom of the text.
    lander_display.setFontPosCenter();  // Draw text with centered Y coordinate
    drawCenteredString(centered_y - font_height, "Fred");
    drawCenteredString(centered_y, "<3");
    drawCenteredString(centered_y + font_height, "Kage");
  // }
  // A boolean value can be changed between it's two states by setting it to the opposite
  // state using the "logical not".  Not true = false.  Not false = true.
  // This would be read as "blink on equals not blink on".
  // blink_on = !blink_on;   // toggle value of blink_on between true and false

  // Nothing is displayed on our display until the buffer is sent to the display, below.
  delay(2000);

  // lander_display.clearDisplay();

  // drawCenteredString(centered_y, "no, ur gay");


  // lander_display.clearDisplay();
  delay(2000);

  lander_display.sendBuffer();  // transfer internal memory to the display
  // delay(500);   // Delay for blink effect
}

// Use the .drawStr() method to draw the current string centered in
// the current display.
byte drawCenteredString(byte y, char *string) {
  byte centered_x = (lander_display.getDisplayWidth() - lander_display.getStrWidth(string)) / 2;
  lander_display.drawStr(centered_x, y, string);
}