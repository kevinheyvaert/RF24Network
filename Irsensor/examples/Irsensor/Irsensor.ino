#include <Irsensor.h>

Irsensor sensor(A1);

void setup()

{
    
    Serial.begin(9600);
    
    
}


void loop()
{
    //Serial.println("<-------- Afstand ----------->");
    //sensor.printSerialDistance(sensor.leesdesensor());
    
   // Serial.println("<--------- Ledsterkte ---------->");
    //sensor.printSerialDistance(sensor.ledsterkte());
    //led power
    //analogWrite(13,sensor.ledpower());
    
   // Serial.println("<--------- Filterde Afstand ---------->");
   // sensor.printSerialDistance(sensor.filtered());
    
//Serial.println("<--------- Gemiddelde afstand 10 waardes ---------->");
    //sensor.printSerialDistance(sensor.gemiddeldtien());
    
//Serial.println("<--------- Gemiddelde afstand 1000 waardes ---------->");
    //sensor.printSerialDistance(sensor.gemiddeldduizend());
    
   // Serial.println("<--------- is dichter dan 10 ---------->");
    //sensor.printSerialDistance(sensor.isCloser(10));
    
    //Serial.println("<--------- is Rising als 1 is ---------->");
    //sensor.printSerialDistance(sensor.isRising());
    
   // Serial.println("<--------- is falling als 1 is ---------->");
    //sensor.printSerialDistance(sensor.isFalling());
    
    
    
    
    
    
}
