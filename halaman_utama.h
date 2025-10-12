/*
  =========================================================
   Modul : Halaman Utama LCD
   Author: shmukti

   Deskripsi:
     - Halaman utama (halaman = 0) untuk menampilkan 
       informasi sensor dan status sistem pada LCD.
     - Menyediakan ringkasan real-time kondisi hidroponik:
       * TDS, pH, suhu air, suhu udara, kelembaban udara.
       * Status WiFi & MQTT.
       * Waktu & tanggal (RTC DS3231).

   Variabel:
     - nama_hari[8] : array nama singkat hari 
       { "Er", "Sn", "Sl", "Rb", "Km", "Jm", "Sb", "Mn" }
         * 0 = Er (dummy / error fallback)
         * 1 = Senin, 2 = Selasa, ..., 7 = Minggu
     - halaman       : penanda halaman aktif (int)
     - now           : objek DateTime dari rtc.now()

   Alur fungsi:
     1. Jika halaman == 0:
        - Ambil waktu sekarang dari RTC.
        - Update sensor (DHT11, DS18B20, TDS).
        - Tampilkan data ke LCD 20x4:
            Baris 0: "TDS:xxxxppm" | Status WiFi/MQTT ("W"=OK, "X"=Error)
            Baris 1: "PH:xx"       | Suhu Air (xx °C)
            Baris 2: Suhu Udara (xx °C) | Kelembaban (xx %)
            Baris 3: Hari, tanggal/bulan/tahun & jam:menit:detik
        - Simbol derajat (°) ditampilkan dengan `lcd.print(char(223));`

     2. Jika tombol OK (BTN_OK) ditekan:
        - LCD di-clear.
        - halaman diganti ke 1 (menu berikutnya).
        - Bunyi beep() sebagai feedback.

   Catatan:
     - Format WiFi/MQTT status:
         * WiFi.status() == WL_CONNECTED ? "W" : "X"
         * mqtt.connected() ? "M" : "X"
         → tampil di LCD: contoh "WiFi:WM" (WiFi OK, MQTT OK).
     - nilai_tds, nilai_ph, nilai_suhu_air, nilai_suhu_udara,
       nilai_kelembaban_udara diperbarui dari driver sensor.
     - Hari ke dari RTC:
         * dayOfTheWeek(): 0 = Sunday → di-offset agar cocok 
           dengan array nama_hari[].

   Tujuan:
     - Memberikan ringkasan sistem di halaman utama.
     - Memudahkan user untuk melihat kondisi sensor 
       dan status koneksi dengan cepat.
     - Menjadi pintu masuk ke menu pengaturan (tekan tombol OK).

  =========================================================
*/

String nama_hari[8] = { "Er", "Sn", "Sl", "Rb", "Km", "Jm", "Sb", "Mn" };

void halaman_utama() {

  if (halaman == 0) {

    DateTime now = rtc.now();

    update_sensor_dht();
    update_sensor_suhu_air();
    update_sensor_tds();
    update_sensor_ph();

    lcd.setCursor(0, 0);
    lcd.printf("TDS:%.4dppm",nilai_tds);
    lcd.setCursor(13, 0);
    lcd.printf("WiFi:%S%S", WiFi.status() == WL_CONNECTED ? "W" : "X", mqtt.connected() ? "M" : "X");
    lcd.setCursor(0, 1);
    lcd.printf("PH :%.2d", nilai_ph);
    lcd.setCursor(10, 1);
    lcd.printf("T.Air:%2d", nilai_suhu_air);

    lcd.print(char(223));
    lcd.print("C");
    lcd.setCursor(0, 2);
    lcd.printf("Tem:%2d", nilai_suhu_udara);
    lcd.print(char(223));
    lcd.print("C");
    lcd.setCursor(10, 2);
    lcd.printf("Humy :%2d", nilai_kelembaban_udara);
    lcd.print("%");

    lcd.setCursor(0, 3);
    int hari_ke = now.dayOfTheWeek();
    lcd.print(nama_hari[hari_ke]);
    lcd.printf(",%.2d/%.2d/%.2d %.2d:%.2d:%.2d", now.day(), now.month(), now.year() - 2000, now.hour(), now.minute(), now.second());

    if (BTN_OK) {
      lcd.clear();
      halaman = 1;
      beep();
    }
  }
}