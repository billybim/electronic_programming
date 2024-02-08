/*
 * Kelompok 6
 * Projek Biofarmaka
 * Rumah Atsiri Indonesia
 * Adi Franata Jaya, Andin Sukma, Anisya Anjarwati, Febriana K, Billy C
 * ALAT HOMOGENITAS LULUR OTOMATIS BERBASIS SENSOR SOIL MOISTURE 
 */

// Inisiasi Variabel
int det1 = A0;
int det2 = A1;
int relai = 3;
int buzz = 7;
 
// Variabel sensor
int bacaData1;
int bacaData2;

void setup() {
  pinMode(det1, INPUT);
  pinMode(det2, INPUT);
  pinMode(relai, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  Serial.println("Kelembaban terdeteksi...");  
}

void loop() {
  bacaData1 = analogRead(det1);
  bacaData2 = analogRead(det2);
  int moisture1 = map(bacaData1,1023,0,0,100);
  int moisture2 = map(bacaData2,1023,0,0,100);
  Serial.print("Nilai kelembaban detektor 1: ");
  Serial.println(moisture1);
  Serial.print("Nilai kelembaban detektor 2: ");
  Serial.println(moisture2);

  if (moisture1 != moisture2 && abs(moisture1-moisture2)>2) {
    digitalWrite(relai, HIGH);
    digitalWrite(buzz, LOW);
    Serial.println("Mixer berputar");
  }
  else {
    digitalWrite(relai, LOW);
    digitalWrite(buzz, HIGH);
    Serial.println("Campuran sudah homogen");
  }
  delay(5000);
}
