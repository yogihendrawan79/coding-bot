#define SENSOR_PIN A1 // Contoh pin yang digunakan untuk sensor infrared
#define THRESHOLD 500 // Ambang batas untuk membedakan gelap dan terang

void setup() {
  Serial.begin(9600); // Mulai komunikasi serial untuk debug
  pinMode(SENSOR_PIN, INPUT); // Set sensor pin sebagai input
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN); // Baca nilai sensor

  // Debug: Tampilkan nilai sensor pada monitor serial
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // Tentukan apakah cahaya yang terdeteksi dianggap gelap atau terang
  if (sensorValue < THRESHOLD) {
    Serial.println("Gelap");
    // Tindakan jika cahaya gelap
  } else {
    Serial.println("Terang");
    // Tindakan jika cahaya terang
  }

  delay(1000); // Tunggu sebentar sebelum membaca sensor lagi
}
