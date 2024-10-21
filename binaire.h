#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#define LED_F 2

bool endBinaire;

bool binaire(int Tab[4])
{
  if(digitalRead(LED1) == Tab[0] && digitalRead(LED2) == Tab[1] && digitalRead(LED3) == Tab[2] && digitalRead(LED4) == Tab[3])
  {
    digitalWrite(LED_F,HIGH);
    Serial.println("SUCCES ETAPE 1");
    delay(3000);
    endBinaire = true;
  }
  else
  {
    digitalWrite(LED_F,LOW);
    endBinaire = false;
  }
  delay(50);
  return endBinaire;
}