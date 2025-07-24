#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6j826IYzP"
#define BLYNK_TEMPLATE_NAME "SGH V2"
#define BLYNK_AUTH_TOKEN "bdeeUV6LTo51MO62SntdPycBlGo5E8NT"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// Konfigurasi DHT
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin konfigurasi
#define RELAY1 25
#define RELAY2 26
#define SOIL_SENSOR 34

// Variabel
bool relayState = false;

// Inisialisasi Blynk virtual pin
#define VPIN_RELAY1 V0
#define VPIN_RELAY2 V1
#define VPIN_TEMPERATURE V2
#define VPIN_HUMIDITY V3
#define VPIN_SOIL_MOISTURE V4

// Konfigurasi Wi-Fi
char ssid[] = "Phoenix";      // Masukkan nama Wi-Fi Anda
char pass[] = "harya010";  // Masukkan password Wi-Fi Anda


void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selamat Datang");
  lcd.setCursor(0, 1);
  lcd.print("Robogenz");
  // Inisialisasi Wi-Fi dan Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Inisialisasi pin
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);

  // Inisialisasi sensor
  dht.begin();

  Serial.println("Sistem IoT berbasis Blynk siap!");
}

void loop() {
  Blynk.run();

  // Membaca suhu dan kelembaban
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();

  if (!isnan(suhu) && !isnan(kelembaban)) {
    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print(" °C, Kelembaban: ");
    Serial.print(kelembaban);
    Serial.println(" %");

    // Kirim data ke Blynk
    Blynk.virtualWrite(VPIN_TEMPERATURE, suhu);
    Blynk.virtualWrite(VPIN_HUMIDITY, kelembaban);
  } else {
    Serial.println("Gagal membaca data dari sensor DHT!");
  }

  // Membaca kelembaban tanah
  int soilMoisture = analogRead(SOIL_SENSOR);
  soilMoisture = map(soilMoisture, 0, 4095, 0, 100);
  soilMoisture = (soilMoisture - 100)* -1;
  Serial.print("Kelembaban Tanah: ");
  Serial.println(soilMoisture);
  Serial.println("%");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(suhu);
  lcd.print(" C ");
  lcd.setCursor(0, 1);
  lcd.print("K.Tanah: ");
  lcd.print(soilMoisture);
  lcd.print(" %");

  // Kirim data kelembaban tanah ke Blynk
  Blynk.virtualWrite(VPIN_SOIL_MOISTURE, soilMoisture);

  delay(1000);
}

// Kontrol relay 1 dari Blynk
BLYNK_WRITE(VPIN_RELAY1) {
  int pinValue = param.asInt();  // Membaca nilai dari Blynk
  digitalWrite(RELAY1, pinValue);
}

// Kontrol relay 2 dari Blynk
BLYNK_WRITE(VPIN_RELAY2) {
  int pinValue = param.asInt();  // Membaca nilai dari Blynk
  digitalWrite(RELAY2, pinValue);
}
