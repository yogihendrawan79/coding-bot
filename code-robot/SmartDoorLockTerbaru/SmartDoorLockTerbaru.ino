#include <LiquidCrystal_PCF8574.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <Servo.h> 

#define led 11
#define buzzer 12
Servo myservo;

LiquidCrystal_PCF8574 lcd(0x27);
char password[4];
char pass[4],pass1[4];
int i=0;
char customKey=0;
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() 
  {
  myservo.attach(10);
  myservo.write(0);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  lcd.begin(16, 2);
  lcd.display();
  lcd.setBacklight(255);
  lcd.setCursor(0,0);
  lcd.print("  Robonesia  ");
  lcd.setCursor(0,1);
  lcd.print("  Keypad Lock ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Masukan Password:");
  lcd.setCursor(0,1);
  for(int j=0;j<4;j++)
  EEPROM.write(j, j+49);
  for(int j=0;j<4;j++)
  pass[j]=EEPROM.read(j);
}
  
void loop()
{ 
  customKey = customKeypad.getKey();
  if(customKey=='#')
  change();
  if (customKey)
  {
     password[i++]=customKey;
     lcd.print(customKey);
     beep();
  }
  if(i==4)
  {
    delay(200);
    for(int j=0;j<4;j++)
    pass[j]=EEPROM.read(j);
    if(!(strncmp(password, pass,4)))
    {
      digitalWrite(led, HIGH);
      myservo.write(90);
      beep();
      lcd.clear();
      lcd.print("Pass Diterima");
      delay(3000);
      lcd.setCursor(0,1);
      lcd.print("#.Ganti Password");
      delay(3000);
      lcd.clear();
      lcd.print("Masukan Password:");
      lcd.setCursor(0,1);
      i=0;
      myservo.write(0);
      digitalWrite(led, LOW);
    }
    
    else
    {
      digitalWrite(buzzer, HIGH);
      lcd.clear();
      lcd.print("Password Ditolak");
      lcd.setCursor(0,1);
      lcd.print("#.Ganti Password");
      delay(2000);
      lcd.clear();
      lcd.print("Masukan Password:");
      lcd.setCursor(0,1);
      i=0;
      digitalWrite(buzzer, LOW);
    }
  }
}
void change()
{
  int j=0;
  lcd.clear();
  lcd.print("Password Lama :");
  lcd.setCursor(0,1);
  while(j<4)
  {
    char key=customKeypad.getKey();
    if(key)
    {
      pass1[j++]=key;
      lcd.print(key);
      beep();
    }
    key=0;
  }
  delay(500);
  
  if((strncmp(pass1, pass, 4)))
  {
    lcd.clear();
    lcd.print("Password Salah");
    lcd.setCursor(0,1);
    lcd.print("Coba Lagi");
    delay(1000);
  }
  else
  {
    j=0;
    
  lcd.clear();
  lcd.print("Password Baru :");
  lcd.setCursor(0,1);
  while(j<4)
  {
    char key=customKeypad.getKey();
    if(key)
    {
      pass[j]=key;
      lcd.print(key);
      EEPROM.write(j,key);
      j++;
      beep();
    }
  }
  lcd.print("  Done......");
  delay(1000);
  }
  lcd.clear();
  lcd.print("Masukan Password:");
  lcd.setCursor(0,1);
  customKey=0;
}
void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
}