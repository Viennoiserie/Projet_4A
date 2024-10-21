#include <Servo.h>
#include "Codes_Matrice.h"
#include "binaire.h"
#include "miroir.h"
#include "simon.h"

int PL = 7;

bool etape1 = false;
bool etape2 = false;
bool etape3 = false;
bool etape4 = false;
bool etape5 = false;

void setup() {
  
  Serial.begin(9600);

  pinMode(LED1,INPUT);
  pinMode(LED2,INPUT);
  pinMode(LED3,INPUT);
  pinMode(LED4,INPUT);
  pinMode(PL, INPUT);

  pinMode(LED_F,OUTPUT);

  servoMotor0.attach(servoPin0);
  servoMotor1.attach(servoPin1);
  servoMotor2.attach(servoPin2);

  pinMode(laser, OUTPUT); //LASER
  pinMode(LED, OUTPUT); //LED
  pinMode(photores, INPUT); //PHOTORES

  pinMode(BUTTON_NORTH, INPUT);
  pinMode(BUTTON_SOUTH, INPUT);
  pinMode(BUTTON_EAST, INPUT);
  pinMode(BUTTON_WEST, INPUT);

  strip.begin();
  strip.clear();           
  strip.show(); 

  strip.setBrightness(BRIGHTNESS);

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

  if(!etape1)
  {
    int Tab[4] = {1,0,0,1};
    etape1 = binaire(Tab);
  }

  if(etape1 && !etape2)
  {
    if(digitalRead(PL) == 1)
    {
      Serial.println("SUCCES ETAPE 2");
      delay(3000);
      etape2 = true;
    }
  }

  if(etape2 && !etape3)
  {
    etape3 = miroir();
  }

  if(etape3 && !etape4)
  {
    if(parcours())
    {
      Serial.println("SUCCES ETAPE 4");
      etape4 = true;
    } 
  }
  if(etape4 && !etape5)
  {
    if(game())
    {
      etape5 = true;
      Serial.println("---------------------\nESCAPE GAME TERMINE !\n---------------------");
      delay(3000);
      exit(0);
    }
  }
}


