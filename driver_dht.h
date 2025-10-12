/*
  =========================================================
   Modul : Sensor Suhu & Kelembaban (DHT11)
   Author: shmukti

   Deskripsi:
     - Modul ini digunakan untuk membaca suhu (°C) dan 
       kelembaban relatif (%) dari sensor DHT11.
     - Library yang digunakan:
         * DHT.h  (Adafruit DHT sensor library)

   Konfigurasi:
     - PIN_DHT  = GPIO 25 (data pin sensor ke ESP32)
     - DHTTYPE  = DHT11  (bisa diganti DHT22 jika pakai DHT22)
     - Timer    = Every timer_update_dht(500) 
                  → update sensor setiap 500 ms (0.5 detik)

   Fungsi:
     1. setup_dht()
        - Dipanggil sekali di setup().
        - Menginisialisasi sensor DHT11.
        - Menampilkan status "DHT11 siap digunakan.." 
          di Serial Monitor.

     2. update_sensor_dht()
        - Dipanggil di loop utama.
        - Mengecek apakah timer_update_dht sudah jatuh tempo.
        - Jika ya:
            * Membaca nilai kelembaban (%RH) → simpan ke variabel global nilai_kelembaban_udara.
            * Membaca suhu (°C) → simpan ke variabel global nilai_suhu_udara.

   Catatan:
     - DHT11 memiliki resolusi rendah (±5% RH, ±2 °C) 
       dan interval sampling minimal ~1 detik.
       (Jika butuh lebih cepat & akurat gunakan DHT22/SHT31).
     - Fungsi readHumidity() dan readTemperature() 
       dapat mengembalikan NAN jika pembacaan gagal.
     - Disarankan menambahkan pengecekan `isnan()` untuk 
       menghindari nilai error masuk ke sistem.
     - Timer non-blocking (Every) memastikan pembacaan periodik 
       tanpa mengganggu loop utama.

   Tujuan:
     - Menyediakan data suhu & kelembaban udara 
       untuk sistem monitoring/telemetri berbasis ESP32.

  =========================================================
*/

#include "DHT.h"

//koneksi pin DHT 11 ke pin esp32 pin D25
#define PIN_DHT 25

#define DHTTYPE DHT11  // DHT 11
DHT dht(PIN_DHT, DHTTYPE);

Every timer_update_dht(500);

void setup_dht() {
  dht.begin();  //inisialisasi sensor DHT11
  Serial.println("DHT11 siap digunakan..");
}

void update_sensor_dht() {
  if (timer_update_dht()) {

    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();


    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
    }else{
      nilai_kelembaban_udara = h;
      nilai_suhu_udara = t;
    }
  }
}
