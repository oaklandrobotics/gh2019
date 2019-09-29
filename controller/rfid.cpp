#include "rfid.h"

void rfid_init() {

  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)

  // Prepare the security key for the read and write functions.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;  //keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }

  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);

}

int rfid_search() {

  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return -1;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return -1;
  }

  Serial.println("Card selected");
  // Authenticate using key A
  Serial.println(F("Authenticating using key A..."));
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return -1;
  }

  Serial.print(F("Reading data from block ")); Serial.print(block);
  Serial.println(F(" ..."));
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(block, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  Serial.print(F("Data in block ")); Serial.print(block); Serial.println(F(":"));
  dump_byte_array(buffer, 16); Serial.println();
  Serial.println();

  for (int i = 0; i < 15; i++) {
    Serial.print(buffer[i]);
  }
  Serial.println();

  // Concatination for address to return
  int adr = (buffer[3] << 3) + (buffer[2] << 2) + (buffer[1] << 1) + buffer[0];
  Serial.print("Returning : ");
  Serial.println(adr);
  return adr;
  

}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
