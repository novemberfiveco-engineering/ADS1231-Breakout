#include "ADS1231.h"
#include "Arduino.h"

ADS1231::ADS1231(int pinDATA, int pinSCLK, int pinSPEED, int pinPDWN)
{
    _pinPDWN = pinPDWN;
    pinMode(_pinPDWN, OUTPUT);

    _pinSPEED = pinSPEED;
    pinMode(_pinSPEED, OUTPUT);

    _pinSCLK = pinSCLK;
    pinMode(_pinSCLK, OUTPUT);

    _pinDATA = pinDATA;
    pinMode(_pinDATA, INPUT);
}

void ADS1231::begin(bool highSpeed, bool power)
{
    if (highSpeed) {
        digitalWrite(_pinSPEED, HIGH);
    } else {
        digitalWrite(_pinSPEED, LOW);
    }

    if (power) {
        digitalWrite(_pinPDWN, HIGH);
    } else {
        digitalWrite(_pinPDWN, LOW);
    }

    digitalWrite(_pinDATA, HIGH);
    digitalWrite(_pinSCLK, LOW);
}

int ADS1231::read(long &val)
{
    int i = 0;
    unsigned long start;
    int startOffset;

    if (digitalRead(_pinSPEED) == HIGH) {
        startOffset = 19;
    } else {
        startOffset = 150;
    }

    start = millis();
    while (digitalRead(_pinDATA) != HIGH) {
        if (millis() > start + startOffset) {
            return -1;
        }
    }

    start = millis();
    while (digitalRead(_pinDATA) != LOW) {
        if (millis() > start + startOffset) {
            return -2;
        }
    }

    for (i = 23; i >= 0; i--) {
        digitalWrite(_pinSCLK, HIGH);
        val = (val << 1) + digitalRead(_pinDATA);
        digitalWrite(_pinSCLK, LOW);
    }

    val = (val << 8) / 256;

    digitalWrite(_pinSCLK, HIGH);
    digitalWrite(_pinSCLK, LOW);

    return 0;
}
