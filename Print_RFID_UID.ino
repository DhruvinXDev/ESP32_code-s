#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 22
#define SS_PIN 21

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Scan your RFID card/tag:");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  
  // Print UID
  Serial.print("Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();
  
  // Print UID in format for code
  Serial.print("For code: {");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print("0x");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) {
      Serial.print(", ");
    }
  }
  Serial.println("};");
  //For code: {0xD3, 0x97, 0xB1, 0xB};

  //For code: {0x91, 0x6C, 0xDA, 0xB}; card

  delay(1000);
}
