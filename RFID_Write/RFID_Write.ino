#include <SPI.h>      //include the SPI bus library
#include <MFRC522.h>  //include the RFID reader library

#define SS_PIN  5  //slave select pin
#define RST_PIN 0  //reset pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;          //create a MIFARE_Key struct named 'key', which will hold the card information

//this is the block number we will write into and then read.
int block=2;  
byte buffer[18];
byte size = sizeof(buffer);
//byte blockcontent[16] = {"Last-Minute-Engg"};  //an array with 16 bytes to be written into one of the 64 card blocks is defined
byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //all zeros. This can be used to delete a block.
MFRC522::StatusCode status;


//This array is used for reading out a block.
byte readbackblock[18];
char choice;

void setup() 
{
    Serial.begin(9600);        // Initialize serial communications with the PC
    SPI.begin();               // Init SPI bus
    mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
    Serial.println("Scan a MIFARE Classic card");
  
  // Prepare the security key for the read and write functions.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;  //keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }
  pinMode(36, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);


  
    Serial.println("Select ID to write. 0 through F");
    while (!Serial.available());
    choice = Serial.read();
    blockcontent[0] = choice == '1' || choice == '3' || choice == '5' || choice == '7' || choice == '9' || choice == 'B' || choice == 'D' || choice == 'F' ? 1 : 0;
    blockcontent[1] = choice == '2' || choice == '3' || choice == '6' || choice == '7' || choice == 'A' || choice == 'B' || choice == 'E' || choice == 'F' ? 1 : 0;
    blockcontent[2] = choice == '4' || choice == '5' || choice == '6' || choice == '7' || choice == 'C' || choice == 'D' || choice == 'E' || choice == 'F' ? 1 : 0;
    blockcontent[3] = choice == '8' || choice == '9' || choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D' || choice == 'E' || choice == 'F' ? 1 : 0;

}

void loop()
{  
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

    Serial.println("card selected");

   //the blockcontent array is written into the card block
   writeBlock(block, blockcontent);
   
   //read the block back
   readBlock();
   //uncomment below line if you want to see the entire 1k memory with the block written into it.
  // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
   
   //print the block contents
//   Serial.print("read block: ");
//   for (int j=0 ; j<16 ; j++)
//   {
//     Serial.write (readbackblock[j]);
//   }
//   Serial.println("");

   
}


//Write specific block    
int writeBlock(int blockNumber, byte arrayAddress[]) 
{
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber+1)%4 == 0){Serial.print(blockNumber);Serial.println(" is a trailer block:");return 2;}
  Serial.print(blockNumber);
  Serial.println(" is a data block:");
  
  //authentication of the desired block for access
  MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed: ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  
  //writing the block 
  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK) {
           Serial.print("MIFARE_Write() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return 4;//return "4" as error message
  }
  Serial.println("block was written");
}



//Read specific block
void readBlock(){ 
    int largestModulo4Number=block/4*4;
    int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector
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
       // Authenticate using key B

}
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
