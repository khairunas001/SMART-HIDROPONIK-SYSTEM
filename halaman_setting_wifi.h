/*
  =========================================================
   Modul : Halaman Setting WiFi
   Author: shmukti

   Deskripsi:
     - Halaman ini digunakan untuk mengatur SSID dan Password
       WiFi yang akan dipakai oleh ESP32.
     - User dapat mengubah nama SSID dan password langsung
       melalui input LCD & tombol navigasi.

   Variabel:
     - HALAMAN_AWAL  = 3001
     - HALAMAN_AKHIR = 3002
     - set_wifi_ssid     : String SSID WiFi
     - set_wifi_password : String password WiFi
     - halaman : halaman aktif (3001..3102)

   Alur Fungsi:
     1. Halaman 3001 → SSID
        - Menampilkan:
            >SSID:
             [set_wifi_ssid]
             Pass:
             [set_wifi_password]
        - Highlight pada "SSID".
        - Tombol OK → masuk ke halaman 3101 (edit SSID).
        - Tombol BACK → kembali ke menu sebelumnya.
        - Tombol UP/DOWN → pindah antar halaman (3001–3002).

     2. Halaman 3002 → Password
        - Menampilkan:
             SSID:
             [set_wifi_ssid]
            >Pass:
             [set_wifi_password]
        - Highlight pada "Pass".
        - Tombol OK → masuk ke halaman 3102 (edit Password).
        - Navigasi sama dengan 3001.

     3. Halaman 3101 → Input SSID
        - Memanggil input_text_alpabet("SSID:", set_wifi_ssid, 18).
        - Panjang maksimum SSID = 18 karakter.
        - Tombol BACK → kembali ke halaman 3001, beep() → feedback, lcd.clear().

     4. Halaman 3102 → Input Password
        - Memanggil input_text_nomor("Pass:", set_wifi_password, 18).
        - Panjang maksimum password = 18 karakter.
        - Tombol BACK → kembali ke halaman 3002, beep() → feedback, lcd.clear().

   Fungsi eksternal yang dipakai:
     - navigasi_button_ok_back(nextHalaman, backHalaman)
       → tombol OK masuk ke input, tombol BACK kembali.
     - navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR)
       → navigasi menu atas/bawah.
     - input_text_alpabet(label, var, maxLen)
       → input alfabet (SSID).
     - beep()
       → bunyi notifikasi saat BACK ditekan.

   Catatan:
     - Nilai SSID & password baru disimpan di variabel global 
       set_wifi_ssid & set_wifi_password.
     - Agar berlaku, modul driver_wifi akan menggunakan nilai ini
       saat connectWiFi().
     - Data dapat dipermanenkan ke NVS melalui simpan_memory().

   Tujuan:
     - Memberikan antarmuka pengaturan WiFi langsung di LCD.
     - Memungkinkan user mengganti SSID dan password 
       tanpa perlu re-flash program.

  =========================================================
*/

void halaman_setting_wifi() {

  HALAMAN_AKHIR = 3002;
  HALAMAN_AWAL = 3001;

  if (halaman == 3001) {
    lcd.setCursor(0, 0);
    lcd.print(">SSID:");
    lcd.setCursor(1, 1);
    lcd.print(set_wifi_ssid);
    lcd.setCursor(0, 2);
    lcd.print(" Pass:");
    lcd.setCursor(1, 3);
    lcd.print(set_wifi_password);

    navigasi_button_ok_back(3101, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 3002) {
    lcd.setCursor(0, 0);
    lcd.print(" SSID:");
    lcd.setCursor(1, 1);
    lcd.print(set_wifi_ssid);
    lcd.setCursor(0, 2);
    lcd.print(">Pass:");
    lcd.setCursor(1, 3);
    lcd.print(set_wifi_password);
    navigasi_button_ok_back(3102, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 3101) {
    String temp_set_wifi_ssid = set_wifi_ssid;
    input_text_alpabet("SSID:", set_wifi_ssid, 18);
    if (temp_set_wifi_ssid != set_wifi_ssid) {
      simpan_memory();
    }
    if (BTN_BACK) {
      halaman = 3001;
      beep();
      lcd.clear();
    }
  }
  if (halaman == 3102) {
    String temp_set_wifi_pass = set_wifi_password;
    input_text_alpabet("Pass:", set_wifi_password, 18);
    if (temp_set_wifi_pass != set_wifi_password) {
      simpan_memory();
    }
    if (BTN_BACK) {
      halaman = 3002;
      beep();
      lcd.clear();
    }
  }
}
