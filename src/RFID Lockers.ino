#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "61 57 CC 09") //Leeg
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }

  if (content.substring(1) == "C3 30 90 E5") //Mickey
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }

    if (content.substring(1) == "82 9C 1B 4E") //Bryan
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }


  if (content.substring(1) == "9B EE F9 24") //Jordy
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }

 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
}
