/*
  =========================================================
   Modul : Kontrol Relay Pompa Air
   Author: shmukti

   Deskripsi:
     - Modul ini mengatur hidup/mati pompa air utama
       menggunakan relay yang dikendalikan oleh ESP32.
     - Konfigurasi hardware: relay aktif LOW, pompa terhubung
       ke jalur NC (Normally Closed) – COM.
     - Artinya:
         * LOW  → relay aktif, COM berpindah ke NO → pompa MATI
         * HIGH → relay tidak aktif, COM tetap di NC → pompa HIDUP
     - Dengan konfigurasi ini, kondisi default saat ESP32 
       baru menyala adalah pompa HIDUP.

   Konfigurasi Pin:
     - PIN_RELAY_PA = GPIO 4 → Relay Pompa Air

   Fungsi:
     1. nyalakan_pompa_air()
        - Memberikan sinyal HIGH ke relay.
        - Relay tidak aktif → COM tetap ke NC → pompa HIDUP.
        - Set variabel status_pompa_air = 1 (ON).

     2. matikan_pompa_air()
        - Memberikan sinyal LOW ke relay.
        - Relay aktif → COM pindah ke NO → pompa MATI.
        - Set variabel status_pompa_air = 0 (OFF).

     3. setup_pompa_air()
        - Dipanggil sekali di setup().
        - Mengatur pin relay sebagai OUTPUT.
        - Secara default memanggil nyalakan_pompa_air()
          (pompa HIDUP saat sistem start).
        - Menampilkan pesan "pompa air siap digunakan...."
          di Serial Monitor.

     4. update_status_pompa_air()
        - Menyamakan kondisi target (set_status_pompa_air) 
          dengan status aktual (status_pompa_air).
        - Jika berbeda, panggil fungsi ON/OFF yang sesuai.

   Tujuan:
     - Memberikan kontrol pompa air utama secara manual maupun otomatis.
     - Menjamin status aktual relay selalu sesuai dengan target sistem
       (misalnya dari menu LCD, jadwal, atau perintah MQTT).

  =========================================================
*/

// perlu ini karena akan didefinisikan 2 kali di sini dan di
#ifndef DRIVER_POMPA_AIR_H
#define DRIVER_POMPA_AIR_H

#define PIN_RELAY_PA 4

void matikan_pompa_air() {
  //matikan pompa
  digitalWrite(PIN_RELAY_PA, LOW);
  status_pompa_air = 0;
  set_status_pompa_air = 0;
}
void nyalakan_pompa_air() {
  //nyalakan pompa
  digitalWrite(PIN_RELAY_PA, HIGH);
  status_pompa_air = 1;
  set_status_pompa_air = 1;
}

void setup_pompa_air() {
  //set pin relay pompa sebagai output
  pinMode(PIN_RELAY_PA, OUTPUT);
  //defaultnya adalah pompa hidup
  nyalakan_pompa_air();

  Serial.println("pompa air siap digunakan....");
}

void update_status_pompa_air() {
  if (set_status_pompa_air != status_pompa_air) {
    if (set_status_pompa_air == 1) {
      nyalakan_pompa_air();
    }
    if (set_status_pompa_air == 0) {
      matikan_pompa_air();
    }
  }
}

#endif