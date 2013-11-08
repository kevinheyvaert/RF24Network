#include "Arduino.h"
#include "Irsensor.h"




Irsensor::Irsensor(int pin) :widget()
{
    _pinnummer=pin;
    pinMode(_pinnummer, INPUT);
    widget.begin();
    widget.setFilter('b');
    widget.setOrder(1);

}




int Irsensor::leesdesensor()
{
    
   Value=(12.5 * pow((analogRead(_pinnummer)*(0.00488758553275)), -1));
              
              if(Value > 40)
              {
                  Value=40;
              
              }
    
    return(Value);
}

int Irsensor::filtered()
{
  
    
    return (widget.run(leesdesensor()));

}

void Irsensor::printSerialDistance(int Value)
{
    Serial.println(Value);

}
int Irsensor::gemiddeldtien()
{
    
    if(count >9)
    {
        count =0;
        
    }
    Array10[count]=leesdesensor();
    
    for(int i=0; i<9; i++)
    {
        Gemiddeldtien+= Array10[i];
        
    
    }
    Gemiddeldtien= Gemiddeldtien/10;
    count++;
    
    return (Gemiddeldtien);
    

}
int Irsensor::gemiddeldduizend()
{
    if (count2 >99)
    {
        count2=0;
    
    }
    Array100[count2]=gemiddeldtien();
    
    for (int i=0; i<99;i++)
    {
        Gemiddeldduizend+=Array100[i];
        
    }
    
Gemiddeldduizend = Gemiddeldduizend/100;
  
    count2++;
         return(Gemiddeldduizend);

}

int Irsensor::ledpower()
{
    ledValue = map(filtered(),4,40,0,255);
    
    return ledValue;
}
int Irsensor::ledsterkte()
{
    Ledsterkte = map(ledpower(),0,255,0,100);
    return Ledsterkte;
}

bool Irsensor::isCloser(int afstand)
{
   
    if (afstand>leesdesensor())
    {
        Serial.print("Afstand is kleiner dan ");
        Serial.println(afstand);
        return true;
    }
    
   

}

bool Irsensor::isRising()
{
    Afstand =leesdesensor();
    delay(50);

    if (Afstand < leesdesensor())
    {
        
        Serial.println("Is Rising");
        return true;
        
    }

    else
    {
        return false;
    }
}

bool Irsensor::isFalling()
{
    Afstand =filtered();
    delay(50);
    
    if (Afstand > filtered())
    {
        Serial.println("is Falling");
        return true;
        
    }
    
    else
    {
        return false;
    }
}

