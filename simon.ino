#include "simon.h"

void setup() {

  Serial.begin(9600);
  pinMode(SPEAKER,OUTPUT); 
  digitalWrite(SPEAKER,LOW);

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT); 
  pinMode(led_3, OUTPUT); 
  pinMode(led_4, OUTPUT);

  pinMode(btn_1, INPUT_PULLUP);
  pinMode(btn_2, INPUT_PULLUP);
  pinMode(btn_3, INPUT_PULLUP);
  pinMode(btn_4, INPUT_PULLUP);

  srand(time(NULL));
}

void loop() {
  
  game();
}
