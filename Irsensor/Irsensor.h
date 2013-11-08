#ifndef Irsensor
#define Irsensor_h

#include "Arduino.h"
#include "SignalFilter.h"

class Irsensor
{
  public:
    Irsensor(int pin);
    int leesdesensor();
    void printSerialDistance(int);
    int gemiddeldtien();
    int gemiddeldduizend();
    int filtered();
    int ledpower();
    int ledsterkte();
    bool isCloser(int);
    bool isRising();
    bool isFalling();
    
    
  private:
    int _pinnummer;
    int count;
    int count2;
    int Value;
    int Gemiddeldtien;
    int Gemiddeldduizend;
    int Array10[10];
    int Array100[100];
    int ledValue;
    int Ledsterkte;
    int Afstand;
    SignalFilter widget;
    
    
};

#endif
