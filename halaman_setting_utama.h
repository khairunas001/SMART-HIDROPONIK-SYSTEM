/*
  =========================================================
   Modul : Halaman Setting Utama LCD
   Author: shmukti

   Deskripsi:
     - Halaman ini berfungsi sebagai menu utama pengaturan 
       sistem Smart Hidroponik. 
     - User dapat memilih sub-menu untuk konfigurasi:
         * Setting Jadwal
         * Setting Telemetry
         * Setting WiFi
         * Setting MQTT
         * Setting Jam
         * Setting Tanggal
         * Kontrol Manual

   Variabel:
     - HALAMAN_AWAL = 1  → indeks halaman pertama
     - HALAMAN_AKHIR = 7 → indeks halaman terakhir
     - halaman       = halaman aktif saat ini

   Alur fungsi:
     1. Jika halaman == 1:
        - Menampilkan menu dengan highlight pada ">Setting Jadwal".
        - Tombol OK → masuk ke halaman 1001.
        - Tombol UP/DOWN → navigasi ke halaman lain.

     2. Jika halaman == 2:
        - Highlight ">Setting Telemetry".
        - Tombol OK → masuk ke halaman 2001.

     3. Jika halaman == 3:
        - Highlight ">Setting Wifi".
        - Tombol OK → masuk ke halaman 3001.

     4. Jika halaman == 4:
        - Highlight ">Setting MQTT".
        - Tombol OK → masuk ke halaman 4001.

     5. Jika halaman == 5:
        - Highlight ">Setting Jam".
        - Tombol OK → masuk ke halaman 5001.

     6. Jika halaman == 6:
        - Highlight ">Setting Tanggal".
        - Tombol OK → masuk ke halaman 6001.

     7. Jika halaman == 7:
        - Highlight ">Kontrol Manual".
        - Tombol OK → masuk ke halaman 7001.

   Navigasi:
     - Tombol UP/DOWN → berpindah halaman (1..7).
     - Tombol OK → masuk ke sub-halaman sesuai pilihan.
     - Tombol BACK → kembali ke halaman sebelumnya (biasanya halaman utama = 0).
     - Fungsi helper:
         * navigasi_button_ok_back(targetHalamanOK, targetHalamanBack)
         * navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR)

   Catatan:
     - LCD menggunakan format 20x4, setiap menu ditampilkan pada baris berbeda.
     - Menu aktif selalu ditandai dengan tanda ">" di depan teks.
     - Sistem ini modular, setiap sub-menu memiliki file halaman_xxx.h sendiri.

   Tujuan:
     - Memberikan antarmuka pengaturan yang mudah dipahami.
     - Mengizinkan user mengatur jadwal, konektivitas, 
       dan kontrol manual pompa langsung dari LCD + tombol.

  =========================================================
*/

void halaman_setting_utama() {

  HALAMAN_AKHIR = 8;
  HALAMAN_AWAL = 1;

  if (halaman == 1) {
    lcd.setCursor(0, 0);
    lcd.print(">Setting Jadwal");
    lcd.setCursor(0, 1);
    lcd.print(" Setting Telemetry");
    lcd.setCursor(0, 2);
    lcd.print(" Setting Wifi");
    lcd.setCursor(0, 3);
    lcd.print(" Setting MQTT");

    navigasi_button_ok_back(1001, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 2) {
    lcd.setCursor(0, 0);
    lcd.print(" Setting Jadwal");
    lcd.setCursor(0, 1);
    lcd.print(">Setting Telemetry");
    lcd.setCursor(0, 2);
    lcd.print(" Setting Wifi");
    lcd.setCursor(0, 3);
    lcd.print(" Setting MQTT");

    navigasi_button_ok_back(2001, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 3) {
    lcd.setCursor(0, 0);
    lcd.print(" Setting Jadwal");
    lcd.setCursor(0, 1);
    lcd.print(" Setting Telemetry");
    lcd.setCursor(0, 2);
    lcd.print(">Setting Wifi");
    lcd.setCursor(0, 3);
    lcd.print(" Setting MQTT");

    navigasi_button_ok_back(3001, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 4) {
    lcd.setCursor(0, 0);
    lcd.print(" Setting Jadwal");
    lcd.setCursor(0, 1);
    lcd.print(" Setting Telemetry");
    lcd.setCursor(0, 2);
    lcd.print(" Setting Wifi");
    lcd.setCursor(0, 3);
    lcd.print(">Setting MQTT");

    navigasi_button_ok_back(4001, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 5) {

    lcd.setCursor(0, 0);
    lcd.print(" Setting Jadwal");
    lcd.setCursor(0, 1);
    lcd.print(" Setting Wifi");
    lcd.setCursor(0, 2);
    lcd.print(" Setting MQTT");

    lcd.setCursor(0, 3);
    lcd.print(">Setting Jam");

    navigasi_button_ok_back(5001, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 6) {

    lcd.setCursor(0, 0);
    lcd.print(" Setting Wifi");
    lcd.setCursor(0, 1);
    lcd.print(" Setting MQTT");
    lcd.setCursor(0, 2);
    lcd.print(" Setting Jam");
    lcd.setCursor(0, 3);
    lcd.print(">Setting Tanggal");

    navigasi_button_ok_back(6001, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 7) {

    lcd.setCursor(0, 0);
    lcd.print(" Setting MQTT");
    lcd.setCursor(0, 1);
    lcd.print(" Setting Jam");
    lcd.setCursor(0, 2);
    lcd.print(" Setting Tanggal");
    lcd.setCursor(0, 3);
    lcd.print(">Kontrol Manual");

    navigasi_button_ok_back(7001, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  
  if (halaman == 8) {

    lcd.setCursor(0, 0);
    lcd.print(" Setting Jam");
    lcd.setCursor(0, 1);
    lcd.print(" Setting Tanggal");
    lcd.setCursor(0, 2);
    lcd.print(" Kontrol Manual");
    lcd.setCursor(0, 3);
    lcd.print(">Set Water Level");

    navigasi_button_ok_back(8001, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
}