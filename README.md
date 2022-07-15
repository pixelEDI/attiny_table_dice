<img src="https://img.shields.io/badge/-ATtiny%20Project-blue.svg?&amp;style=flat-square&amp" style="max-width: 100%;"> <img src="https://img.shields.io/badge/-PlattformIO-orange.svg?&amp;style=flat-square&amp" style="max-width: 100%;">


# General info
[![](https://yt-embed.live/embed?v=09OOl_hkTiM)](http://www.youtube.com/watch?v=09OOl_hkTiM "electronic table dice")

## Code
- we work with the FastLED.h library
- first we declare all the button pins, the data pin for the LEDs and an array for the LEDs
- we also declare some flags for the buttons and some variables for a "blink without delay"
- the letsGetStarted function shows us at the beginning that all the LEDs are working properly. In this case we work with delays.
- in the function setLEDColor we match the buttons with the color of the LEDs so if you press the yellow button the LEDs light up in yellow as well.
-in the function diceToLed we combine the correct LEDs with the value of the dice so that we get the usual appearance.
- the function rollTheDice shows us a small frequency of flickering through the dice values until the rolled value is displayed
- for a true random value we work with randomSeed, which is connected to a pin.
- in the loop we debounce the buttons and roll the dice with blink without delay.

## Hardware
- The table dice runns on an ATtiny84 or even 85.
- We used 7 WS2812b single LEDs for the dice "display" and 4 large push buttons with 10k Ω resistors. 
- The dice is powered by a 9 volt block battery, so you need a 5 volt voltage converter. 
 
![Verdrahtung](https://github.com/pixelEDI/attiny_table_dice/blob/main/tableDice_wiring.jpg)


## 3D Case
Get the Case:  [Thingiverse](https://www.thingiverse.com/thing:5432878)

You like it? Then I would be very happy if you treat me to a coffee on [ko-fi.com/pixeledi](https://www.ko-fi.com/pixeledi)
