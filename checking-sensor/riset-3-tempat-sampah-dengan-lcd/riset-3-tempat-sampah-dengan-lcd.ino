#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <Servo.h>

#define TRASH_BIN_1_TRIGGER_PIN 2
#define TRASH_BIN_1_ECHO_PIN 3
#define TRASH_BIN_2_TRIGGER_PIN 4
#define TRASH_BIN_2_ECHO_PIN 5
#define TRASH_BIN_3_TRIGGER_PIN 6
#define TRASH_BIN_3_ECHO_PIN 7

#define SERVO_PIN_1 8
#define SERVO_PIN_2 9
#define SERVO_PIN_3 10

#define LCD_ADDRESS 0x27
#define LCD_ROWS 2
#define LCD_COLUMNS 16

LiquidCrystal_PCF8574 lcd(LCD_ADDRESS); // Inisialisasi objek LCD
Servo servo1, servo2, servo3; // Inisialisasi objek servo

void setup() {
  pinMode(TRASH_BIN_1_TRIGGER_PIN, OUTPUT);
  pinMode(TRASH_BIN_1_ECHO_PIN, INPUT);
  pinMode(TRASH_BIN_2_TRIGGER_PIN, OUTPUT);
  pinMode(TRASH_BIN_2_ECHO_PIN, INPUT);
  pinMode(TRASH_BIN_3_TRIGGER_PIN, OUTPUT);
  pinMode(TRASH_BIN_3_ECHO_PIN, INPUT);
  
  lcd.begin(LCD_COLUMNS, LCD_ROWS); // Inisialisasi LCD
  lcd.setBacklight(255); // Nyalakan backlight LCD
  
  servo1.attach(SERVO_PIN_1); // Attach servo motor to pin
  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);

  // Menampilkan pesan stand-by pada LCD
  lcd.setCursor(0, 0);
  lcd.print("Tempat Sampah   ");
  lcd.setCursor(0, 1);
  lcd.print("    Pintar       ");
}

void loop() {
  if (digitalRead(TRASH_BIN_1_TRIGGER_PIN) == HIGH) {
    openTrashBin(1); // Buka tempat sampah 1
    lcd.setCursor(0, 0);
    lcd.print("Organik         "); // Tampilkan jenis sampah di LCD
    delay(2000); // Tunda beberapa saat
    closeTrashBin(1); // Tutup tempat sampah 1
  }

  if (digitalRead(TRASH_BIN_2_TRIGGER_PIN) == HIGH) {
    openTrashBin(2); // Buka tempat sampah 2
    lcd.setCursor(0, 0);
    lcd.print("Plastik         "); // Tampilkan jenis sampah di LCD
    delay(2000); // Tunda beberapa saat
    closeTrashBin(2); // Tutup tempat sampah 2
  }

  if (digitalRead(TRASH_BIN_3_TRIGGER_PIN) == HIGH) {
    openTrashBin(3); // Buka tempat sampah 3
    lcd.setCursor(0, 0);
    lcd.print("Kertas          "); // Tampilkan jenis sampah di LCD
    delay(2000); // Tunda beberapa saat
    closeTrashBin(3); // Tutup tempat sampah 3
  }
}

void openTrashBin(int binNumber) {
  if (binNumber == 1) {
    servo1.write(45); // Buka tempat sampah 1 sebesar 45 derajat
    delay(3000); // Tunggu selama 3 detik
  } else if (binNumber == 2) {
    servo2.write(45); // Buka tempat sampah 2 sebesar 45 derajat
    delay(3000); // Tunggu selama 3 detik
  } else if (binNumber == 3) {
    servo3.write(45); // Buka tempat sampah 3 sebesar 45 derajat
    delay(3000); // Tunggu selama 3 detik
  }
  lcd.clear(); // Bersihkan tampilan LCD
  lcd.setCursor(0, 1);
  lcd.print("Terima kasih    "); // Tampilkan pesan "Terima kasih" di LCD
  delay(2000); // Tunggu selama 2 detik sebelum menampilkan stand-by
  lcd.clear(); // Bersihkan tampilan LCD
  lcd.setCursor(0, 0);
  lcd.print("Tempat Sampah   ");
  lcd.setCursor(0, 1);
  lcd.print("    Pintar       ");
}

void closeTrashBin(int binNumber) {
  if (binNumber == 1) {
    servo1.write(90); // Tutup tempat sampah 1
    delay(1000); // Tunggu untuk menutup
  } else if (binNumber == 2) {
    servo2.write(90); // Tutup tempat sampah 2
    delay(1000); // Tunggu untuk menutup
  } else if (binNumber == 3) {
    servo3.write(90); // Tutup tempat sampah 3
    delay(1000); // Tunggu untuk menutup
  }
}
