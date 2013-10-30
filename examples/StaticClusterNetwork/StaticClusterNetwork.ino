/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

//extern void board_start(const char* program_name);

// nRF24L01(+) radio attached to SPI and pins 8 & 9
RF24 radio(8,9);

// Network uses that radio
RF24Network network(radio);

// Address of our node
const uint16_t this_node = 0;

// Address of the other node
const uint16_t other_node = 1;

// How often to send 'hello world to the other unit
const unsigned long interval = 2000; //ms

// When did we last send?
unsigned long last_sent;

void setup(void)
{
  Serial.begin(57600);
  Serial.println("RF24Network/examples/helloworld_rx/");
  //board_start("RF24Network/examples/helloworld_tx/");
  
 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
}

void loop (void)
{
  reading();
  transmitting();
}

void reading()
{
  // Pump the network regularly
  network.update();

  // Is there anything ready for us?
  while ( network.available() )
  {
    // If so, grab it and print it out
    RF24NetworkHeader header;
    static char message[32];
    network.read(header,message,sizeof(message));
    Serial.print("Received: ");
    Serial.println(message);
  }
}

void transmitting()
{
  // Pump the network regularly
  network.update();

  // If it's time to send a message, send it!
  unsigned long now = millis();
  if ( now - last_sent > interval  )
  {
    last_sent = now;

    //toggleLED();
    printf("Sending...\r\n");
    const char* hello = "Hello, world!";
    RF24NetworkHeader header(/*to node*/ other_node);
    bool ok = network.write(header,hello,strlen(hello));
    if (ok)
    {
      printf("\tok.\r\n");
      Serial.print("Send: ");
    }
    else
    {
      printf("\tfailed.\r\n");
      delay(250); // extra delay on fail to keep light on longer
    }
    //toggleLED();
  }
}

