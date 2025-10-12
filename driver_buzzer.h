/*
  =========================================================
   Modul : Buzzer
   Author: shmukti

   Deskripsi:
     - Modul ini digunakan untuk menghasilkan bunyi sederhana 
       sebagai indikator (notifikasi, konfirmasi input, dsb).
     - Buzzer dikontrol dengan sinyal digital HIGH/LOW.

   Konfigurasi Pin:
     - PIN_BUZZER = GPIO 26

   Fungsi:
     1. setup_buzzer()
        - Dipanggil sekali pada setup().
        - Mengatur pin buzzer sebagai OUTPUT.
        - Memastikan buzzer dalam keadaan mati (LOW) saat awal.
        - Menampilkan pesan "buzzer siap digunakan...."
          ke Serial Monitor.

     2. beep()
        - Membunyikan buzzer selama 200 ms.
        - Digunakan sebagai suara singkat (beep) 
          misalnya saat tombol ditekan atau aksi berhasil.

     3. greeting_buzer()
        - Memberikan efek bunyi sapaan (dua kali beep dengan jeda).
        - Pola:
            HIGH 200 ms → LOW 500 ms → HIGH 200 ms → LOW
        - Cocok dipanggil saat device baru menyala (startup greeting).

   Catatan:
     - Buzzer ini tipe aktif (cukup diberi HIGH untuk bunyi).
       Jika buzzer tipe pasif → perlu PWM/analogWrite.
     - Durasi delay() masih blocking, 
       bila ingin non-blocking gunakan millis().
     - Volume tergantung spesifikasi buzzer (3.3V/5V).

   Tujuan:
     - Memberikan feedback audio sederhana bagi user.
     - Meningkatkan user experience pada sistem navigasi menu
       dan notifikasi event.

  =========================================================
*/

// Definisi pin buzzer
#define PIN_BUZZER 26

void setup_buzzer() {
  // Set pin buzzer sebagai output
  pinMode(PIN_BUZZER, OUTPUT);

  // Matikan buzzer di awal
  digitalWrite(PIN_BUZZER, LOW);
  Serial.println("buzzer siap digunakan....");
}

void beep() {
  // Bunyikan buzzer selama 500 ms
  digitalWrite(PIN_BUZZER, HIGH);
  delay(200);
  // Matikan buzzer
  digitalWrite(PIN_BUZZER, LOW);
}

void greeting_buzer() {
  digitalWrite(PIN_BUZZER, HIGH);
  delay(200);
  digitalWrite(PIN_BUZZER, LOW);
  delay(500);
  digitalWrite(PIN_BUZZER, HIGH);
  delay(200);
  digitalWrite(PIN_BUZZER, LOW);
}
