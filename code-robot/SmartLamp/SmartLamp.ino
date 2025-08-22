//Codingan Arduino - Smart Lamp (Clapping Lamp)
//Robonesia - Latih Hobi

const int relay = 8;
const int sensor = 2;
boolean relayAktif = false;
int keadaansebelumnya = LOW;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(sensor, INPUT);
}

void loop() {
  int keadaansekarang = digitalRead(sensor);
  if ((keadaansekarang == HIGH) and (keadaansekarang != keadaansebelumnya)) {
    //  Membalik keadaan relay aktif
    relayAktif = not relayAktif;

    //Atur relay berdasarkan nilai relayAktif

    if (relayAktif) {
      digitalWrite(relay, HIGH);
      delay(100);  //tunda sesaat
    } else {
      digitalWrite(relay, LOW);
      delay(100);  //tunda sesaat
    }
  }
  //perbaharui keadaan sebelumnya
  keadaansebelumnya = keadaansekarang;
}
