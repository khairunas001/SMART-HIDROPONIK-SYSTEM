/*
  =========================================================
   Modul : Halaman Setting MQTT
   Author: shmukti

   Deskripsi:
     - Halaman ini digunakan untuk mengatur konfigurasi 
       koneksi MQTT (broker & port).
     - User dapat mengubah alamat broker (domain/IP) 
       dan port koneksi melalui input di LCD.

   Variabel:
     - HALAMAN_AWAL  = 4001
     - HALAMAN_AKHIR = 4002
     - set_mqtt_broker : String alamat broker MQTT
     - set_mqtt_port   : String port broker MQTT
     - halaman         : halaman aktif (4001..4102)

   Alur Fungsi:
     1. Halaman 4001 → Broker
        - Menampilkan:
            >Broker:
             [set_mqtt_broker]
             Port:
             [set_mqtt_port]
        - Highlight pada "Broker".
        - Tombol OK → masuk ke halaman 4101 (edit broker).
        - Tombol BACK → kembali ke menu sebelumnya.
        - Tombol UP/DOWN → navigasi ke halaman lain (4001–4002).

     2. Halaman 4002 → Port
        - Menampilkan:
             Broker:
             [set_mqtt_broker]
            >Port:
             [set_mqtt_port]
        - Highlight pada "Port".
        - Tombol OK → masuk ke halaman 4102 (edit port).
        - Navigasi tombol sama dengan 4001.

     3. Halaman 4101 → Input Broker
        - Memanggil fungsi input_text_alpabet("Broker:", set_mqtt_broker, 18).
        - Maksimal panjang broker = 18 karakter.
        - Tombol BACK → kembali ke halaman 4001, beep() → feedback, lcd.clear().

     4. Halaman 4102 → Input Port
        - Memanggil fungsi input_text_nomor("Port:", set_mqtt_port, 4).
        - Maksimal panjang port = 4 digit.
        - Tombol BACK → kembali ke halaman 4002, beep() → feedback, lcd.clear().

   Fungsi eksternal yang dipakai:
     - navigasi_button_ok_back(nextHalaman, backHalaman)
       → tombol OK masuk ke input, tombol BACK kembali.
     - navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR)
       → navigasi menu atas/bawah.
     - input_text_alpabet(label, var, maxLen)
       → input teks alfabet untuk broker.
     - input_text_nomor(label, var, maxLen)
       → input numerik untuk port.
     - beep()
       → bunyi notifikasi saat BACK ditekan.

   Catatan:
     - Nilai broker & port yang baru disimpan ke variabel global 
       set_mqtt_broker & set_mqtt_port.
     - Agar berlaku, fungsi connectMQTT() akan menggunakan nilai ini.
     - Data dapat dipermanenkan ke NVS melalui simpan_memory().
     - Default broker = "broker.mqtt.cool", default port = "1883".

   Tujuan:
     - Memberikan antarmuka pengaturan MQTT langsung di LCD.
     - Memungkinkan user mengganti broker/port tanpa re-flash kode.

  =========================================================
*/

void halaman_setting_mqtt() {

  HALAMAN_AKHIR = 4002;
  HALAMAN_AWAL = 4001;

  if (halaman == 4001) {
    lcd.setCursor(0, 0);
    lcd.print(">Broker:");
    lcd.setCursor(1, 1);
    lcd.print(set_mqtt_broker);
    lcd.setCursor(0, 2);
    lcd.print(" Port:");
    lcd.setCursor(1, 3);
    lcd.print(set_mqtt_port);


    navigasi_button_ok_back(4101, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 4002) {
    lcd.setCursor(0, 0);
    lcd.print(" Broker:");
    lcd.setCursor(1, 1);
    lcd.print(set_mqtt_broker);
    lcd.setCursor(0, 2);
    lcd.print(">Port:");
    lcd.setCursor(1, 3);
    lcd.print(set_mqtt_port);

    navigasi_button_ok_back(4102, 0);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 4101) {
    String temp_set_mqtt_broker = set_mqtt_broker;
    input_text_alpabet("Broker:", set_mqtt_broker, 18);
    if (temp_set_mqtt_broker != set_mqtt_broker) {
      simpan_memory();
    }
    if (BTN_BACK) {
      halaman = 4001;
      beep();
      lcd.clear();
    }
  }
  if (halaman == 4102) {
    String temp_set_mqtt_port = set_mqtt_port;
    input_text_nomor("Port:", set_mqtt_port, 4);
    if (temp_set_mqtt_port != set_mqtt_port) {
      simpan_memory();
    }
    if (BTN_BACK) {
      halaman = 4002;
      beep();
      lcd.clear();
    }
  }
}
