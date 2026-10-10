// ==========================================
// KONFIGURASI PIN SENSOR ULTRASONIK
// ==========================================
int Echo1 = 6; // Sensor Kiri echo
int Trig1 = 7; // Sensor Kiri trig
int Echo2 = 5; // Sensor Tengah/Depan echo
int Trig2 = 4; // Sensor Tengah/Depan trig
int Echo3 = 2; // Sensor Kanan echo
int Trig3 = 8; // Sensor Kanan trig

// ==========================================
// KONFIGURASI PIN DRIVER MOTOR L298N
// ==========================================
int in1 = 9;   // Motor Kiri
int in2 = 10;  // Motor Kiri
int in3 = 12;  // Motor Kanan
int in4 = 13;  // Motor Kanan
int ENA = 3;   // Pin PWM Motor Kiri
int ENB = 11;  // Pin PWM Motor Kanan


const int batas = 15; // Jarak batas halangan (cm)

// Variabel penampung jarak
int Left_Distance = 0;
int Middle_Distance = 0;
int Right_Distance = 0;

void setup() {
  // Inisialisasi Pin Sensor
  pinMode(Trig1, OUTPUT); pinMode(Echo1, INPUT);
  pinMode(Trig2, OUTPUT); pinMode(Echo2, INPUT);
  pinMode(Trig3, OUTPUT); pinMode(Echo3, INPUT);

  // Inisialisasi Pin Motor
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

// Fungsi pembacaan jarak ultrasonik
int bacaJarak(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long durasi = pulseIn(echo, HIGH, 30000);
  if (durasi == 0) return 999;
  return durasi * 0.034 / 2;
}

// ==========================================
// FUNGSI GERAK MOTOR (DENGAN KONTROL PWM)
// ==========================================
void maju() {
  analogWrite(ENA, 155);
  analogWrite(ENB,100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void mundur() {
  analogWrite(ENA, 155);
  analogWrite(ENB, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void kanan() {
  analogWrite(ENA, 155);
  analogWrite(ENB, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void kiri() {
  analogWrite(ENA, 155);
  analogWrite(ENB, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void berhenti() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// ==========================================
// LOOP UTAMA PROGRAM
// ==========================================
void loop() {
  Left_Distance = bacaJarak(Trig1, Echo1);
  delay(10);
  Middle_Distance = bacaJarak(Trig2, Echo2);
  delay(10);
  Right_Distance = bacaJarak(Trig3, Echo3);

  // Ada halangan di semua sisi -> Berhenti
  if (Middle_Distance < batas && Left_Distance < batas && Right_Distance < batas) {
    berhenti();
  }
  // Ada halangan di depan & kanan -> Mundur lalu belok kiri
  else if (Middle_Distance < batas && Right_Distance < batas) {
    mundur(); delay(1000);
    kiri();   delay(1000);
  }
  // Ada halangan di depan & kiri -> Mundur lalu belok kanan
  else if (Middle_Distance < batas && Left_Distance < batas) {
    mundur(); delay(1000);
    kanan();  delay(1000);
  }
  // Ada halangan di depan -> Mundur lalu belok kanan
  else if (Middle_Distance < batas) {
    mundur(); delay(1000);
    kanan();  delay(1000);
  }
  // Ada halangan di kiri saja -> Belok kanan
  else if (Left_Distance < batas) {
    kanan();
  }
  // Ada halangan di kanan saja -> Belok kiri
  else if (Right_Distance < batas) {
    kiri();
  }
  // Jalanan bebas -> Maju
  else {
    maju();
  }
}
