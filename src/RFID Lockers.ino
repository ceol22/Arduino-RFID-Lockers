#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27,16,2);

Servo kluis1;
Servo kluis2;
Servo kluis3;

int led1 = 4;
int led2 = 5;
int led3 = 6;

int button1 = 2;
int x = 0;

int kluis1Val = 0;
int kluis2Val = 0;
int kluis3Val = 0;


void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();

  pinMode(button1,INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3), OUTPUT);

  kluis1.attach(3);
  kluis2.attach(5);
  kluis3.attach(6);

  kluis1.write(0);
  kluis2.write(0);
  kluis3.write(0);

  Serial.println("Approximate your card to the reader...");
  Serial.println();

  lcd.setCursor(0,0);
  lcd.print("Welkom,");
  lcd.setCursor(0,1);
  lcd.print("Scan uw pas");
}


void loop(){

  while(x==0){

    int buttonVal = digitalRead(button1);
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
      mfrc522.PICC_HaltA();
        Serial.println("Authorized access");
        kluis1.write(90);
        kluis2.write(90);
        kluis3.write(90);
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led3,HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Waarschuwing!");
        lcd.setCursor(0,1);
        lcd.print("Alles geopend");
        x = 1;
        delay(3000);
    }

    if (content.substring(1) == "C3 30 90 E5") //Mickey
    {
      mfrc522.PICC_HaltA();
        Serial.println("Authorized access");
        Serial.println();
        kluis3.write(90);
        digitalWrite(led3,HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Hoi Mickey Doos");
        lcd.setCursor(0,1);
        lcd.print("Snellerder");
        x = 1;
        delay(3000);
    }

      if (content.substring(1) == "82 9C 1B 4E") //Bryan
      {
        mfrc522.PICC_HaltA();
        Serial.println("Authorized access");
        Serial.println();
        kluis2.write(90);
        digitalWrite(led2,HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Mui Olde rukker");
        lcd.setCursor(0,1);
        lcd.print("Anmak'n");
        x = 1;
        delay(3000);
      }


      if (content.substring(1) == "9B EE F9 24") //Jelle
      {
        mfrc522.PICC_HaltA();
        Serial.println("Authorized access");
        Serial.println();
        kluis1.write(180);
        digitalWrite(led1,HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Hoi Jelle");
        lcd.setCursor(0,1);
        lcd.print("Doe maar rustig");
        x = 1;
        delay(3000);
      }

  


  }


  while(x ==1){
   mfrc522.PICC_HaltA();
    int buttonVal = digitalRead(button1);
    delay(100);
    if(buttonVal == 0){
    kluis1.write(180);
    kluis2.write(180);
    kluis3.write(180);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Doei");
    lcd.setCursor(0,1);
    lcd.print("Kalm an doen");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Welkom,");
    lcd.setCursor(0,1);
    lcd.print("Scan uw pas");
    x = 0;

  }
   buttonVal = digitalRead(button1);
  Serial.println(buttonVal);
  }
}
