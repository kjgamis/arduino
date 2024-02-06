/*
 * 30 Days - Lost in Space
 * Day 10 - Creative Dat
 *
 * Learn more at https://inventr.io/adventure
 *
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Our photoresistor will give us a reading of the current light level on this analog pin
const byte PHOTORESISTOR_PIN = A0;  // Photoresistor analog pin

// RGB LED pins
const byte RED_PIN = 11;    // pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // pin ccontrolling the blue leg of our RGB LED

const byte LIGHT_SWITCH_PIN = 2;

/*
 * Display a color on our RGB LED by providing an intensity for
 * our red, green and blue LEDs.
 */
void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity
) {
  analogWrite(RED_PIN, red_intensity);      // write red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // write green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // write blue LED intensity using PWM
}

void setup() {
  // Declare the RGB LED pins as outputs:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Start serial monitor
  Serial.begin(9600);
}

void loop() {
  // multiple loop() runs.
  unsigned int light_value = analogRead(PHOTORESISTOR_PIN); 
  Serial.print("Light value: ");
  Serial.println(light_value);

  delay(750);  // Delay 1/10 of a second so displayed values don't scroll too fast

  if (digitalRead(LIGHT_SWITCH_PIN) == HIGH && light_value <= 75) {
    if (light_value > 0 && light_value < 50) {
      displayColor(20, 0, 0);  // red
    } else if (light_value > 50 && light_value <= 75) {
      displayColor(0, 20, 0); // green
    }
  } else {
    displayColor(0, 0, 0);     // off
  }
}
