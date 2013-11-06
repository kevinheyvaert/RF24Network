/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
 
 /* 
     edited by Joris Huybrechts <jorisadri@hotmail.com>
     
     Example for sending data to node you defined. 
      
 */


//#include <avr/pgmspace.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include "nodeconfig.h"
#include "printf.h"

// This is for git version tracking.  Safe to ignore
#ifdef VERSION_H
#include "version.h"
#else
#define __TAG__ "Unknown"
#endif

// nRF24L01(+) radio using the Getting Started board
RF24 radio(8,7);
RF24Network network(radio);

// Our node address
uint16_t this_node;

// the adres for receiving node
uint16_t to;

// for example
char info;



// Array of nodes we are aware of
const short max_active_nodes = 10;
uint16_t active_nodes[max_active_nodes];
short num_active_nodes = 0;
short next_ping_node_index = 0;

// Prototypes for functions to send & handle messages
void send_N(uint16_t to);  //Sends adres data from nodes
void handle_A(RF24NetworkHeader& header); //Handels packet you recieved when it is not address data.
void handle_N(RF24NetworkHeader& header); // handels recieved address data
void add_node(uint16_t node); // add new node

void setup(void)
{
    
    // Print preamble
    Serial.begin(57600);
    printf_begin();
    printf_P(PSTR("\n\rRF24Network/examples/meshping/\n\r"));
    printf_P(PSTR("VERSION: " __TAG__ "\n\r"));
    
    
    // Pull node address out of eeprom
    
    // Which node are we?
    this_node = nodeconfig_read();
    
    //
    // Bring up the RF network
    //
    
    SPI.begin();
    radio.begin();
    network.begin(/*channel*/ 100, /*node address*/ this_node );
}

void loop (void)
{
    
    network.update();
    //is there data for us
    while (network.available())
    {
        //look to the packet
        RF24NetworkHeader header;
        network.peek(header);
        
        //Send to correct handler
        switch (header.type)
        {
            case 'A':
                handle_A(header);
                break;
            case 'N':
                handle_N(header);
                break;
            default:
                Serial.println("Wrong message type:");
                break;
        };
    }
    
    // if youre not the base(0) then do what this node neet to do and send data.
    if ( this_node > 00 || to == 00 )
    {
        //example code
        Serial.flush() ;//flush all previous received and transmitted data
        while(Serial.available()) {
            info = Serial.read();
            senddata(0,info);// here the node send his information to the base
        }
    }
    //if you are the base send node addresses
    else
    {
        send_N(to);
    }
    
    
}

//this function sends the actual info
void senddata(/*node address*/uint16_t to, /*data to transmit. you can choose other types too*/ char info )
{
    RF24NetworkHeader header(to, 'A');
    
    boolean issend= network.write(header,&info,sizeof(info));
    
    if(issend == true)
    {
        Serial.println("Transmitted");
    }
    //look for new nodes
    nodeconfig_listen();
}


// if data arrive this function will start. Change if needed
void handle_A(RF24NetworkHeader& header)
{
    char info;
    network.read(header,&info,sizeof(char));
    Serial.println(info);
}


void add_node(uint16_t node)
{
    // Do we already know about this node?
    short i = num_active_nodes;
    while(i--)
    {
        if (active_nodes[i] == node)
            break;
    }
    
    if ( i == -1 && num_active_nodes < max_active_nodes )
    {
        active_nodes[num_active_nodes++] = node;
    }
    
}


// handels when there are node addresses
void handle_N(RF24NetworkHeader& header)
{
    static uint16_t incoming_nodes[max_active_nodes];
    
    network.read(header,&incoming_nodes,sizeof(incoming_nodes));
    printf_P(PSTR("%lu: APP Received nodes from 0%o\n\r"),millis(),header.from_node);
    
    int i = 0;
    while ( i < max_active_nodes && incoming_nodes[i] > 00 )
        add_node(incoming_nodes[i++]);
}

// sender for base.
void send_N(uint16_t to)
{  // sends a list of active nodes
    RF24NetworkHeader header(/*to node*/ to, /*type*/ 'N' /*Time*/);
    boolean a = network.write(header,active_nodes,sizeof(active_nodes));
}


