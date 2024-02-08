//Blynk
#define BLYNK_TEMPLATE_ID "TMPL6oVDAkbzT"
#define BLYNK_TEMPLATE_NAME "skripsi"
#define BLYNK_AUTH_TOKEN "-dX_vTSOC120AgLgulPcw-BrLuGJWebK"
#define BLYNK_PRINT Serial

//WiFi Blynk ESP32
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//pin-pin
#define Vc 5
#define ledH 18
#define ledM 19
#define srn 21

//gas CO
#define Rl_mq7 10000
#define r0_mq7 70
#define pin_mq7 34
#define a_mq7 95.002
#define b_mq7 -1.524

//gas CO2
#define Rl_mq135 20000
#define r0_mq135 38000
#define pin_mq135 35
#define a_mq135 113.12
#define b_mq135 -2.886

//gas CH4
#define Rl_mq5 20000
#define r0_mq5 6500
#define pin_mq5 32
#define a_mq5 180.94
#define b_mq5 -2.554


// Wifi Password
char ssid[] = "Amadeo Spesial Ramadhan";
char pass[] = "billyy123";
//LCD Blynk
WidgetLCD lcd(V3);

void getppm() {
  //ppm co
  float adc_mq7 = analogRead(pin_mq7);
  double rs_mq7 = ((4095.0*Rl_mq7)/adc_mq7)-Rl_mq7;
  float ppm_co = a_mq7*pow((float)rs_mq7/(float)r0_mq7,b_mq7);
  //ppm co2
  float adc_mq135 = analogRead(pin_mq135);
  double rs_mq135 = ((4095.0*Rl_mq135)/adc_mq135)-Rl_mq135;
  float ppm_co2 = a_mq135*pow((float)rs_mq135/(float)r0_mq135,b_mq135);
  //ppm ch4
  float adc_mq5 = analogRead(pin_mq5);
  double rs_mq5 = ((4095.0*Rl_mq5)/adc_mq5)-Rl_mq5;
  float ppm_ch4 = a_mq5*pow((float)rs_mq5/(float)r0_mq5,b_mq5);

  Blynk.virtualWrite(V0, ppm_co);
  Blynk.virtualWrite(V1, ppm_co2);
  Blynk.virtualWrite(V2, ppm_ch4);
  Serial.print("CO: ");
  Serial.print(ppm_co);
  Serial.println(" ppm");
  Serial.print("CO2: ");
  Serial.print(ppm_co2);
  Serial.println(" ppm");
  Serial.print("CH4: ");
  Serial.print(ppm_ch4);
  Serial.println(" ppm");

  if (ppm_co < 35 && ppm_co2 < 500 && ppm_ch4 < 200) {
    digitalWrite(ledH, HIGH);
    digitalWrite(ledM, LOW);
    digitalWrite(srn, LOW);
    Serial.println("AMAN");
    lcd.clear();
    lcd.print(0,0, "Kondisi gas: ");
    lcd.print(0,1, "AMAN");
  }
  else {
    digitalWrite(ledM, HIGH);
    digitalWrite(ledH, LOW);
    digitalWrite(srn, HIGH);
    Serial.println("BAHAYA");
    lcd.clear();
    lcd.print(0,0, "Kondisi gas: ");
    lcd.print(0,1, "BAHAYA");
    delay(3000);
  }
  delay(1000);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(pin_mq7, INPUT);
  pinMode(pin_mq135, INPUT);
  pinMode(pin_mq5, INPUT);
  pinMode(ledH, OUTPUT);
  pinMode(ledM, OUTPUT);
  pinMode(srn, OUTPUT);

  //start
  lcd.clear();
  lcd.print(0,0, "Welcome !!!");
  lcd.print(0,1, "Monitoring Gas, start!");
  delay(2000);
}

void loop() {
  Blynk.run();
  getppm();
}
