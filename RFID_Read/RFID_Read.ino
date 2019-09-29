#include <SPI.h>      //include the SPI bus library
#include <MFRC522.h>  //include the RFID reader library

#define SS_PIN  5  //slave select pin
#define RST_PIN 0  //reset pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;          //create a MIFARE_Key struct named 'key', which will hold the card information

int block=2;  
byte buffer[18];
byte size = sizeof(buffer);
MFRC522::StatusCode status;
    int largestModulo4Number=block/4*4;
    int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector
    
void setup() 
{
    Serial.begin(115200);        // Initialize serial communications with the PC
    SPI.begin();               // Init SPI bus
    mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
    Serial.println("Scan a MIFARE Classic card");
  
  // Prepare the security key for the read and write functions.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;  //keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);

  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
}

void loop()
{  
  //Serial.println("Beginning of loop");
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    Serial.println("Debug Point 5");
    return;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    Serial.println("Debug Point 4");
    return;
  }
    Serial.println("Debug Point 1");
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

    Serial.println("card selected");

    // Authenticate using key A
    Serial.println(F("Authenticating using key A..."));
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
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

    for (int i=0; i<15; i++){
      Serial.print(buffer[i]);
    }

    digitalWrite(26,buffer[3]);
    digitalWrite(27,buffer[2]);
    digitalWrite(14,buffer[1]);
    digitalWrite(12,buffer[0]);

    Serial.println("This should loop back");
    Serial.println("Debug point 2");
    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

    return;
    Serial.println("Debug point 3");
}




void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
