/*
  =========================================================
   Fungsi : halaman_setting_telemetry()

   Deskripsi:
     - Menampilkan halaman setting telemetry pada LCD.
     - Memberikan opsi kepada user untuk melihat dan 
       mengubah interval pengiriman data (dalam milidetik).

   Alur utama:
     1. Set variabel HALAMAN_AKHIR dan HALAMAN_AWAL ke 2001.
     2. Jika halaman == 2001:
        - Tampilkan teks "Send Data Every:" pada baris pertama.
        - Tampilkan nilai set_timer_telemetry (ms) pada baris kedua.
        - Navigasi:
            * OK → masuk ke halaman 2101.
            * UP/DOWN → navigasi antar halaman (2001..2001).
     3. Jika halaman == 2101:
        - Panggil input_text_nomor() untuk input angka baru.
        - Jika tombol BACK ditekan:
            * Update nilai timer_telemetry dengan input baru.
            * Kembali ke halaman 2001.
            * Bunyi beep() dan clear LCD.

   Catatan:
     - Variabel global yang dipakai:
         * halaman, HALAMAN_AKHIR, HALAMAN_AWAL
         * set_timer_telemetry (String)
         * timer_telemetry (objek timer dengan reset())
         * BTN_BACK (flag tombol back)
     - Fungsi eksternal yang dipakai:
         * navigasi_button_ok_back()
         * navigasi_button_up_down()
         * input_text_nomor()
         * beep()
     - LCD digunakan untuk menampilkan menu setting.
     - Interval telemetry akan langsung di-reset ketika user 
       selesai menginput nilai baru.

   Author  : shmukti@jogjaprov.go.id
   Whatsapp: shmukti.ichibot.id
  =========================================================
*/

void halaman_setting_telemetry() {

  HALAMAN_AKHIR = 2002;
  HALAMAN_AWAL = 2001;

  if (halaman == 2001) {
    lcd.setCursor(0, 0);
    lcd.print(">Send Data Every:");
    lcd.setCursor(1, 1);
    lcd.print(set_timer_telemetry);
    lcd.print("mS");
    lcd.setCursor(0, 2);
    lcd.print(" Topic Prefix:");
    lcd.setCursor(1, 3);
    lcd.print(set_prefix_telemetry);
    navigasi_button_ok_back(2101, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 2002) {
    lcd.setCursor(0, 0);
    lcd.print(" Send Data Every:");
    lcd.setCursor(1, 1);
    lcd.print(set_timer_telemetry);
    lcd.print("mS");
    lcd.setCursor(0, 2);
    lcd.print(">Topic Prefix:");
    lcd.setCursor(1, 3);
    lcd.print(set_prefix_telemetry);
    navigasi_button_ok_back(2102, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }


  if (halaman == 2101) {
    input_text_nomor("Set Timer(mS):", set_timer_telemetry, 5);
    if (BTN_BACK) {
      timer_telemetry.reset(set_timer_telemetry.toInt(), true);
      halaman = 2001;
      beep();
      lcd.clear();
    }
  }

  if (halaman == 2102) {
    String temp_set_prefix_telemetry = set_prefix_telemetry;
    input_text_alpabet("Topic Prefix:", set_prefix_telemetry, 18);
    if(set_prefix_telemetry!=temp_set_prefix_telemetry){
      simpan_memory();
    }

    if (BTN_BACK) {
      halaman = 2002;
      beep();
      lcd.clear();
    }
  }
}