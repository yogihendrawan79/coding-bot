#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);

#include "DHT.h"       //library sensor yang telah diimportkan
#define DHTPIN 3       //Pin apa yang digunakan
#define DHTTYPE DHT11  // DHT 11
float Fan = 2;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);  // komunikasi lcd
  dht.begin();       //prosedur memulai pembacaan module sensor
  pinMode(Fan, OUTPUT);
}

void loop() {
  lcd.setBacklight(255);
  delay(2000);  //menunggu beberapa detik untuk pembacaan

  //pembacaan sensor membutuhkan waktu 250ms

  //Pembacaan untuk data kelembaban
  float humidity_1 = dht.readHumidity();
  //Pembacaan dalam format celcius (c)
  float celcius_1 = dht.readTemperature();

  //mengecek pembacaan apakah terjadi kegagalan atau tidak
  if (isnan(humidity_1) || isnan(celcius_1)) {
    digitalWrite(Fan, HIGH);
    lcd.println("Pembacaan data dari module sensor gagal!");
    return;
  }
  if (celcius_1 >= 28)
  {
    digitalWrite(Fan, HIGH);
  }
  else
  {
    digitalWrite(Fan, LOW);
  }
  //pembacaan nilai pembacaan data kelembaban
  lcd.setCursor(0, 0);
  lcd.print("Kelembaban: ");
  lcd.print(humidity_1);
  lcd.print(" %\t");

  //pembacaan nilai pembacaan data suhu
  lcd.setCursor(0, 1);
  lcd.print("Suhu : ");
  lcd.print(celcius_1);  //format derajat celcius
  lcd.print("°");        //simbol derajat
  lcd.println("C  ");
}
