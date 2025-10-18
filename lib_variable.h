#include "Arduino.h"
#include "WString.h"
/*
  =========================================================
   Modul : Variabel Global Sistem Hidroponik
   Author: shmukti

   Deskripsi:
     - Variabel-variabel global ini digunakan untuk menyimpan
       status, konfigurasi, data sensor, dan pengaturan jadwal
       pada sistem kendali hidroponik berbasis ESP32.

   Struktur Variabel:

   1. Navigasi Halaman
      - halaman        : halaman aktif saat ini
      - HALAMAN_AWAL   : indeks halaman awal menu
      - HALAMAN_AKHIR  : indeks halaman akhir menu

   2. Setting Waktu
      - set_jam, set_menit, set_detik
      - set_tanggal, set_bulan, set_tahun, set_hari
        → digunakan untuk setting RTC/manual time.

   3. Status Pompa (runtime)
      - status_pompa_air, status_pompa_na, status_pompa_nb,
        status_pompa_phu, status_pompa_phd
        → menyimpan kondisi pompa (ON/OFF).

   4. Setting Status Pompa (dari menu)
      - set_status_pompa_air, set_status_pompa_na, dst
        → nilai target ON/OFF yang bisa diubah dari LCD/menu.

   5. Data Sensor
      - nilai_kelembaban_udara (DHT11)
      - nilai_suhu_udara (DHT11)
      - nilai_suhu_air (DS18B20)
      - nilai_ph (sensor pH analog/serial)
      - nilai_tds (sensor TDS analog)

   6. Konfigurasi Jaringan & MQTT
      - set_mqtt_broker   : alamat broker MQTT (String)
      - set_mqtt_port     : port broker MQTT
      - set_wifi_ssid     : SSID WiFi
      - set_wifi_password : password WiFi
      - set_timer_telemetry  : interval publish telemetry (ms)
      - set_prefix_telemetry : prefix telemetry untuk topic publish mqtt
      
   7. Jadwal Otomatisasi
      - index_jadwal : indeks jadwal aktif
      - JUMLAH_JADWAL : jumlah maksimum jadwal (5)
      - Array per-jadwal (tiap index 0..JUMLAH_JADWAL-1):
          * jadwal_status         : aktif/non-aktif jadwal
          * jadwal_hari_senin..minggu : hari eksekusi
          * jadwal_jam/menit/detik : waktu eksekusi
          * jadwal_limit_tds / jadwal_status_tds / jadwal_operasi_tds
          * jadwal_limit_ph / jadwal_status_ph / jadwal_operasi_ph
          * jadwal_timer_pompa_na/nb/phu/phd : durasi pompa (detik)
          * jadwal_set_pompa_na/nb/phu/phd   : ON/OFF pompa yang dijalankan

   Catatan:
     - Semua variabel ini bersifat global agar dapat diakses
       dari berbagai modul (telemetry, jadwal, menu LCD, dsb).
     - Nilai default diinisialisasi di awal, dan bisa disimpan/
       dibaca kembali melalui NVS (lihat modul simpan_memory).
     - Status runtime (status_pompa_x) berbeda dengan setting
       (set_status_pompa_x) → yang pertama merepresentasikan
       kondisi pompa saat ini, yang kedua merepresentasikan target.

   Tujuan:
     - Menyediakan penyimpanan global untuk seluruh parameter
       sistem hidroponik sehingga mudah diakses dan dikontrol.
  =========================================================
*/

int halaman = 0;
int HALAMAN_AWAL;
int HALAMAN_AKHIR;

int set_jam = 15;
int set_menit = 20;
int set_detik = 0;

int set_tanggal = 25;
int set_bulan = 8;
int set_tahun = 2025;
int set_hari = 1;

int status_pompa_air = 0;
int status_pompa_na = 0;
int status_pompa_nb = 0;
int status_pompa_phu = 0;
int status_pompa_phd = 0;
int status_solenoid = 0;

int set_status_pompa_air = 0;
int set_status_pompa_na = 0;
int set_status_pompa_nb = 0;
int set_status_pompa_phu = 0;
int set_status_pompa_phd = 0;
int set_status_solenoid = 0;

//-------------- variable global untuk automasi pompa/kran air
byte set_waterlevel_automode = 1;  // true = otomatis pakai sensor, false = manual via MQTT

int nilai_kelembaban_udara = 0;
int nilai_suhu_udara = 0;
int nilai_suhu_air = 0;
int nilai_ph = 0;
int nilai_tds = 0;

String set_mqtt_broker = "broker.mqtt.cool";
String set_mqtt_port = "1883";

String set_wifi_ssid = "tselhome_0B20";
String set_wifi_password = "qbGhR782R8N";

String set_timer_telemetry = "5000";
String set_prefix_telemetry = "bpvpska/hdp1/";

int index_jadwal = 0;
#define JUMLAH_JADWAL 5
int jadwal_status[JUMLAH_JADWAL] = { 1, 0, 0, 0, 0 };
int jadwal_hari_senin[JUMLAH_JADWAL] = { 1, 1, 1, 1, 1 };
int jadwal_hari_selasa[JUMLAH_JADWAL] = { 1, 1, 1, 1, 1 };
int jadwal_hari_rabu[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_hari_kamis[JUMLAH_JADWAL] = { 1, 1, 1, 1, 1 };
int jadwal_hari_jumat[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_hari_sabtu[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_hari_minggu[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_jam[JUMLAH_JADWAL] = { 15, 0, 0, 0, 0 };
int jadwal_menit[JUMLAH_JADWAL] = { 21, 0, 0, 0, 0 };
int jadwal_detik[JUMLAH_JADWAL] = { 10, 0, 0, 0, 0 };
int jadwal_limit_tds[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_status_tds[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_operasi_tds[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_status_ph[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_limit_ph[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_operasi_ph[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };

int jadwal_timer_pompa_na[JUMLAH_JADWAL] = { 1, 0, 0, 0, 0 };
int jadwal_timer_pompa_nb[JUMLAH_JADWAL] = { 2, 0, 0, 0, 0 };
int jadwal_timer_pompa_phu[JUMLAH_JADWAL] = { 3, 0, 0, 0, 0 };
int jadwal_timer_pompa_phd[JUMLAH_JADWAL] = { 4, 0, 0, 0, 0 };

int jadwal_set_pompa_na[JUMLAH_JADWAL] = { 1, 0, 0, 0, 0 };
int jadwal_set_pompa_nb[JUMLAH_JADWAL] = { 1, 0, 0, 0, 0 };
int jadwal_set_pompa_phu[JUMLAH_JADWAL] = { 0, 0, 0, 0, 0 };
int jadwal_set_pompa_phd[JUMLAH_JADWAL] = { 1, 0, 0, 0, 0 };

String txt_on_off[2] = { "OFF", "ON " };