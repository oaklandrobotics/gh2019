#ifndef RFID_TAG_H
#define RFID_TAG_H

#include <SPI.h>      //include the SPI bus library
#include <MFRC522.h>  //include the RFID reader library

#define SS_PIN  5  //slave select pin
#define RST_PIN 0  //reset pin

void rfid_init();
int rfid_search();
void dump_byte_array(byte *buffer, byte bufferSize);

#endif
