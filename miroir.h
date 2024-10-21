#include <Servo.h>

#define potPIN0 A0
#define potPIN1 A1
#define potPIN2 A2

#define servoPin0 10
#define servoPin1 9
#define servoPin2 8

#define laser 20
#define LED 22
#define photores A3

int value1;
int value2;
int value3;
int sensorValue;

Servo servoMotor0;
Servo servoMotor1;
Servo servoMotor2;

bool endMiroir = false;

bool miroir()
{
    while(!endMiroir)
    {
        digitalWrite(laser, HIGH);
        sensorValue = analogRead(photores);
        
        /* Controle servo1 */
        value1 = analogRead(potPIN0);
        value1 = map(value1, 0, 1023, 0, 180);
        servoMotor0.write(value1);

        /* Controle servo2 */
        value2 = analogRead(potPIN1);
        value2 = map(value2, 0, 1023, 0, 180);
        servoMotor1.write(value2);   

        /* Controle servo3 */
        value3 = analogRead(potPIN2);
        value3 = map(value3, 0, 1023, 0, 180);
        servoMotor2.write(value3);   
        
        delay(15); 
        if(analogRead(photores)>500)
        {
        endMiroir = true;
        digitalWrite(LED, HIGH);
        Serial.println("SUCCES ETAPE 3");
        delay(3000);
        }
    }
    return endMiroir;
}

