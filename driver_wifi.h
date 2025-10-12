/*
  =========================================================
   Modul : WiFi Client ESP32
   Author: shmukti

   Deskripsi:
     - Modul ini mengatur koneksi ESP32 ke jaringan WiFi
       menggunakan library bawaan WiFi.h.
     - SSID dan Password diambil dari variabel global
       set_wifi_ssid dan set_wifi_password.
     - Koneksi dicek setiap 2 detik menggunakan timer_wifi.

   Konfigurasi:
     - WIFI_SSID : SSID target WiFi
     - WIFI_PASS : Password target WiFi
     - WiFiClient espClient : client WiFi yang digunakan 
       oleh MQTT (PubSubClient)
     - Interval reconnect : 2000 ms (2 detik)

   Fungsi:
     1. connectWiFi()
        - Dipanggil tiap 2 detik (timer_wifi).
        - Mengambil SSID & PASS dari variabel global.
        - Mengecek status WiFi:
            * Jika tidak terkoneksi → cetak "Wifi tidak terkoneksi.."
            * Jika terkoneksi → tampilkan IP lokal di Serial Monitor.
        - Catatan: baris WiFi.begin() dikomentari di sini, 
          sehingga awal koneksi dipicu oleh setup_wifi().

     2. setup_wifi()
        - Dipanggil di setup().
        - Set mode WiFi menjadi station (WIFI_STA).
        - Ambil SSID & PASS dari variabel global.
        - Panggil WiFi.begin() untuk memulai koneksi.
        - Tampilkan "WiFi siap digunakan...." di Serial.
        - Panggil connectWiFi() untuk cek status awal.

     3. loop_wifi()
        - Dipanggil di loop utama.
        - Mengecek status WiFi secara berkala.
        - Jika tidak terkoneksi → panggil connectWiFi() 
          untuk mencoba ulang.

   Catatan:
     - Library WiFi.h bawaan ESP32 digunakan.
     - WiFi.begin() membutuhkan beberapa detik untuk terkoneksi, 
       sehingga biasanya dicek dengan loop while(WiFi.status() != WL_CONNECTED).
     - Untuk koneksi stabil, bisa tambahkan retry count 
       atau fallback ke AP mode jika gagal.
     - Variabel set_wifi_ssid & set_wifi_password 
       bisa disimpan permanen di NVS (Preferences).

   Tujuan:
     - Memastikan ESP32 tetap terhubung ke WiFi secara otomatis.
     - Memberikan koneksi dasar untuk MQTT dan komunikasi IoT.

  =========================================================
*/

#include <WiFi.h>

// KONFIGURASI WIFI
String WIFI_SSID="";
String WIFI_PASS="";

WiFiClient espClient;

Every timer_wifi(2000);  //setiap 2 detik

void connectWiFi() {

  if (timer_wifi()) {  // cek setiap 2 detik
    WIFI_SSID = set_wifi_ssid;
    WIFI_PASS = set_wifi_password;

    Serial.print("Menghubungkan WiFi: ");
    Serial.println(WIFI_SSID);
    //WiFi.begin(WIFI_SSID.c_str(), WIFI_PASS.c_str());
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Wifi tidak terkoneksi..");
    } else {
      Serial.print("\nWiFi OK. IP: ");
      Serial.println(WiFi.localIP());
    }
  }
}

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WIFI_SSID = set_wifi_ssid;
  WIFI_PASS = set_wifi_password;

  WiFi.begin(WIFI_SSID.c_str(), WIFI_PASS.c_str());
  Serial.println("WiFi siap digunakan....");
  connectWiFi();
}

void loop_wifi() {

  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
}
