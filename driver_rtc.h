/*
  =========================================================
   Modul : RTC DS3231 (Real Time Clock)
   Author: shmukti

   Deskripsi:
     - Modul ini digunakan untuk menjaga waktu aktual 
       (jam, menit, detik, hari, tanggal, bulan, tahun) 
       secara independen dari ESP32.
     - RTC DS3231 terhubung melalui protokol I2C.

   Konfigurasi:
     - Library:
         * Wire.h    -> komunikasi I2C
         * RTClib.h  -> pengelolaan RTC DS3231/DS1307
     - Default pin I2C ESP32:
         * SDA = GPIO 21
         * SCL = GPIO 22
     - Objek RTC: RTC_DS3231 rtc;

   Fungsi:
     1. setup_rtc()
        - Dipanggil sekali di setup().
        - Memulai komunikasi I2C (Wire.begin()).
        - Mengecek apakah RTC DS3231 terdeteksi:
            * Jika tidak → tampilkan "RTC tidak terdeteksi, cek wiring!"
            * Jika berhasil → tampilkan "RTC DS3231 siap..."

   Catatan:
     - RTC DS3231 dilengkapi dengan baterai backup 
       (CR2032/CR1220) sehingga tetap menyimpan waktu 
       meskipun ESP32 mati.
     - Jika RTC baru pertama kali digunakan, waktu 
       perlu diset terlebih dahulu dengan fungsi rtc.adjust().
       Contoh:
         rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
       (akan set waktu sesuai compile time).
     - Fungsi pembacaan waktu:
         DateTime now = rtc.now();
         now.hour(), now.minute(), now.second()
         now.day(), now.month(), now.year()
         now.dayOfTheWeek()   // 0=Sunday ... 6=Saturday

   Tujuan:
     - Menyediakan waktu real-time untuk jadwal otomatis.
     - Digunakan pada sistem hidroponik untuk eksekusi pompa 
       berdasarkan jam/hari yang ditentukan.

  =========================================================
*/

#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup_rtc() {

  // Mulai komunikasi I2C (SDA = D21, SCL = D22 di ESP32)
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("RTC tidak terdeteksi, cek wiring!");
  } else {
    Serial.println("RTC DS3231 siap...");
  }
}
