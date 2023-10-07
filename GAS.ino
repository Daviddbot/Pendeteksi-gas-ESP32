#include <Wire.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

char ssid[] = "Why";
char pass[] = "150713222014";

// Token Blynk Anda

char auth[] = "4mbZAn1c5XG6zai_LCpRe2swNctgo5vZ";


LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD I2C dengan alamat 0x27, 16 kolom, 2 baris
const int Sensor_input = 34; /* Digital pin 4 untuk input sensor */

void setup() {
  Serial.begin(115200); /* Baud rate untuk komunikasi serial */

  // Inisialisasi WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Inisialisasi Blynk
  Blynk.begin(auth, ssid, pass);

  
  pinMode(Sensor_input, INPUT); /* Input sensor */
  pinMode(19,OUTPUT);
  lcd.init(); /* Inisialisasi LCD */
  lcd.backlight(); /* Nyalakan backlight LCD */
  lcd.setCursor(0, 0); /*mengatur cursor dari lcd 16x02*/
  lcd.print("Gas Sensor:");
}

void loop() {
    Blynk.run();
    
  int sensor_Aout = analogRead(Sensor_input); /* Baca nilai analog dari sensor */
  int mappedValue = map(sensor_Aout, 0, 4095, 0, 1023);  /*mapping data */
  Serial.print("Gas Sensor: "); /*menampilkan tulisan gas sensor di serial monitor*/
  Serial.print(mappedValue ); /* Tampilkan nilai yang dibaca */
  Serial.print("\t");
  Serial.print("\t");

  lcd.setCursor(0, 1);
  lcd.print("                "); /* Hapus baris kedua */
  lcd.setCursor(0, 1);
  lcd.print("Sensor MQ2: ");
  lcd.print(mappedValue ); /* Tampilkan nilai sensor MQ2 */

  Blynk.virtualWrite(V1, mappedValue );
  
  if (mappedValue  > 700) { /* Kondisi jika nilai sensor di atas 1800 */
    Serial.println("Gas");
    lcd.setCursor(0, 0);
    lcd.print("Gas Detected");
    digitalWrite(19, HIGH); /* Nyalakan LED jika mendeteksi gas */
  } else {
    Serial.println("No Gas");
    lcd.setCursor(0, 0);
    lcd.print("No Gas Detected");
    digitalWrite(19, LOW); /* Matikan LED jika tidak mendeteksi gas */
  }
  delay(1000); /* Delay 1 detik */
}
