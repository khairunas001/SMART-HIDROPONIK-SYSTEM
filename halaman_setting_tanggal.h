/*
  =========================================================
   Modul : Halaman Setting Tanggal (RTC)
   Author: shmukti

   Deskripsi:
     - Halaman ini digunakan untuk mengatur tanggal, bulan,
       dan tahun pada RTC DS3231.
     - Nilai jam/menit/detik tidak diubah di sini, hanya 
       mengikuti waktu RTC saat ini.

   Variabel:
     - HALAMAN_AWAL  = 6001
     - HALAMAN_AKHIR = 6004
     - set_tanggal, set_bulan, set_tahun : variabel sementara untuk input tanggal
     - halaman : halaman aktif (6001..6104)

   Alur Fungsi:
     1. Halaman 6001 → Set Tanggal
        - Highlight baris tanggal.
        - Range tanggal 1–31.
        - Navigasi:
          * UP/DOWN → pindah menu (6001–6004).
          * VALUE UP/DOWN → ubah tanggal.
          * OK → tetap di halaman 6001.
          * BACK → kembali ke menu setting utama (halaman = 6).

     2. Halaman 6002 → Set Bulan
        - Highlight baris bulan.
        - Range bulan 1–12.
        - Navigasi sama dengan 6001.

     3. Halaman 6003 → Set Tahun
        - Highlight baris tahun.
        - Range tahun 2000–2099.
        - Navigasi sama dengan 6001.

     4. Halaman 6004 → Menu Simpan
        - Highlight ">Simpan".
        - Tombol OK → pindah ke halaman 6104.
        - Tombol BACK → kembali ke menu utama (halaman = 6).

     5. Halaman 6104 → Eksekusi Simpan
        - LCD menampilkan "Tanggal Tersimpan!".
        - rtc.adjust() dipanggil untuk menyimpan tanggal baru:
            rtc.adjust(DateTime(set_tahun, set_bulan, set_tanggal,
                                now.hour(), now.minute(), now.second()));
        - Artinya hanya tanggal/bulan/tahun yang berubah, jam/menit/detik tetap sama.
        - Bunyi beep() sebagai notifikasi sukses.
        - Setelah delay 1 detik, kembali ke halaman 6004.

   Fungsi eksternal yang dipakai:
     - navigasi_button_value(var, step, min, max)
       → untuk mengatur nilai tanggal/bulan/tahun.
     - navigasi_button_ok_back(nextHalaman, backHalaman)
       → untuk navigasi OK & BACK.
     - navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR)
       → untuk navigasi menu ke atas/bawah.
     - rtc.adjust(DateTime(...))
       → untuk menyimpan tanggal baru ke RTC.
     - beep()
       → bunyi notifikasi setelah simpan.

   Catatan:
     - Validasi jumlah hari per bulan & tahun kabisat 
       belum diterapkan (tanggal bisa saja di-set ke 31/Feb).
     - rtc.adjust() langsung menimpa waktu RTC, 
       sehingga tidak boleh dipanggil terlalu sering.
     - Gunakan menu "Setting Jam" untuk update jam/menit/detik.

   Tujuan:
     - Memberikan cara mudah untuk setting tanggal RTC secara manual.
     - Memastikan waktu RTC tetap akurat untuk penjadwalan pompa.

  =========================================================
*/

#include "RTClib.h"
void halaman_setting_tanggal() {

  HALAMAN_AKHIR = 6004;
  HALAMAN_AWAL = 6001;

  if (halaman == 6001) {
    lcd.setCursor(0, 0);
    lcd.printf(">Tanggal:%.2d", set_tanggal);
    lcd.setCursor(0, 1);
    lcd.printf(" Bulan  :%.2d", set_bulan);
    lcd.setCursor(0, 2);
    lcd.printf(" Tahun  :%.2d", set_tahun);
    lcd.setCursor(0, 3);
    lcd.print(" Simpan");

    navigasi_button_value(set_tanggal, 1, 1, 31);
    navigasi_button_ok_back(6001, 6);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 6002) {
    lcd.setCursor(0, 0);
    lcd.printf(" Tanggal:%.2d", set_tanggal);
    lcd.setCursor(0, 1);
    lcd.printf(">Bulan  :%.2d", set_bulan);
    lcd.setCursor(0, 2);
    lcd.printf(" Tahun  :%.2d", set_tahun);
    lcd.setCursor(0, 3);
    lcd.print(" Simpan");

    navigasi_button_value(set_bulan, 1, 1, 12);
    navigasi_button_ok_back(6002, 6);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 6003) {
    lcd.setCursor(0, 0);
    lcd.printf(" Tanggal:%.2d", set_tanggal);
    lcd.setCursor(0, 1);
    lcd.printf(" Bulan  :%.2d", set_bulan);
    lcd.setCursor(0, 2);
    lcd.printf(">Tahun  :%.2d", set_tahun);
    lcd.setCursor(0, 3);
    lcd.print(" Simpan");

    navigasi_button_value(set_tahun, 1, 2000, 2099);
    navigasi_button_ok_back(6003, 6);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 6004) {
    lcd.setCursor(0, 0);
    lcd.printf(" Tanggal:%.2d", set_tanggal);
    lcd.setCursor(0, 1);
    lcd.printf(" Bulan  :%.2d", set_bulan);
    lcd.setCursor(0, 2);
    lcd.printf(" Tahun  :%.2d", set_tahun);
    lcd.setCursor(0, 3);
    lcd.print(">Simpan");

    navigasi_button_ok_back(6104, 6);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 6104) {
    lcd.clear();
    DateTime now = rtc.now();
    lcd.setCursor(0, 0);
    lcd.print("Tanggal Tersimpan!");
    // January 21, 2014 at 3am you would call:
    rtc.adjust(DateTime(set_tahun, set_bulan, set_tanggal, now.hour(), now.minute(), now.second()));

    delay(1000);
    beep();
    halaman = 6004;
  }
}
