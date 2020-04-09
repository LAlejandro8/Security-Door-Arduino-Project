#include <Keypad.h>
#include <Servo.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
   
  char* secretCode = "221125";
  int position = 0;
  Servo Servomotor;
  
  int ledRojo = 13;
  int ledAzul = 12;
  int ServoMotorAzul = 10;
   
  const byte rows = 4;
  const byte cols = 4;
  char keys[rows][cols] = {
  
   {'1','2','3','A'},
   {'4','5','6','B'},
   {'7','8','9','C'},
   {'*','0','#','D'}
 };
  
 byte rowPins[rows] = {9, 8, 7, 6};
 byte colPins[cols] = {5, 4, 3, 2};
 Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);
 LiquidCrystal lcd (19, 18, 17, 16, 15, 14);
  
 void setup()
 {

   Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.print("  APPduDoor2.0  ");
   delay(1500);
   lcd.clear();
   setLocked(true);
   pinMode(ledRojo, OUTPUT);
   pinMode(ledAzul, OUTPUT);
 }
  
 void loop()
 {
  
   char key = keypad.getKey();

      if(Serial.available()>0)
   {
     key = Serial.read();
   }
   
       if (key == '*' || key == '#')
   {
     position = 0;
     setLocked(true);
   } 
       if (key == secretCode[position])
   {
     position ++;
   }
       if (position == 6)
   {
     setLocked(false);
   }
   
   delay(100);
 }
  
 void setLocked(int locked)
 {
   char key = keypad.getKey();
   if (locked){
   
   lcd.setCursor(0, 0);
   lcd.print("   Bloqueado!   ");
   lcd.setCursor(0, 1);
   lcd.print("   Cerrando...  ");
   delay(2000);
   lcd.clear();
   lcd.setCursor(0, 0);
   digitalWrite(ledRojo, HIGH); 
   digitalWrite(ledAzul, LOW);            
   lcd.print("Digite su clave:");
   lcd.setCursor(0, 1);
   lcd.blink();
   Servomotor.attach(ServoMotorAzul);
   Servomotor.write(0);
   }
  
 else{
  
   lcd.setCursor(0, 0);
   lcd.print("  Desbloqueado  ");
   lcd.setCursor(0, 1);
   lcd.print("   Abriendo...  ");
   delay(2000);
   lcd.clear();
   lcd.setCursor(0, 0);
   digitalWrite(ledAzul, HIGH);
   digitalWrite(ledRojo, LOW);   
   lcd.print("  Bienvenido!!  ");
   Servomotor.attach(ServoMotorAzul);
   Servomotor.write(90);
   
   }
}
 
                
