// Simple Transmitter and Receiver, Arduino by MohamadKh75
// 2017-09-27
// ********************


#include <SPI.h>    //to handle the communication interface with the modem
#include <RF24.h>   //the library which helps us to control the radio modem
#include <nRF24L01.h>   //to handle this particular modem driver


RF24 radio(7, 8);   //create a radio object and set the pins (7 for CE - 8 for CSN)
const byte rxAddr[6] = "00001";   //declare a global array (used for determine the modem that we want to communicate)

void setup()
{
  Serial.begin(9600);   //Set the serial conncetion to check the result in Serial Monitor
  
  radio.begin();    //activates the modem
  radio.openReadingPipe(0, rxAddr);   //determines the address of our modem which receives data
                                      //first arg. is the number of the stream
  
  radio.startListening();   //switch the modem to data receiving mode
}

void loop()
{
  if (radio.available())
  {
    char text[32] = {0};    //var. for the received msg
    radio.read(&text, sizeof(text));    //received msg
    
    Serial.println(text);   //print it in the Serial Monitor
  }

  else
    Serial.println("Oops!");
}

