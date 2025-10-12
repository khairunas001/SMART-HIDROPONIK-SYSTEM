/*
  =========================================================
   Modul : Sensor TDS Meter (ADC ESP32)
   Author: shmukti

   Deskripsi:
     - Mengukur TDS (Total Dissolved Solids) air dalam ppm menggunakan
       modul TDS (mis. Gravity TDS) yang keluarannya analog → dibaca ADC ESP32.
     - Perhitungan: ADC → Tegangan → EC (mS/cm) → kompensasi suhu → TDS (ppm).
     - Update pembacaan dilakukan periodik via timer_tds(1000 ms).

   Konstanta & Konfigurasi:
     - PIN_TDS   = GPIO 34 (ADC1)  → input analog dari modul TDS
     - VREF      = 3.3 V           → referensi tegangan ADC
     - ADC_RES   = 4095 (12-bit)   → skala ADC 0..4095
     - TDS_FACTOR= 0.5             → faktor konversi EC→TDS (umum 0.5; 0.64/0.7 untuk standar lain)
     - TEMP_C    = 25.0 °C         → suhu kompensasi (disarankan pakai DS18B20 aktual)
     - analogSetPinAttenuation(PIN_TDS, ADC_11db) → rentang input hingga ~3.3 V

   Fungsi:
     1) setup_tds_meter()
        - Set resolusi ADC ke 12-bit dan attenuation 11 dB untuk memperlebar range tegangan.
        - Menampilkan status inisialisasi di Serial.

     2) bacaADC_Average(pin, nSample)
        - Membaca ADC beberapa kali (default 30x) dan menghitung rata-rata
          untuk mengurangi noise.

     3) update_sensor_tds()
        - Dipanggil periodik (timer_tds()).
        - Langkah:
            a. Baca ADC rata-rata → adcRaw.
            b. Konversi ke tegangan: voltage = (adcRaw/ADC_RES)*VREF.
            c. Estimasi EC (mS/cm) dengan polinomial empiris (contoh modul Gravity):
               ec = (133.42*V^3 - 255.86*V^2 + 857.39*V)/1000
            d. Kompensasi suhu ke 25°C:
               ec25 = ec / (1 + 0.02*(TEMP_C - 25))
            e. Konversi EC→TDS:
               tds = ec25 * TDS_FACTOR * 1000  (ppm)
            f. Simpan ke variabel global: nilai_tds.

   Catatan Penting:
     - Range praktis sensor TDS untuk hidroponik: 0–2000 ppm.
     - Gunakan suhu air aktual (DS18B20) untuk akurasi (ganti TEMP_C).
     - Polinomial EC di atas adalah pendekatan umum; setiap modul/probe
       bisa butuh kalibrasi ulang (single/two-point):
         * Siapkan larutan standar EC (mis. 1.413 mS/cm).
         * Baca tegangan → sesuaikan koefisien/faktor agar bacaan cocok.
     - Gunakan pin ADC1 (GPIO32–39) karena ADC2 berbagi dengan WiFi.
     - Jaga kebersihan probe; bilas dengan air deionisasi setelah pemakaian.
     - Filtering tambahan (median/moving average) bisa ditambahkan untuk stabilitas.

   Tujuan:
     - Menyediakan pembacaan TDS yang stabil & terkompensasi suhu,
       siap dipakai untuk kontrol nutrisi dan telemetry MQTT.
  =========================================================
*/


// ====== TDS Meter Test (ESP32) ======
#define PIN_TDS 34       // AOUT TDS → GPIO34 (ADC1)
#define VREF 3.3f        // Tegangan referensi ADC (volt)
#define ADC_RES 4095.0f  // Resolusi 12-bit ESP32
#define TDS_FACTOR 0.5f  // Konversi EC→TDS (umum: 0.5)
#define TEMP_C 25.0f     // Suhu air (°C). Ganti dengan pembacaan DS18B20 bila ada.

Every timer_tds(1000);

void setup_tds_meter() {
  analogReadResolution(12);                    // Pastikan 12-bit
  analogSetPinAttenuation(PIN_TDS, ADC_11db);  // Perlebar range (≈ hingga 3.3V)
  Serial.println("TDS Meter Test - Start");
}

float bacaADC_Average(uint8_t pin, uint16_t nSample = 30) {
  uint32_t sum = 0;
  for (uint16_t i = 0; i < nSample; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return (float)sum / nSample;
}

void update_sensor_tds() {

  if (timer_tds()) {
    // 1) Baca ADC & rata-rata
    float adcRaw = bacaADC_Average(PIN_TDS);

    // 2) Konversi ke tegangan
    float voltage = (adcRaw / ADC_RES) * VREF;  // Volt

    // 3) Estimasi EC (mS/cm) dari tegangan (rumus umum modul TDS Gravity)
    //    Catatan: Modul berbeda bisa perlu kalibrasi faktor a,b.
    //    Rumus polinomial empiris (contoh umum):
    float ec = (133.42f * voltage * voltage * voltage
                - 255.86f * voltage * voltage
                + 857.39f * voltage)
               / 1000.0f;  // mS/cm

    // 4) Kompensasi suhu (koefisien ~2% per °C dari 25°C)
    float ec25 = ec / (1.0f + 0.02f * (TEMP_C - 25.0f));  // mS/cm @25°C

    // 5) Konversi EC→TDS (ppm)
    float tds = ec25 * TDS_FACTOR * 1000.0f;  // ppm

    // 6) Tampilkan
    //Serial.print("ADC: "); Serial.print(adcRaw, 1);
    //Serial.print("  V: "); Serial.print(voltage, 3);
    //Serial.print(" V  EC25: "); Serial.print(ec25, 3);
    //Serial.print(" mS/cm  TDS: "); Serial.print(tds, 0);
    //Serial.println(" ppm");
    nilai_tds = tds;
  }
}
