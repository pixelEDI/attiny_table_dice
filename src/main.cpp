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
Table Dice| V1.0 | 06/2022

*/

#include <Arduino.h>
#include "FastLED.h"

const byte buttonYellow = 0;
const byte buttonBlue = 1;
const byte buttonRed = 2;
const byte buttonGreen = 3;
const byte DATA_PIN = 5;

const byte NUM_LEDS = 7;
CRGB leds[NUM_LEDS];

// flags
bool yellowButton = false;
bool blueButton = false;
bool redButton = false;
bool greenButton = false;
byte cRed = 0;
byte cGreen = 0;
byte cBlue = 0;

byte dice;
unsigned long TimeNow;
unsigned long lastTimeButtonChange = millis();
unsigned int debounceDelay = 50;
byte buttonState = LOW;
byte newButtonState;

void turnOffAllLEDs()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].setRGB(0, 0, 0);
  }
  FastLED.show();
}

void getStarted()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].setRGB(254, 1, 154);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(350);
  }

  turnOffAllLEDs();

  for (int i = 0; i < 3; i++)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(254, 1, 154);
      FastLED.setBrightness(60);
      FastLED.show();
    }
    delay(350);
    turnOffAllLEDs();
    delay(350);
  }
}

void setAllButtonFlagsFalse()
{
  yellowButton = false;
  redButton = false;
  greenButton = false;
  blueButton = false;
}

void whichButtonPressed()
{

  if (digitalRead(buttonYellow) == HIGH)
  {
    setAllButtonFlagsFalse();
    yellowButton = true;
  }
  else if (digitalRead(buttonBlue) == HIGH)
  {
    setAllButtonFlagsFalse();
    blueButton = true;
  }
  else if (digitalRead(buttonGreen) == HIGH)
  {
    setAllButtonFlagsFalse();
    greenButton = true;
  }
  else if (digitalRead(buttonRed) == HIGH)
  {
    setAllButtonFlagsFalse();
    redButton = true;
  }
}

void setLEDColor()
{
  if (yellowButton)
  {
    newButtonState = digitalRead(buttonYellow);
    cRed = 255;
    cGreen = 255;
    cBlue = 0;
  }
  else if (blueButton)
  {
    newButtonState = digitalRead(buttonBlue);
    cRed = 0;
    cGreen = 0;
    cBlue = 255;
  }
  else if (greenButton)
  {
    newButtonState = digitalRead(buttonGreen);
    cRed = 0;
    cGreen = 255;
    cBlue = 0;
  }
  else if (redButton)
  {
    newButtonState = digitalRead(buttonRed);
    cRed = 255;
    cGreen = 0;
    cBlue = 0;
  }
}

void diceToLed()
{
  turnOffAllLEDs();
  switch (dice)
  {
  case 1:
    leds[3].setRGB(cRed, cGreen, cBlue);
    break;

  case 2:
    leds[2].setRGB(cRed, cGreen, cBlue);
    leds[4].setRGB(cRed, cGreen, cBlue);
    break;
  case 3:
    leds[0].setRGB(cRed, cGreen, cBlue);
    leds[3].setRGB(cRed, cGreen, cBlue);
    leds[6].setRGB(cRed, cGreen, cBlue);
    break;

  case 4:
    leds[0].setRGB(cRed, cGreen, cBlue);
    leds[2].setRGB(cRed, cGreen, cBlue);
    leds[4].setRGB(cRed, cGreen, cBlue);
    leds[6].setRGB(cRed, cGreen, cBlue);
    break;

  case 5:
    leds[0].setRGB(cRed, cGreen, cBlue);
    leds[2].setRGB(cRed, cGreen, cBlue);
    leds[3].setRGB(cRed, cGreen, cBlue);
    leds[4].setRGB(cRed, cGreen, cBlue);
    leds[6].setRGB(cRed, cGreen, cBlue);
    break;

  case 6:
    leds[0].setRGB(cRed, cGreen, cBlue);
    leds[1].setRGB(cRed, cGreen, cBlue);
    leds[2].setRGB(cRed, cGreen, cBlue);
    leds[4].setRGB(cRed, cGreen, cBlue);
    leds[5].setRGB(cRed, cGreen, cBlue);
    leds[6].setRGB(cRed, cGreen, cBlue);
    break;
  }

  FastLED.setBrightness(20);
  FastLED.show();
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
  pinMode(buttonYellow, INPUT);
  pinMode(buttonBlue, INPUT);
  pinMode(buttonGreen, INPUT);
  pinMode(buttonRed, INPUT);

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  turnOffAllLEDs();
  getStarted();
  randomSeed(analogRead(0));
}

void loop()
{
  TimeNow = millis();

  if (TimeNow - lastTimeButtonChange > debounceDelay)
  {

    whichButtonPressed();
    setLEDColor();

    if (newButtonState != buttonState)
    {
      lastTimeButtonChange = TimeNow;
      buttonState = newButtonState;

      if (buttonState == HIGH)
      {
        rollTheDice();
      }
    }
  }
}