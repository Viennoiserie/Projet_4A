#include "Codes_Matrice.h"

void setup() {

  Serial.begin(9600);
  pinMode(BUTTON_NORTH, INPUT);
  pinMode(BUTTON_SOUTH, INPUT);
  pinMode(BUTTON_EAST, INPUT);
  pinMode(BUTTON_WEST, INPUT);

  strip.begin();
  strip.clear();           
  strip.show(); 

  strip.setBrightness(BRIGHTNESS);
}

void loop() {

  parcours();
}
