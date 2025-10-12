/*
  =========================================================
   Modul : Halaman Setting Jam (RTC)
   Author: shmukti

   Deskripsi:
     - Halaman ini digunakan untuk mengatur jam, menit, 
       dan detik pada RTC DS3231.
     - User dapat menaikkan/menurunkan nilai dengan tombol 
       navigasi dan menyimpan hasil setting ke RTC.

   Variabel:
     - HALAMAN_AWAL  = 5001
     - HALAMAN_AKHIR = 5004
     - set_jam, set_menit, set_detik : variabel sementara untuk input waktu
     - halaman : halaman aktif (5001..5104)

   Alur Fungsi:
     1. Halaman 5001 → Set Jam
        - Highlight baris jam.
        - Tampilkan nilai jam (00–23).
        - Navigasi:
          * UP/DOWN → pindah menu (5001–5004).
          * VALUE UP/DOWN → ubah nilai jam (0–23).
          * OK → tetap di halaman 5001.
          * BACK → kembali ke halaman setting utama (halaman = 5).

     2. Halaman 5002 → Set Menit
        - Highlight baris menit.
        - Range menit (00–59).
        - Navigasi sama dengan 5001.

     3. Halaman 5003 → Set Detik
        - Highlight baris detik.
        - Range detik (00–59).
        - Navigasi sama dengan 5001.

     4. Halaman 5004 → Menu Simpan
        - Highlight ">Simpan".
        - Tombol OK → pindah ke halaman 5104.
        - Tombol BACK → kembali ke menu utama (halaman = 5).

     5. Halaman 5104 → Eksekusi Simpan
        - Ambil tanggal & tahun dari RTC sekarang (rtc.now()).
        - Menyimpan jam, menit, detik baru dengan rtc.adjust().
        - Menampilkan pesan "Jam Tersimpan!".
        - Beep sebagai notifikasi.
        - Setelah delay 1 detik, kembali ke halaman 5004.

   Fungsi eksternal yang dipakai:
     - navigasi_button_value(var, step, min, max)
       → untuk mengatur nilai jam/menit/detik.
     - navigasi_button_ok_back(nextHalaman, backHalaman)
       → untuk navigasi OK & BACK.
     - navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR)
       → untuk navigasi menu ke atas/bawah.
     - rtc.adjust(DateTime(...))
       → untuk menyimpan jam baru ke RTC.
     - beep()
       → bunyi notifikasi setelah simpan.

   Catatan:
     - Nilai tahun, bulan, dan tanggal tidak diubah di menu ini 
       (hanya jam, menit, detik).
     - rtc.adjust() otomatis mengubah waktu RTC sesuai input baru.
     - Gunakan menu "Setting Tanggal" untuk update tanggal/bulan/tahun.
     - Penggunaan delay(1000) masih blocking, bisa diganti millis() 
       jika ingin lebih responsif.

   Tujuan:
     - Memungkinkan user mengatur jam RTC secara manual.
     - Memberikan konfirmasi visual & audio setelah setting disimpan.

  =========================================================
*/

void halaman_setting_jam() {

  HALAMAN_AKHIR = 5004;
  HALAMAN_AWAL = 5001;

  if (halaman == 5001) {
    lcd.setCursor(0, 0);
    lcd.printf(">Jam  :%.2d", set_jam);
    lcd.setCursor(0, 1);
    lcd.printf(" Menit:%.2d", set_menit);
    lcd.setCursor(0, 2);
    lcd.printf(" Detik:%.2d", set_detik);
    lcd.setCursor(0, 3);
    lcd.printf(" Simpan");
    navigasi_button_value(set_jam, 1, 0, 23);
    navigasi_button_ok_back(5001, 5);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 5002) {
    lcd.setCursor(0, 0);
    lcd.printf(" Jam  :%.2d", set_jam);
    lcd.setCursor(0, 1);
    lcd.printf(">Menit:%.2d", set_menit);
    lcd.setCursor(0, 2);
    lcd.printf(" Detik:%.2d", set_detik);
    lcd.setCursor(0, 3);
    lcd.printf(" Simpan");
    navigasi_button_value(set_menit, 1, 0, 59);
    navigasi_button_ok_back(5002, 5);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 5003) {
    lcd.setCursor(0, 0);
    lcd.printf(" Jam  :%.2d", set_jam);
    lcd.setCursor(0, 1);
    lcd.printf(" Menit:%.2d", set_menit);
    lcd.setCursor(0, 2);
    lcd.printf(">Detik:%.2d", set_detik);
    lcd.setCursor(0, 3);
    lcd.printf(" Simpan");
    navigasi_button_value(set_detik, 1, 0, 59);
    navigasi_button_ok_back(5003, 5);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 5004) {
    lcd.setCursor(0, 0);
    lcd.printf(" Jam  :%.2d", set_jam);
    lcd.setCursor(0, 1);
    lcd.printf(" Menit:%.2d", set_menit);
    lcd.setCursor(0, 2);
    lcd.printf(" Detik:%.2d", set_detik);
    lcd.setCursor(0, 3);
    lcd.printf(">Simpan");
    navigasi_button_ok_back(5104, 5);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 5104) {
    lcd.clear();
    DateTime now = rtc.now();
    lcd.setCursor(0, 0);
    lcd.print("Jam Tersimpan!");
    // January 21, 2014 at 3am you would call:
    rtc.adjust(DateTime(now.year(), now.month(), now.day(),
                        set_jam, set_menit, set_detik));
    delay(1000);
    beep();
    halaman = 5004;
  }
}