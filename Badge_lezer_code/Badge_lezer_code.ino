/*
 * 
 * All the resources for this project: https://randomnerdtutorials.com/
 * Modified by Rui Santos
 * 
 * Modified for safe project by Andrés Lycke & Jeroen Dobbelaere
 * 
 * Created by FILIPEFLOP
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//const int buttonPin = 3;
//int buttonState = 0;
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  Serial.println(digitalRead(3));
  pinMode(6, OUTPUT);
  pinMode(3, INPUT_PULLUP);

    // initialize the LCD, 
  lcd.begin();
 
  // Turn on the blacklight and print a message.
  lcd.backlight();

}
void loop() 
{
  lcd.clear();
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
  if (content.substring(1) == "F9 00 8B 6E" || content.substring(1) == "04 70 48 32 10 4F 80") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(6 ,HIGH);
    Serial.println("WELCOME World");
    lcd.print("WELCOME");
    lcd.setCursor(0,1);
    lcd.print("World");
    
   // int buttonState = digitalRead(3);
    delay(3000);
    Serial.println(digitalRead(3));
    delay(1000);


  }
 
 else   {
    Serial.println(" Access denied");
    lcd.print("Access denied");
    delay(3000);
  }
    int buttonState = digitalRead(3);
    Serial.println(buttonState);
    
    if (buttonState == LOW){
      digitalWrite(6, LOW);
      Serial.println("RELAY off");
     // lcd.print("");
      delay(3000);
    }
} 
