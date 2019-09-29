#ifndef RFID_H
#define RFID_H

#include <SPI.h>      //include the SPI bus library
#include <MFRC522.h>  //include the RFID reader library

#define SS_PIN  5  //slave select pin
#define RST_PIN 0  //reset pin

int block=2;  
byte buffer[18];
byte size = sizeof(buffer);
int trailerBlock=3;//determine trailer block for the sector

MFRC522 mfrc522(SS_PIN, RST_PIN);  // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;          //create a MIFARE_Key struct named 'key', which will hold the card information
MFRC522::StatusCode status;



void rfid_init();
int rfid_search();
void dump_byte_array(byte *buffer, byte bufferSize);

#endif
