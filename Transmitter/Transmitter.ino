// Simple Transmitter and Receiver, Arduino by MohamadKh75
// 2017-09-29
// ********************


#include <SPI.h>    //to handle the communication interface with the modem
#include <RF24.h>   //the library which helps us to control the radio modem
#include <nRF24L01.h>   //to handle this particular modem driver


RF24 radio(7, 9);   //create a radio object and set the pins (7 for CE - 8 for CSN)
const byte rxAddr[6] = "00001";   //declare a global array (used for determine the modem that we want to communicate)
bool is_sending = false;

void setup()
{
  Serial.begin(9600);   //Set the serial conncetion to check the result in Serial Monitor
  
  radio.begin();    //activates the modem
  radio.setRetries(15, 15);   //[first arg * 250] ms  (here is 15*250 = 3750 ms) for retry to send the data in case of not receiving by another modem
                              //second arg is number of attempts 
  radio.openWritingPipe(rxAddr);    //sets the address of the receiver

  radio.stopListening();    //switch the modem to data transmission mode
}

void loop()
{
  const char text[] = "Hello World; it's MohamadKh75!";    //our msg
  is_sending = radio.write(&text, sizeof(text));   //send the msg! - PS: Through this method, you can send up to 32 bytes at one time
  
  Serial.println(is_sending);   //print if the sending was successful
  
  delay(1000);    //send the msg every second to the receiver
}
