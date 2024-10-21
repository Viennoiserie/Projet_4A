#include "fonctions_tantrix.h"

void setup() {

  setPins();
  setupServos();
  setupTantrix();
  setupScreen();
  //scan();
}

void loop() {


  if(millis() >= next_scan)
  {
    next_scan = millis()+1;
    scan();
  }

  backgroundColor(255, 255, 255);

  find_button_press();
  
  /**
  // Set a font color (r, g, b)
  

  //Servomotor part
  delay(200);
  writeToScreen("Servomotor0");
  positionMoteur0(45);
  delay(1000);
  writeToScreen("Servomotor1");
  positionMoteur1(90);
  delay(1000);
  writeToScreen("Servomotor2");
  positionMoteur2(180);
  delay(1000);
  writeToScreen("Servomotor3");
  positionMoteur3(270);
  delay(5000);

  //Positionnement à 0
  writeToScreen("Reset position");
  resetPositionMoteur(0);
  delay(500);
  resetPositionMoteur(1);
  delay(500);
  resetPositionMoteur(2);
  delay(500);
  resetPositionMoteur(3);
  */
}

