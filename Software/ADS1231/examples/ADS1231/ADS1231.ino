/*
  ADS1231.ino - Library for communicating with the ADS1231 breakout.
  Created by November Five, December 29, 2016.
*/

#include "ADS1231.h"

ADS1231 ads1231(2, 3, 4, 5);

void setup()
{
    Serial.begin(9600);
    ads1231.begin(false, true);
}

void loop()
{
    long val;
    ads1231.read(val);
    Serial.println(val);
    delay(1000);
}
