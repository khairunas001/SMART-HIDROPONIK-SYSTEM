/*
  =========================================================
   Modul : Sensor Suhu Air (DS18B20)
   Author: shmukti

   Deskripsi:
     - Modul ini digunakan untuk membaca suhu air menggunakan 
       sensor DS18B20 yang terhubung melalui protokol OneWire.
     - Library yang digunakan:
         * OneWire.h
         * DallasTemperature.h
     - Nilai suhu disimpan ke variabel global nilai_suhu_air.

   Konfigurasi:
     - PIN_DS18B20 = GPIO 32
     - Sensor DS18B20 dapat dipasang lebih dari satu pada bus OneWire,
       tetapi kode ini hanya membaca sensor pertama (index 0).

   Fungsi:
     1. setup_ds18b20()
        - Dipanggil sekali pada setup().
        - Inisialisasi komunikasi dengan sensor DS18B20.
        - Menampilkan pesan "Test DS18B20 mulai..." di Serial Monitor.

     2. update_sensor_suhu_air()
        - Dipanggil di loop utama untuk update nilai suhu.
        - Langkah kerja:
            * Kirim request ke DS18B20 agar mengukur suhu terbaru.
            * Ambil hasil pembacaan dalam Celcius dari sensor index ke-0.
            * Jika sensor tidak terdeteksi (DEVICE_DISCONNECTED_C),
              set nilai_suhu_air = 0.
            * Jika valid, set nilai_suhu_air = suhuC.
        - Hasil dapat digunakan untuk telemetry MQTT atau log.

   Catatan:
     - DS18B20 butuh resistor pull-up 4.7kΩ antara pin data dan VCC.
     - Bisa dipasang multiple sensor dalam satu pin, 
       namun perlu identifikasi alamat sensor untuk pembacaan spesifik.
     - Nilai default 0 menandakan sensor tidak terbaca / error.

   Tujuan:
     - Menyediakan pembacaan suhu air yang stabil untuk sistem hidroponik,
       aquarium, atau monitoring lingkungan berbasis ESP32.

  =========================================================
*/

#include <OneWire.h>
#include <DallasTemperature.h>

// Konfigurasi pin
#define PIN_DS18B20 32

// Setup OneWire dan DallasTemperature
OneWire oneWire(PIN_DS18B20);
DallasTemperature ds18b20(&oneWire);

void setup_ds18b20() {
  Serial.println("Test DS18B20 mulai...");
  ds18b20.begin();  // inisialisasi sensor
}

void update_sensor_suhu_air() {
  ds18b20.requestTemperatures();             // minta sensor update data
  float suhuC = ds18b20.getTempCByIndex(0);  // ambil suhu sensor pertama
  if (suhuC == DEVICE_DISCONNECTED_C) {
    nilai_suhu_air = 0;
  } else {
    nilai_suhu_air = suhuC;
  }
}