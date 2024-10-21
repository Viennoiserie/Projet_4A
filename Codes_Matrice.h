#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN     6
#define LED_COUNT  64
#define BRIGHTNESS 10 

#define BUTTON_NORTH A0
#define BUTTON_WEST A1
#define BUTTON_EAST A2
#define BUTTON_SOUTH A3

/*

Dans les tableaux de chemin, ces boutons correspondront respectivement à : 

           (Nord)
             1
             |
 (Ouest) 2---|---3 (Est)
             |
             4
           (Sud)

*/

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint16_t rightPath[65] = {3,3,3,3,4,4,4,2,2,1,2,4,4,4,4,3,3,3,3,3,3,0};

uint16_t currentPos[2] = {0,0};

uint16_t index = 0; 

void clear() {

  strip.clear();
}

/**
*
* @return Joue une petite annimation pour indiquer la réussite
*
*/

void goodJob() {

  clear();
  uint16_t j = 0;

  for(uint16_t i = 0; i < 64; i++) {

    switch(j) {

      case 0:
        strip.setPixelColor(i, 255, 0, 0);
        break;

      case 1: 
        strip.setPixelColor(i, 0, 255, 0);
        break;

      case 2:
        strip.setPixelColor(i, 0, 0, 255);
        break;

      default:
        break;
    } 

    j++;

    if(i%3 == 0) {

      j = 0;
    }   

    strip.show()
  }
}

/**
*
* @return renvoie un int correspondant aux leds de la matrice à allumer (de 0 à 63)
*
* Nous aimerions nous déplacer sur ses leds de la même manière que nous le ferions avec une matrice (lignes puis colonnes) donc :
*
* @param l: correspond à la ligne que nous aimerions allumer
* @param c: correspond à la colonne que nous aimerions allumer
*
*/

uint16_t matrix_to_matrix(uint16_t l, uint16_t c) {

  // Si on veut, par exemple, ligne 1 - colonne 2 : allume la leds numéro 10 ( = 1*8+2 )
  uint16_t res = l * 8 + c; 

  return(res);
}


/**
*
* @return remet à zero notre avancement (sert à recommencer le jeux en cas d'erreur)
*
*/

void resetAll() {

  clear();
  currentPos[0] = 0;
  currentPos[1] = 0;

  index = 0;

  for(uint16_t i = 0; i < 64; i++) {

    strip.setPixelColor(i, 255, 0 , 0);
  }

  strip.show();
  delay(50);
  clear();
  strip.show();
  delay(50);

  for(uint16_t i = 0; i < 64; i++) {

    strip.setPixelColor(i, 255, 0 , 0);
  }

  strip.show();
  delay(50);
  clear();
  strip.show();
  delay(50);

  for(uint16_t i = 0; i < 64; i++) {

    strip.setPixelColor(i, 255, 0 , 0);
  }

  strip.show();
  delay(50);
  clear();

  uint16_t pos = matrix_to_matrix(currentPos[0], currentPos[1]);
  strip.setPixelColor(pos, 255, 0, 0);
  strip.show();
}

/**
*
* @return allume la led au-dessus de notre position actuelle
*
*/

void goingNorth(uint16_t tab[2], uint16_t state) {

  // Si le bouton est appuyé
  if(state == LOW) {

    if(tab[0] > 0) { // On vérifie qu'il soit bien possible de "monter"

      if(rightPath[index] == 1){ // 1 correspond au nord, donc on vérifie si le nord est bien la direction attendue à ce moment la dans le jeux

        index++; // On avance
        tab[0]--; // On change notre position actuelle

        uint16_t pos = matrix_to_matrix(tab[0], tab[1]); // On calcule notre position en terme de nombre (0 à 63 toujours)

        strip.setPixelColor(pos, 255, 0, 0); // On allume là où nous nous trouvons
        strip.show();
      }
      else{

        resetAll();
      }
    }
    else{

      resetAll();
    }

    Serial.println("NorthDown");
    delay(100);
  }
  else {

    Serial.println("NorthUp");
  }
}

/**
*
* @return allume la led en-dessous de notre position actuelle (même fonctionnement que le nord)
*
*/

void goingSouth(uint16_t tab[2], uint16_t state) {

  if(state == LOW) {

    if(tab[0] < 8) {

      if(rightPath[index] == 4){

        index++;
        tab[0]++;

        uint16_t pos = matrix_to_matrix(tab[0], tab[1]);

        strip.setPixelColor(pos, 255, 0, 0);
        strip.show();
      }
      else{

        resetAll();
      }
    }
    else{

      resetAll();
    }

    Serial.println("SouthDown");
    delay(100);
  }
  else {

    Serial.println("SouthUp");
  }
}

/**
*
* @return allume la led à gauche de notre position actuelle (même fonctionnement que le nord)
*
*/

void goingWest(uint16_t tab[2], uint16_t state) {

  if(state == LOW) {

    if(tab[1] > 0) {

      if(rightPath[index] == 2) {

        index++;
        tab[1]--;

        uint16_t pos = matrix_to_matrix(tab[0], tab[1]);

        strip.setPixelColor(pos, 255, 0, 0);
        strip.show();
      }  
      else {

        resetAll();
      }
    }
    else{

      resetAll();
    }   

    Serial.println("WestDown");
    delay(100);
  }
  else {

    Serial.println("WestUp");
  }
}

/**
*
* @return allume la led à droite de notre position actuelle (même fonctionnement que le nord)
*
*/

void goingEast(uint16_t tab[2], uint16_t state) {

  if(state == LOW) {

    if(tab[1] < 8) {

      if(rightPath[index] == 3) {

        index++;
        tab[1]++;

         uint16_t pos = matrix_to_matrix(tab[0], tab[1]);

        strip.setPixelColor(pos, 255, 0, 0);
        strip.show();
      }
      else{

        resetAll();
      }
    }
    else{

      resetAll();
    }

    Serial.println("EastDown");
    delay(100);
  }
  else {

    Serial.println("EastUp");
  }
}

/**
*
* @return gère le chemin parcouru et donc le jeux
*
*/

void parcours() {

  bool gameOn = true;
  
  // On lit une première fois les boutons
  uint16_t lastNorthState = digitalRead(BUTTON_NORTH);
  uint16_t lastSouthState = digitalRead(BUTTON_SOUTH);
  uint16_t lastEastState = digitalRead(BUTTON_EAST);
  uint16_t lastWestState = digitalRead(BUTTON_WEST);

  // On instancie notre position initiale
  uint16_t matrixPos = matrix_to_matrix(currentPos[0], currentPos[1]);

  // On l'affiche
  strip.setPixelColor(matrixPos, 255, 0, 0);
  strip.show();

  while(gameOn) { // Une fois en jeux :

    // Lecture des 4 boutons pour voir si un changement survient
    uint16_t northState = digitalRead(BUTTON_NORTH);
    uint16_t southState = digitalRead(BUTTON_SOUTH);
    uint16_t eastState = digitalRead(BUTTON_EAST);
    uint16_t westState = digitalRead(BUTTON_WEST);

    if(rightPath[index] == 0) { // Le chiffre 0 indique la fin du parcours

      goodJob();
      gameOn = false;
    }

    if(northState != lastNorthState) { // En cas de changement dans l'état du bouton

      goingNorth(currentPos, northState); // On update notre position
      lastNorthState = northState;        // Le nouvel état devient alors l'ancien état
    }   

    if(southState != lastSouthState) { // idem

      goingSouth(currentPos, southState);
      lastSouthState = southState;
    } 

    if(eastState != lastEastState) { // idem 

      goingEast(currentPos, eastState);
      lastEastState = eastState;
    } 

    if(westState != lastWestState) { // idem

      goingWest(currentPos, westState);
      lastWestState = westState;
    }  

    Serial.println(index);
    Serial.println(rightPath[index+1]);
  }
}

