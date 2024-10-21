#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SPEAKER 12 // Pin du speaker
#define ROUNDS 5   // Nombre de rounds que l'on va jouer

// Définition des pins boutons ET leds

#define led_1 27
#define led_2 29
#define led_3 26
#define led_4 28

#define btn_1 36
#define btn_2 37
#define btn_3 38
#define btn_4 39

// Cet array d'entiers contient tout les leds ET boutons

int ledArray[] = {led_1, led_2, led_3, led_4};
int btnArray[] = {btn_1, btn_2, btn_3, btn_4};

// Cet array d'entiers contient toutes les notes possibles (possible de les modifier !)

int BassTab[] = {2500,2300,2200,2000,1800,1600,1500,1300,1200,1000,800,600,500};

/**
*
* @return joue un son et allume une zone du bandeau 
*
* @param note : correspond à la note que vous souhaitez
* @param index : index utile
*
*/

void play_sound(int note, int index) {

  digitalWrite(ledArray[index], HIGH);

  while(digitalRead(btnArray[index]) == LOW){

    // On balance la sauce dans les speakers

    digitalWrite(SPEAKER, HIGH);
    delayMicroseconds(note);
    digitalWrite(SPEAKER, LOW);
    delayMicroseconds(note);
  }

  digitalWrite(ledArray[index], LOW);
}

/**
*
* @return écoute les 8 boutons : Cette fonction doit être utilisée dans le loop() !
*
*/

int listenButton() {

  // Je ne pense pas pouvoir faire de switch case ici alors bah :
  // Plein de if / else pour trouver quel boutons sont appuyés à chaque tick

  if(digitalRead(btn_1) == LOW){play_sound(BassTab[0], 0); return(0);}

  else if(digitalRead(btn_2) == LOW){play_sound(BassTab[1], 1); return(1);}

  else if(digitalRead(btn_3) == LOW){play_sound(BassTab[2], 2); return(2);}

  else if(digitalRead(btn_4) == LOW){play_sound(BassTab[3], 3); return(3);}

  else{return(4);}
}


/**
*
* @return joue une petite animation pour indiquer le passage d'un round à un autre
*
*/

void transition() {

  for(int i = 0; i < 4; i++) {

    digitalWrite(ledArray[i], HIGH);

    delay(100);

    digitalWrite(ledArray[i], LOW);
  }

  delay(100);

  for(int i = 0; i < 4; i++) {

    digitalWrite(ledArray[i], HIGH);

    delay(100);

    digitalWrite(ledArray[i], LOW);
  }
}


/**
*
* @return joue une petite animation pour indiquer la victoire
*
*/

bool win() {

  for(int i = 3; i >= 0; i--) {

    digitalWrite(ledArray[i], HIGH);

    delay(100);

    digitalWrite(ledArray[i], LOW);
  }

  delay(100);

  for(int i = 3; i >= 0; i--) {

    digitalWrite(ledArray[i], HIGH);

    delay(100);

    digitalWrite(ledArray[i], LOW);
  }
  return true;
}


/**
*
* @return joue une petite animation pour indiquer quelle notes jouer
*
* @param list : Une liste contenant autant de place que de rounds à jouer
* @param i : un entier qui indique jusqu'où il faut boucler la list pour l'affichage; ex : Si i = 2 et ROUNDS = 10, on bouclera uniquement jusqu'à 2.
*
*/

void showGame(int list[ROUNDS], int i) {

  for(int j = 0; j < i; j++) {

    digitalWrite(ledArray[list[j]], HIGH);

    for(int jj = 0; jj < 100; jj++){

      digitalWrite(SPEAKER, HIGH);
      delayMicroseconds(BassTab[list[j]]);
      digitalWrite(SPEAKER, LOW);
      delayMicroseconds(BassTab[list[j]]);
    }

    digitalWrite(ledArray[list[j]], LOW);

    delay(500);
  }
}

/**
*
* @return sert à lire les différents boutons appuyé par le joueur et vérifie si ce sont les bons
*
* @param list : Une liste contenant autant de place que de rounds à jouer
* @param i : un entier qui indique jusqu'où il faut boucler la list pour l'affichage; ex : Si i = 2 et ROUNDS = 10, on bouclera uniquement jusqu'à 2.
*
*/

bool checkGame(int list[ROUNDS], int i) {

  bool res = true;

  // Ces int ont des valeurs plus grandes que le maximum de leds (nous avons 4 leds, donc l'index max est 3) pour qu'elles ne soient pas prise en compte

  int previouslyPressed = 4;
  int currentlyPressed = 4;

  for(int j = 0; j < i; j++){

    // J'écoute quel bouton est appuyé

    currentlyPressed = listenButton();

    // Tant que c'est égal à 4 (donc que le joueur n'appuie sur aucun des boutons) on attends

    while(currentlyPressed == 4) { currentlyPressed = listenButton(); }

    // Si le bouton est le bon ET qu'il est différent de celui d'avant alors c'est juste

    if(currentlyPressed == list[j] && currentlyPressed != previouslyPressed) {

      previouslyPressed = currentlyPressed;
    }

    // Si le bouton est mauvais ET qu'il est différent de celui d'avant alors c'est faux.

    else if(currentlyPressed != list[j] && currentlyPressed != previouslyPressed) { 
      
      res = false;
      break; // Si c'est faux je sors et renvoie false !
    }
  }

  return(res); // Je retourne true si la combinaison est juste et false sinon.
}

/**
*
* @return sert à remplir la liste de valeurs vides (4 dans notre cas)
*
* @param list : Une liste contenant autant de place que de rounds à jouer
*
*/

void fillSteps(int array[ROUNDS]) { for(int i = 0; i < ROUNDS; i++) { array[i] = 4; }}

/**
*
* @return c'est la fonction qui gère le jeux
*
*/

bool game() {

  int gameSteps[ROUNDS];
  int newIndex;

  bool currentRes;

  // On initialise la liste

  fillSteps(gameSteps);

  // On démarre le jeux

  for(int i = 0; i < ROUNDS; i++) {

    newIndex = (rand() % (3 - 0 + 1)) + 0;

    // Si le chiffre donné est le même que le précedent alors je change de chiffre !

    if(i >= 1) { while(newIndex == gameSteps[i-1]) { newIndex = (rand() % (3 - 0 + 1)) + 0; } }

    // La liste change de valeur tour par tour (elle prend les entiers correspondant aux réponses à donner)

    gameSteps[i] = newIndex;

    // J'affiche le jeux au tour i
    showGame(gameSteps, i);

    // Je vérifie les réponses au tour i
    currentRes = checkGame(gameSteps, i);

    // Si c'est faux je quite la boucle for pour la recommencer depuis le début (avec de nouvelles valeurs !)
    if(!currentRes) { i = 0; }

    transition();
    delay(750);
  }

  win();
  return(true);
}

