#include <DHT.h>

#define DHTPIN 2     // Pin yang terhubung ke output sensor DHT11
#define DHTTYPE DHT11   // Tipe sensor DHT (DHT11, DHT22, DHT21)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 Test!");

  dht.begin();
}

void loop() {
  delay(2000);  // Delay untuk menghindari pembacaan yang terlalu cepat

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca dari sensor DHT");
    return;
  }

  Serial.print("Kelembapan: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println("°C");
}
