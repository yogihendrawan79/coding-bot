//==========================================================================================
//
//  Robot digerakan dengan 2 motor gearbox
//  Dikendalikan dengan controller wireless stick ps 2
//  Mengunakan solenoid untuk menendang bola
//  Progam ini di buat oleh Misbah najh (SEKOLAH ROBOT) dan di Modifikasi oleh Robonesia.id
//
//==========================================================================================

///////////////////definisi library controller/////////////////////
#include <PS2X_lib.h>
#define PS2_DAT        A0
#define PS2_CMD        A1
#define PS2_SEL        A2
#define PS2_CLK        A3

#define pressures   true
//#define pressures   false
#define rumble      true
//#define rumble      false

PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

////////////////definisi library servo & shield motor/////////////////
#include <Servo.h>
#include <AFMotor.h>
#define B 2           //LED RGB define
#define G 9
#define R 10
#define buzzer A5     //buzzer define
#define tendang A4    //solenoid define
AF_DCMotor motor1(3); //motor shield define
AF_DCMotor motor2(2); //motor shield define
Servo servo;

void setup() {
  Serial.begin(57600);// bautrate menyesuaikan controller
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.println("controller ditemukan , konfigurasi robot soccer berhasil");
    Serial.println("Tekan tombol untuk memulai = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("tekan dan tahan tombol X, controller akan bergetar");
    Serial.println("tahan L1 atau R1 untuk melihat nilainya");
    Serial.println("selamat datang di cahnnel SEKOLAH ROBOT selamat belajar");
  }
  else if (error == 1)
    Serial.println("Maaf controller tidak ditemukan, cek kabel receiver mungkin terbalik atau putus");

  else if (error == 2)
    Serial.println("Controller ditemukan tetapi menolak perintah");

  else if (error == 3)
    Serial.println("controller menolak untuk dijalankan, mungkin tidak mendukungnya");

  //  Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Jenis Kontroler tidak dikenal ditemukan");
      break;
    case 1:
      Serial.println("DualShock Controller ditemukan");
      break;
    case 2:
      Serial.println("GuitarHero Controller ditemukan");
      break;
    case 3:
      Serial.println("Wireless Sony DualShock Controller ditemukan");
      break;
  }
  //////////////konfigurasi keluaran pin//////////
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(tendang, OUTPUT);
  lampu();
}



void loop() {
  if (error == 1) //tidak looping ketika kontroler ditemukan
    return;

  else {
    int x = 255; //ATUR KECEPTAN ROBOT 150-225
    int y = 255; //ATUR KECEPTAN BELOK ROBOT 150-225
    //tombol start untuk bell
    if (ps2x.Button(PSB_START)) {
      bel();
      Serial.println("Start");
    }
    if (ps2x.Button(PSB_SELECT))Serial.println("Select");
    ps2x.read_gamepad(false, vibrate);

    if (ps2x.Button(PSB_PAD_UP))    {
      maju(x);
    }
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      kanan(x);  //muter kanan
    }
    if (ps2x.Button(PSB_PAD_LEFT))  {
      kiri(x);   //muter kiri
    }
    if (ps2x.Button(PSB_PAD_DOWN))  {
      mundur(x);
    }

    if (ps2x.Analog(PSS_LY) < 100)    {
      maju(x);
    }
    if (ps2x.Analog(PSS_RX) < 25)     {
      mkiri(y);  //belok kekiri
    }
    if (ps2x.Analog (PSS_RX) > 200)   {
      mkanan(y); //belok kekanan
    }
    if (ps2x.Analog(PSS_LY) > 150)    {
      mundur(x);
      if (ps2x.Analog(PSS_RX) < 25)     {
        bkiri(y);  //mundur kekiri
      }
      if (ps2x.Analog (PSS_RX) > 200)   {
        bkanan(y); //mundur kekanan
      }
    }

    vibrate = ps2x.Analog(PSAB_CROSS);  //bergetar ketika X ditekan dan ditahan

    if (ps2x.NewButtonState()) {
      if (ps2x.Button(PSB_L1)) {
        sepak(); Serial.println("L1");
      } //menendang bola
      if (ps2x.Button(PSB_R1)) {
        sepak(); Serial.println("R1");
      } //menendang bola
    }
    if (ps2x.ButtonPressed(PSB_L2)) { // led hijau on
      Serial.println("L2"); digitalWrite(R, LOW); digitalWrite(G, HIGH); digitalWrite(B, LOW);
    }
    if (ps2x.ButtonPressed(PSB_R2)) { // led biru on
      Serial.println("R2"); digitalWrite(R, LOW); digitalWrite(G, LOW); digitalWrite(B, HIGH);
    }

    if (ps2x.ButtonPressed(PSB_TRIANGLE)) {
      shot1(x); Serial.println("Segitiga");
    } //tes segitiga
    if (ps2x.ButtonPressed(PSB_CIRCLE)) {
      dribelkanan(x); Serial.println("O");
    }   //tes lingkaran
    if (ps2x.ButtonPressed(PSB_SQUARE)) {
      dribelkiri(x); Serial.println("Kotak");
    }//tes kotak
    if (ps2x.NewButtonState(PSB_CROSS)) {
      Serial.println("X");
    }                  //tes X

    if (ps2x.Analog(PSS_LY) != 127 || ps2x.Analog(PSS_LX) != 128 || ps2x.Analog(PSS_RY) != 127 || ps2x.Analog(PSS_RX) != 128) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC);  //Nilai analog kiri LY
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC);  //Nilai analog kiri LX
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC);  //Nilai analog kanan RY
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC);//Nilai analaog kanan RX
    }
  }
  delay(50);   berhenti();
}

//========================CARA KALIBRASI ROBOT================================
//============================================================================
//1. PASTIKAN KETIKA ROBOT MAJU, MAKA ROBOT HARUS BERGERAK MAJU LURUS
//   (kurangi kecepatn roda kanan jika roda kanan terlalu cepat)
//2. PASTIKAN KETIKA ROBOT MUNDUR, MAKA ROBOT HARUS BERGERAK MUNDUR LURUS
//   (kurangi kecepatn roda kiri jika roda kiri terlalu cepat)
//3. LAKUKAN KALIBRASI LAINYA DENGAN MEMAHAMI DASAR POIN 1 & 2
//
//===========SELAMAT BELAJAR SEMOGA ROBOT BERJALAN DENGAN BAIK=================
//=================SEKOLAH ROBOT LEARNING FROM BEGINING========================


int spdkanan = 0; //kurangi kecepatn roda kanan
int spdkiri = 0; //kurangi kecepatn roda kiri

void maju(int x) {
  motor1.setSpeed(x - spdkanan); motor1.run(FORWARD); // KECEPATAN KEDUA MOTOR HARUS SAMA
  motor2.setSpeed(x - spdkiri); motor2.run(FORWARD); // KURANGI NILAI X AGAR KECEPATAN SAMA
  Serial.println("maju");
}
void mundur(int x) {
  motor1.setSpeed(x - spdkanan);   motor1.run(BACKWARD); // KECEPATAN KEDUA MOTOR HARUS SAMA
  motor2.setSpeed(x - spdkiri); motor2.run(BACKWARD); // KURANGI NILAI X AGAR KECEPATAN SAMA
  Serial.println("mundur");
}
void kanan(int y) {                             //muter kanan
  motor1.setSpeed(y - spdkanan);     motor1.run(RELEASE);
  motor2.setSpeed(225);  motor2.run(FORWARD);
  Serial.println("kiri");
}
void kiri(int y) {                              //muter kiri
  motor1.setSpeed(y - spdkanan);   motor1.run(FORWARD);
  motor2.setSpeed(y + 50 - spdkiri);     motor2.run(RELEASE);
  Serial.println("kanan");
}
void mkanan(int y) {                            //belok kanan
  motor1.setSpeed(y - spdkanan);     motor1.run(RELEASE);
  motor2.setSpeed(y - 35 - spdkiri);  motor2.run(FORWARD);
  Serial.println("mkanan");
}
void mkiri(int y) {                            //belok kiri
  motor1.setSpeed(y - 35 - spdkanan);   motor1.run(FORWARD);
  motor2.setSpeed(y - spdkiri);     motor2.run(RELEASE);
  Serial.println("mkiri");
}
void bkanan(int y) {                           //mundur kanan
  motor1.setSpeed(y - 35 - spdkanan);   motor1.run(BACKWARD);
  motor2.setSpeed(y - spdkiri);  motor2.run(RELEASE);
  Serial.println("bkanan");
}
void bkiri(int y) {                           //mundur kiri
  motor1.setSpeed(y - spdkanan);  motor1.run(RELEASE);
  motor2.setSpeed(y - 35 - spdkiri);  motor2.run(BACKWARD);
  Serial.println("bkiri");
}
void berhenti()
{
  motor1.setSpeed(0);
  motor2.run(RELEASE);
  motor2.setSpeed(0);
  motor2.run(RELEASE);
}
void bel() {
  digitalWrite(buzzer, HIGH);
  delay(50); digitalWrite(buzzer, LOW);
}
void sepak() {
  digitalWrite(tendang, HIGH);
  delay(100); digitalWrite(tendang, LOW);
}
void lampu() {         //Tes RGB
  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  delay(500);

  digitalWrite(B, HIGH);
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  delay(500);

  digitalWrite(G, HIGH);
  digitalWrite(R, LOW);
  digitalWrite(B, LOW);
  delay(500);
}

void shot1(int x) { //maju dan rem
  maju(x);
  delay(300);
  mundur(x);
  delay(50);
}
void dribelkanan(int x) { //menghindari lawan dari kanan
  kanan(x);
  delay(250); // kalibrasi kecepatan belok agar sesuai 90*
  maju(x);
  delay(500);
  kiri(x);
  delay(150); // kalibrasi kecepatan belok agar sesuai 90*
}
void dribelkiri(int x) { //menghindari lawan dari kiri
  kiri(x);
  delay(350); // kalibrasi kecepatan belok agar sesuai 90*
  maju(x);
  delay(500);
  kanan(x);
  delay(250); // kalibrasi kecepatan belok agar sesuai 90*
}
