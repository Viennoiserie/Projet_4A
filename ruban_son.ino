#include "fcts_son.h"

void setup() {

  Serial.begin(9600);
  pinMode(SPEAKER,OUTPUT); 
  digitalWrite(SPEAKER,LOW);

  stripMirror.begin();
  stripMirror.clear();
  stripMirror.show();

  pinMode(btn_1, INPUT_PULLUP);
  pinMode(btn_2, INPUT_PULLUP); 
  pinMode(btn_3, INPUT_PULLUP); 
  pinMode(btn_4, INPUT_PULLUP);
  pinMode(btn_5, INPUT_PULLUP); 
  pinMode(btn_6, INPUT_PULLUP); 
  pinMode(btn_7, INPUT_PULLUP); 
  pinMode(btn_8, INPUT_PULLUP); 
}

void loop() {
  
  listenButton();
}
