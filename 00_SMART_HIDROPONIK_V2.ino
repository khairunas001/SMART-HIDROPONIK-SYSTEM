/*
  =========================================================
   Project : Smart Hidroponik ESP32
   Author  : shmukti
   Versi   : 1.0

   Deskripsi:
     - Program utama sistem Smart Hidroponik berbasis ESP32.
     - Sistem ini mengintegrasikan berbagai sensor, aktuator,
       RTC, komunikasi WiFi & MQTT, serta antarmuka LCD + tombol.
     - Semua fitur dipisah menjadi modul (library/driver) 
       untuk memudahkan maintenance dan pengembangan.

   Library & Modul yang Digunakan:
     - Every.h              : timer non-blocking berbasis millis
     - lib_variable.h       : definisi variabel global
     - lib_memory.h         : baca/tulis konfigurasi ke NVS
     - driver_lcd.h         : tampilan LCD I2C
     - driver_buzzer.h      : kontrol buzzer
     - driver_button.h      : input tombol navigasi
     - driver_dht.h         : sensor suhu & kelembaban udara (DHT11)
     - driver_ds18b20.h     : sensor suhu air (DS18B20)
     - driver_tds_meter.h   : sensor TDS (kadar nutrisi air)
     - driver_pompa_air.h   : kontrol relay pompa air
     - driver_pompa_nutrisi.h: kontrol relay pompa nutrisi & pH
     - driver_rtc.h         : RTC DS3231 untuk penjadwalan
     - driver_wifi.h        : koneksi WiFi
     - driver_mqtt.h        : komunikasi MQTT
     - lib_telemetry.h      : publish data sensor ke MQTT
     - lib_navigasi_menu.h  : logika navigasi menu LCD
     - lib_jadwal.h         : logika jadwal otomatis pompa
     - halaman_*.h          : halaman-halaman menu LCD
         * halaman_utama.h
         * halaman_setting_utama.h
         * halaman_setting_jadwal.h
         * halaman_setting_jadwal_detail.h
         * halaman_setting_jam.h
         * halaman_setting_tanggal.h
         * halaman_setting_mqtt.h
         * halaman_setting_wifi.h
         * halaman_setting_kontrol_manual.h
         * halaman_setting_telemetry.h

   Fungsi Utama:
     1. setup()
        - Inisialisasi serial monitor.
        - Memanggil fungsi setup_xx() dari setiap driver/modul.
        - Memberikan greeting buzzer.
        - Menampilkan splash screen di LCD:
            "Smart Hidroponik"
            "Satpel Bantul"
            "BBPV Surakarta"
            "Version 1.0"
          selama 5 detik, lalu clear.
        - Bunyi beep setelah splash screen.

     2. loop()
        - Menjalankan fungsi loop_xx() untuk menjaga sistem berjalan:
            * loop_wifi()       : cek koneksi WiFi
            * loop_mqtt()       : cek & handle koneksi MQTT
            * loop_telemetry()  : publish data sensor ke broker
            * loop_jadwal()     : eksekusi jadwal pompa
        - Menjalankan fungsi halaman_xx() untuk menampilkan 
          dan mengontrol menu LCD interaktif:
            * halaman_utama()
            * halaman_setting_utama()
            * halaman_setting_jadwal()
            * halaman_setting_jadwal_detail()
            * halaman_setting_jam()
            * halaman_setting_tanggal()
            * halaman_setting_mqtt()
            * halaman_setting_wifi()
            * halaman_setting_kontrol_manual()
            * halaman_setting_telemetry()

   Catatan:
     - Semua modul dibuat terpisah dalam file .h agar struktur 
       program lebih modular dan mudah di-maintain.
     - Timer non-blocking digunakan (library Every) untuk 
       menghindari penggunaan delay() berlebihan.
     - MQTT & WiFi harus terkoneksi agar data telemetry bisa terkirim.
     - RTC DS3231 memastikan eksekusi jadwal berjalan sesuai waktu nyata.
     - Sistem ini bisa diintegrasikan dengan dashboard IoT 
       melalui MQTT broker (misalnya Node-RED, ThingsBoard, dll).

   Tujuan:
     - Mengotomatisasi sistem hidroponik (penjadwalan nutrisi & pH).
     - Memantau data sensor (suhu udara, kelembaban, suhu air, TDS, pH).
     - Memberikan antarmuka lokal (LCD + tombol + buzzer).
     - Memberikan konektivitas IoT (WiFi + MQTT) untuk monitoring jarak jauh.

  =========================================================
*/

#include <Every.h>

#include "lib_variable.h"
#include "lib_memory.h"

#include "driver_lcd.h"
#include "driver_buzzer.h"
#include "driver_button.h"
#include "driver_dht.h"
#include "driver_ds18b20.h"
#include "driver_tds_meter.h"
#include "driver_ph_meter.h"
#include "driver_pompa_air.h"
#include "driver_pompa_nutrisi.h"
#include "driver_rtc.h"
#include "driver_wifi.h"
#include "driver_solenoid.h"
#include "driver_water_level.h"
#include "driver_mqtt.h"

#include "driver_sensor_cahaya.h"
#include "lib_telemetry.h"
#include "lib_navigasi_menu.h"
#include "lib_jadwal.h"
#include "halaman_utama.h"
#include "halaman_setting_waterlevel.h"
#include "halaman_setting_utama.h"
#include "halaman_setting_jadwal.h"
#include "halaman_setting_jadwal_detail.h"
#include "halaman_setting_jam.h"
#include "halaman_setting_tanggal.h"
#include "halaman_setting_mqtt.h"
#include "halaman_setting_wifi.h"
#include "halaman_setting_kontrol_manual.h"
#include "halaman_setting_telemetry.h"

void setup() {

  Serial.begin(115200);
  setup_memory();

  setup_lcd();
  setup_button();
  setup_buzzer();
  setup_dht();
  setup_ds18b20();
  setup_tds_meter();
  setup_ph_meter();
  setup_pompa_air();
  setup_pompa_nutrisi();
  setup_solenoid();
  setup_rtc();
  setup_wifi();
  setup_mqtt();
  setup_telemetry();
  setup_water_level();
  setup_sensor_cahaya();
  greeting_buzer();


  // Tampilkan pesan pembuka
  lcd.setCursor(0, 0);
  lcd.print("Smart Hydroponic");
  lcd.setCursor(0, 1);
  lcd.print("BLKPP DIY");
  lcd.setCursor(0, 2);
  lcd.print("Kelompok 2");
  lcd.setCursor(0, 3);
  lcd.print("BPVP Surakarta V2.0");
  delay(5000);
  lcd.clear();

  beep();
}

void loop() {
  loop_wifi();
  loop_mqtt();
  loop_telemetry();
  loop_jadwal();
  loop_water_level();
  loop_sensor_cahaya();
  
  halaman_utama();
  halaman_setting_utama();
  halaman_setting_waterlevel();
  halaman_setting_jadwal();
  halaman_setting_jadwal_detail();
  halaman_setting_jam();
  halaman_setting_tanggal();
  halaman_setting_mqtt();
  halaman_setting_wifi();
  halaman_setting_kontrol_manual();
  halaman_setting_telemetry();
}
