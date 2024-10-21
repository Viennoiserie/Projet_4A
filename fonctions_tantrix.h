#ifndef TANTRIX_H
#define TANTRIX_H

#include <Arduino.h>
#include <Servo.h>
#include <TFT.h>  
#include <SPI.h>

// Pin definition for screen : 
// Chip Select - Commande/Data - Reset
#define cs   8
#define dc   9
#define rst  10

// Pin definition for servos
#define servoPin0 3
#define servoPin1 4
#define servoPin2 5
#define servoPin3 6

// Number of rows and columns for LEDs and buttons
#define NUM_LED_COLUMNS 4
#define NUM_LED_ROWS 4

#define NUM_BTN_COLUMNS 4
#define NUM_BTN_ROWS 4

#define NUM_COLORS 3

#define MAX_DEBOUNCE 3

//Creating servomotor's objects
Servo servoMotor0; 
Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;

// Creating an instance for the screen
TFT TFTscreen = TFT(cs, dc, rst);

// Global variables :
uint8_t LED_outputs[NUM_LED_COLUMNS][NUM_LED_ROWS];

int32_t next_scan;

const uint8_t btnselpins[4]   = {50,41,40,53};
const uint8_t btnreadpins[4]  = {46,47,48,49};
const uint8_t ledselpins[4]   = {42,43,44,45};

// RGB pins for each of 4 rows 
const uint8_t colorpins[4][3] = {{22,24,26}, {30,31,32},{33,34,35},{36,37,38}};

int8_t debounce_count[NUM_BTN_COLUMNS][NUM_BTN_ROWS];

void setPins()
{
    uint8_t i;

    for(i = 0; i < NUM_LED_COLUMNS; i++)
    {
        pinMode(ledselpins[i], OUTPUT);

        // With nothing selected by default
        digitalWrite(ledselpins[i], HIGH);
    }

    for(i = 0; i < NUM_BTN_COLUMNS; i++)
    {
        pinMode(btnselpins[i], OUTPUT);

        // With nothing selected by default
        digitalWrite(btnselpins[i], HIGH);
    }

    // Key return lines
    for(i = 0; i < 4; i++)
    {
        pinMode(btnreadpins[i], INPUT_PULLUP);
    }

    // LED drive lines
    for(i = 0; i < NUM_LED_ROWS; i++)
    {
        for(uint8_t j = 0; j < NUM_COLORS; j++)
        {
            pinMode(colorpins[i][j], OUTPUT);
            digitalWrite(colorpins[i][j], LOW);
        }
    }

    for(uint8_t i = 0; i < NUM_BTN_ROWS; i++)
    {
        for(uint8_t j = 0; j < NUM_BTN_COLUMNS; j++)
        {
            debounce_count[i][j] = 0;
        }
    }
}

void setupServos() {

  servoMotor0.attach(servoPin0); //Attribuer la pin de sortie à l'objet servo
  servoMotor1.attach(servoPin1);
  servoMotor2.attach(servoPin2);
  servoMotor3.attach(servoPin3);
}

void setupTantrix() {

  // Opens serial port, sets data rate to 115 200 bps
  Serial.begin(115200);

  Serial.print("Starting Setup...");

  // Setup hardware
  setPins();

  // Initiate global variables
  next_scan = millis() + 1;

  for(uint8_t i = 0; i < NUM_LED_ROWS; i++)
  {
    for(uint8_t j = 0; j < NUM_LED_COLUMNS; j++)
    {
      LED_outputs[i][j] = 0;
    }
  }
}

void setupScreen(){

  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setTextColor(ST7735_WHITE);
}

void writeToScreen(char* string) {

  TFTscreen.fillScreen(ST7735_BLACK);
  TFTscreen.text(string, 6, 57);
}

void find_button_press() {

  uint8_t val0 = digitalRead(btnreadpins[0]);
  uint8_t val1 = digitalRead(btnreadpins[1]);
  uint8_t val2 = digitalRead(btnreadpins[2]);
  uint8_t val3 = digitalRead(btnreadpins[3]);

  if(val0 == LOW) {
    digitalWrite(colorpins[0][0], HIGH);
  }
  if(val1 == LOW) {
    digitalWrite(colorpins[1][0], HIGH);
  }
  if(val2 == LOW) {
    digitalWrite(colorpins[2][0], HIGH);
  }
  if(val3 == LOW) {
    digitalWrite(colorpins[3][0], HIGH);
  }
}

void scan()
{

  uint8_t val;
  uint8_t i, j;
  uint8_t current = 0;

  // Run
  digitalWrite(btnselpins[current], LOW);
  digitalWrite(ledselpins[current], LOW);

  for(i = 0; i < NUM_LED_ROWS; i++)
  {
      uint8_t val = (LED_outputs[current][i] & 0x03);

      if(val)
      {
          digitalWrite(colorpins[i][val-1], HIGH);
      }
  }

  delay(1);

  for(j = 0; j < NUM_BTN_ROWS; j++)
  {
    val = digitalRead(btnreadpins[j]);

    if(val == LOW)
    {
      // active low: val is low when btn is pressed
      if(debounce_count[current][j] < MAX_DEBOUNCE)
      {
        debounce_count[current][j]++;
        if(debounce_count[current][j] == MAX_DEBOUNCE )
        {
          Serial.print("Key Down ");
          Serial.println((current * NUM_BTN_ROWS) + j);

          LED_outputs[current][j]++;
        }
      }
    }
    else
    {
      // otherwise, button is released
      if( debounce_count[current][j] > 0)
      {
        debounce_count[current][j]--;
        if( debounce_count[current][j] == 0 )
        {
          Serial.print("Key Up ");
          Serial.println((current * NUM_BTN_ROWS) + j);
        }
      }
    }
  }// for j = 0 to 3;

  delay(1);

  digitalWrite(btnselpins[current], HIGH);
  digitalWrite(ledselpins[current], HIGH);

  for(i = 0; i < NUM_LED_ROWS; i++)
  {
    for(j = 0; j < NUM_COLORS; j++)
    {
      digitalWrite(colorpins[i][j], LOW);
    }
  }

  current++;
  if (current >= NUM_BTN_COLUMNS)
  {
    current = 0;
  }
}

void positionMoteur0(int degre) {
  servoMotor0.write(degre);
}

void positionMoteur1(int degre) {
  servoMotor1.write(degre);
}

void positionMoteur2(int degre) {
  servoMotor2.write(degre);
}

void positionMoteur3(int degre) {
  servoMotor3.write(degre);
}

void resetPositionMoteur(int motorNumber) {

  switch(motorNumber) {
    case 0: 
      servoMotor0.write(0);
      break;
    
    case 1: 
      servoMotor1.write(0);
      break;

    case 2: 
      servoMotor2.write(0);
      break;

    case 3: 
      servoMotor3.write(0);
      break;

    default:
      servoMotor0.write(0);
      delay(500);
      servoMotor1.write(0);
      delay(500);
      servoMotor2.write(0);
      delay(500);
      servoMotor3.write(0);
      break;
  }
}

void backgroundColor(int r, int g, int b){
  TFTscreen.stroke(r, g, b);
}

#endif