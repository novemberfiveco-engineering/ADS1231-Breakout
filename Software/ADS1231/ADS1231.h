#ifndef ADS1231_h
#define ADS1231_h

#include <Arduino.h>

class ADS1231
{
  public:
    ADS1231(int pinDATA, int pinSCLK, int pinSPEED, int pinPDWN);
    void begin(bool highSpeed, bool power);
    int read(long &val);

  private:
    int _pinDATA;
    int _pinSCLK;
    int _pinSPEED;
    int _pinPDWN;
};

#endif
