#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// La taille du strip de led dans le mirroir (j'ai compté à la main 74, on va partir du principe que c'est bien ca XD)

#define STRIPSIZE 74  

#define SPEAKER 12 // Pin du speaker
#define MIRROR A0 //  Pin de contrôle des leds

// Définition des pins boutons

#define btn_1 2
#define btn_2 3
#define btn_3 4
#define btn_4 5
#define btn_5 6
#define btn_6 7
#define btn_7 8
#define btn_8 9

// Cet array d'entiers contient toutes les notes possibles (possible de les modifier !)

int BassTab[] = {2500,2200,2000,1800,1500,1300,1100,900};

// Ces arrays d'entiers correspondent à des zones du bandeaux de leds 

int zone1[] = {0,1,2,3,4,5,6,7,8};
int zone2[] = {9,10,11,12,13,14,15,16,17};
int zone3[] = {18,19,20,21,22,23,24,25,26};
int zone4[] = {27,28,29,30,31,32,33,34,35};
int zone5[] = {36,37,38,39,40,41,42,43,44};
int zone6[] = {45,46,47,48,50,51,52,53,54};
int zone7[] = {55,56,57,58,59,60,61,62,63};
int zone8[] = {64,65,66,67,68,69,70,71,72};

// Définition du bandeau

Adafruit_NeoPixel stripMirror = Adafruit_NeoPixel(STRIPSIZE, MIRROR, NEO_GRB + NEO_KHZ800);

/**
*
* @return joue un son et allume une zone du bandeau 
*
* @param note : correspond à la note que vous souhaitez
* @param bouton : correspond au bouton sur lequel vous appuyez
* @param zone : correspond à la zone du bandeau que vous comptez allumer
*
*/

void play_sound(int note, int bouton, int zone[]) {

  // Allumage des leds en premier

  for(int i = 0; i < 9; i++){

    stripMirror.setPixelColor(zone[i], 255, 255, 255);
    stripMirror.show();
  }

  // Tant que le bouton reste appuye (état logique 1) :

  while(digitalRead(bouton) == 1){

    // On balance la sauce dans les speakers

    digitalWrite(SPEAKER, HIGH);
    delayMicroseconds(note);
    digitalWrite(SPEAKER, LOW);
    delayMicroseconds(note);
  }

  // Dès que le bouton change d'état (on revient donc à 0) on éteint les leds 

  stripMirror.clear();
  stripMirror.show();
}

/**
*
* @return écoute les 8 boutons : Cette fonction doit être utilisée dans le loop() !
*
*/

void listenButton() {

  // Je ne pense pas pouvoir faire de switch case ici alors bah :
  // Plein de if / else pour trouver quel boutons sont appuyés à chaque tick

  // Si j'appuie sur un bouton x, je joue la note[x], je donne x en paramètre ainsi que la zoneX.

  if(digitalRead(btn_1) == 1){play_sound(BassTab[0], btn_1, zone1);}

  else if(digitalRead(btn_2) == 1){play_sound(BassTab[1], btn_2, zone2);}

  else if(digitalRead(btn_3) == 1){play_sound(BassTab[2], btn_3, zone3);}

  else if(digitalRead(btn_4) == 1){play_sound(BassTab[3], btn_4, zone4);}

  else if(digitalRead(btn_5) == 1){play_sound(BassTab[4], btn_5, zone5);}

  else if(digitalRead(btn_6) == 1){play_sound(BassTab[5], btn_6, zone6);}

  else if(digitalRead(btn_7) == 1){play_sound(BassTab[6], btn_7, zone7);}

  else if(digitalRead(btn_8) == 1){play_sound(BassTab[7], btn_8, zone8);}
}
