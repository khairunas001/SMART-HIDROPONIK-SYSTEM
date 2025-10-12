/*
  Pembaca pH sederhana untuk modul PH-4502C (ESP32)
  - Hubungkan OUT modul PH-4502C ke pin ADC1 ESP32 (mis: GPIO34)
  - GND ke GND, VCC ke 3.3V
  - Buka Serial Monitor @115200 untuk melihat hasil pH

  Cara kalibrasi cepat:
  1) Celupkan probe ke larutan buffer pH 7, tunggu stabil.
  2) Jika layar belum ~7.00, ubah nilai phOffset di bawah
     (misal: jika terbaca 6.80, set phOffset = 0.20).
*/

#define PIN_PH   34       // OUT modul pH ke GPIO34 (ADC1)
const float PH_NEUTRAL_V = 2.50; // Tegangan ~netral pH7 (asumsi umum)
const float PH_SLOPE  = 3.50;   // Kemiringan: pH = 7 + (2.5 - V)*3.5 (sederhana)
float phOffset        = 0.00;   // Koreksi kalibrasi sederhana (geser hasil pH)

// Baca beberapa kali lalu rata-rata untuk mengurangi noise
float readVoltageAverage(uint8_t pin, uint16_t samples = 10) {
  uint32_t sum = 0;
  for (uint16_t i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delay(2); // jeda kecil
  }
  float adcAvg = (float)sum / samples;
  return (adcAvg / ADC_RES) * VREF; // konversi ke Volt
}

void setup_ph_meter() {

  pinMode(PIN_PH, INPUT);
  analogReadResolution(12);                         // pastikan 12-bit
  analogSetPinAttenuation((gpio_num_t)PIN_PH, ADC_11db); // rentang ~0..3.3V

  Serial.println("Pembaca pH PH-4502C (sederhana) siap...");
  Serial.println("Tips kalibrasi: celup ke buffer pH 7 lalu atur phOffset agar terbaca ~7.00");
}

void update_sensor_ph() {
  // 1) Baca tegangan rata-rata dari sensor
  float volt = readVoltageAverage(PIN_PH, 10);

  // 2) Hitung pH dengan rumus sederhana
  //    pH ≈ 7 + (2.5 - V)*3.5  (+ offset kalibrasi)
  float pH = 7.0 + (PH_NEUTRAL_V - volt) * PH_SLOPE + phOffset;

  // 3) Batasi ke 0..14 agar tidak “aneh” saat noise besar
  if (pH < 0)  pH = 0;
  if (pH > 14) pH = 14;

  nilai_ph = pH;

  // 4) Tampilkan
  // Serial.print("V=");
  // Serial.print(volt, 3);
  // Serial.print(" V | pH=");
  // Serial.println(pH, 2);

  // delay(1000); // update tiap 1 detik (sederhana)
}


