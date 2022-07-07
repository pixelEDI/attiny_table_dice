/*
        _          _ ______ _____ _____ 
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |  
 | '_ \| \ \/ / _ \ |  __| | |  | || |  
 | |_) | |>  <  __/ | |____| |__| || |_ 
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |                                    
 |_|                                    
                             
www.pixeledi.eu | twitter.com/pixeledi
LED Dice | V1.0 | 06/2022

*/

#include <Arduino.h>

const byte led1 = 9;
const byte led2 = 8;
const byte led3 = 6;
const byte led4 = 3;
const byte led5 = 2;
const byte led6 = 4;
const byte led7 = 5;
const byte button = 0;

byte dice = 0;
unsigned long TimeNow;
unsigned long lastTimeButtonChange = millis();
unsigned int debounceDelay = 50;
byte buttonState = LOW;

const byte NUM_ARRAYS = 7;
int allLEDs[NUM_ARRAYS] = {led1, led2, led3, led4, led5, led6, led7};

void turnOffAllLEDs()
{
  for (int i = 0; i < NUM_ARRAYS; i++)
  {
    digitalWrite(allLEDs[i], LOW);
  }
}

void letsGetStarted()
{
  for (int i = 0; i < NUM_ARRAYS; i++)
  {
    digitalWrite(allLEDs[i], HIGH);
    delay(300);
  }

  turnOffAllLEDs();

  for (int i = 0; i < 3; i++)
  {
    for (int i = 0; i < NUM_ARRAYS; i++)
    {
      digitalWrite(allLEDs[i], HIGH);
    }
    delay(300);
    turnOffAllLEDs();
    delay(300);
  }
}

void diceToLed()
{
  turnOffAllLEDs();

  switch (dice)
  {
  case 1:
    digitalWrite(led4, HIGH);
    break;
  case 2:
    digitalWrite(led1, HIGH);
    digitalWrite(led7, HIGH);
    break;
  case 3:
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    break;
  case 4:
    digitalWrite(led1, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led7, HIGH);
    break;
  case 5:
    digitalWrite(led1, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led7, HIGH);
    break;
  case 6:
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
    break;
  }
}

void rollTheDice()
{
  byte cnt = 0;
  byte diceDelay = 20;

  while (cnt < 20)
  {
    dice = random(1, 7);
    diceToLed();
    diceDelay += 7;
    delay(diceDelay);
    cnt++;
  }
}

void setup()
{

  randomSeed(analogRead(7));

  pinMode(button, OUTPUT);

  for (int i = 0; i < NUM_ARRAYS; i++)
  {
    pinMode(allLEDs[i], OUTPUT);
  }

  turnOffAllLEDs();
  letsGetStarted();
}

void loop()
{

  // byte dice=0;
  // unsigned long TimeNow;
  // unsigned long lastTimeButtonChange = millis();
  // unsigned int debounceDelay=50;
  // byte buttonState = LOW;

  TimeNow = millis();

  if (TimeNow - lastTimeButtonChange > debounceDelay)
  {

    byte newButtonState = digitalRead(button);

    if (newButtonState != buttonState)
    {
      lastTimeButtonChange = TimeNow;
      buttonState = newButtonState;

      if (buttonState == HIGH)
      {
        // debugg
        //digitalWrite(led1, !digitalRead(led1));
        rollTheDice();
      }
    }
  }
}