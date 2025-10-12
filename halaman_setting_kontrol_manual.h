/*
  =========================================================
   Modul : Halaman Setting Kontrol Manual Pompa
   Author: shmukti

   Deskripsi:
     - Menu untuk mengubah status ON/OFF pompa secara manual
       langsung dari LCD, tanpa menunggu jadwal.
     - Pompa yang dikendalikan:
         * Air   (set_status_pompa_air)
         * NA    (set_status_pompa_na)
         * NB    (set_status_pompa_nb)
         * PHU   (set_status_pompa_phu)
         * PHD   (set_status_pompa_phd)
     - Status ditampilkan dengan teks "OFF"/"ON ".

   Variabel:
     - txt_status_pompa[2] : {"OFF","ON "}
     - HALAMAN_AWAL  = 7001
     - HALAMAN_AKHIR = 7005
     - halaman       : 7001..7005 (tiap halaman fokus ke satu pompa)
     - set_status_pompa_x : target status yang dapat diubah dari menu
     - update_status_pompa_air()/update_status_pompa_nutrisi()
       akan menyelaraskan target dengan kondisi relay aktual.

   Alur Halaman:
     - 7001 → Fokus ke Pompa Air (baris diberi tanda '>'):
         Tampilkan semua status; VALUE UP/DOWN mengubah Air.
         Panggil update_status_pompa_air() untuk eksekusi.
     - 7002 → Fokus ke Pompa NA; VALUE UP/DOWN mengubah NA.
         Panggil update_status_pompa_nutrisi().
     - 7003 → Fokus ke Pompa NB; VALUE UP/DOWN mengubah NB.
         Panggil update_status_pompa_nutrisi().
     - 7004 → Fokus ke Pompa PHU; VALUE UP/DOWN mengubah PHU.
         Panggil update_status_pompa_nutrisi().
     - 7005 → Fokus ke Pompa PHD; VALUE UP/DOWN mengubah PHD.
         Panggil update_status_pompa_nutrisi().

   Navigasi:
     - navigasi_button_value(var, step=1, min=0, max=1)
       → ubah ON/OFF pompa yang sedang difokuskan.
     - navigasi_button_ok_back(halOK, halBack)
       → OK tetap di halaman fokus, BACK kembali ke menu setting utama (7).
     - navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR)
       → pindah fokus antar pompa (7001..7005).

   Catatan:
     - Perubahan status ditampilkan langsung di LCD dan segera
       dieksekusi melalui fungsi update_status_* agar relay sinkron.
     - Pastikan logika relay & wiring (active LOW/HIGH, NC/NO) sesuai
       dengan modul relay yang digunakan (lihat modul driver pompa).

   Tujuan:
     - Memberi kontrol manual cepat untuk tiap pompa.
     - Memudahkan pengetesan perangkat & override di lapangan.
  =========================================================
*/

String txt_status_pompa[2] = { "OFF", "ON " };
void halaman_setting_kontrol_manual() {

  HALAMAN_AKHIR = 7005;
  HALAMAN_AWAL = 7001;

  if (halaman == 7001) {
    lcd.setCursor(0, 0);
    lcd.print("Set Pompa:");
    lcd.setCursor(0, 1);
    lcd.printf(">Air:%s   PHU:%s", txt_status_pompa[set_status_pompa_air], txt_status_pompa[set_status_pompa_phu]);
    lcd.setCursor(0, 2);
    lcd.printf(" NA :%s   PHD:%s", txt_status_pompa[set_status_pompa_na], txt_status_pompa[set_status_pompa_phd]);
    lcd.setCursor(0, 3);
    lcd.printf(" NB :%s", txt_status_pompa[set_status_pompa_nb]);

    navigasi_button_value(set_status_pompa_air, 1, 0, 1);
    navigasi_button_ok_back(7001, 7);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
    update_status_pompa_air();
  }

  if (halaman == 7002) {
    lcd.setCursor(0, 0);
    lcd.print("Set Pompa:");
    lcd.setCursor(0, 1);
    lcd.printf(" Air:%s   PHU:%s", txt_status_pompa[set_status_pompa_air], txt_status_pompa[set_status_pompa_phu]);
    lcd.setCursor(0, 2);
    lcd.printf(">NA :%s   PHD:%s", txt_status_pompa[set_status_pompa_na], txt_status_pompa[set_status_pompa_phd]);
    lcd.setCursor(0, 3);
    lcd.printf(" NB :%s", txt_status_pompa[set_status_pompa_nb]);

    navigasi_button_value(set_status_pompa_na, 1, 0, 1);
    navigasi_button_ok_back(7002, 7);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
    update_status_pompa_nutrisi();
  }

  if (halaman == 7003) {
    lcd.setCursor(0, 0);
    lcd.print("Set Pompa:");
    lcd.setCursor(0, 1);
    lcd.printf(" Air:%s   PHU:%s", txt_status_pompa[set_status_pompa_air], txt_status_pompa[set_status_pompa_phu]);
    lcd.setCursor(0, 2);
    lcd.printf(" NA :%s   PHD:%s", txt_status_pompa[set_status_pompa_na], txt_status_pompa[set_status_pompa_phd]);
    lcd.setCursor(0, 3);
    lcd.printf(">NB :%s", txt_status_pompa[set_status_pompa_nb]);

    navigasi_button_value(set_status_pompa_nb, 1, 0, 1);
    navigasi_button_ok_back(7003, 7);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
    update_status_pompa_nutrisi();
  }
  if (halaman == 7004) {
    lcd.setCursor(0, 0);
    lcd.print("Set Pompa:");
    lcd.setCursor(0, 1);
    lcd.printf(" Air:%s  >PHU:%s", txt_status_pompa[set_status_pompa_air], txt_status_pompa[set_status_pompa_phu]);
    lcd.setCursor(0, 2);
    lcd.printf(" NA :%s   PHD:%s", txt_status_pompa[set_status_pompa_na], txt_status_pompa[set_status_pompa_phd]);
    lcd.setCursor(0, 3);
    lcd.printf(" NB :%s", txt_status_pompa[set_status_pompa_nb]);

    navigasi_button_value(set_status_pompa_phu, 1, 0, 1);
    navigasi_button_ok_back(7004, 7);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
    update_status_pompa_nutrisi();
  }
  if (halaman == 7005) {
    lcd.setCursor(0, 0);
    lcd.print("Set Pompa:");
    lcd.setCursor(0, 1);
    lcd.printf(" Air:%s   PHU:%s", txt_status_pompa[set_status_pompa_air], txt_status_pompa[set_status_pompa_phu]);
    lcd.setCursor(0, 2);
    lcd.printf(" NA :%s  >PHD:%s", txt_status_pompa[set_status_pompa_na], txt_status_pompa[set_status_pompa_phd]);
    lcd.setCursor(0, 3);
    lcd.printf(" NB :%s", txt_status_pompa[set_status_pompa_nb]);

    navigasi_button_value(set_status_pompa_phd, 1, 0, 1);
    navigasi_button_ok_back(7005, 7);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
    update_status_pompa_nutrisi();
  }
}
