/*
  =========================================================
   Modul : Kontrol Relay Pompa Nutrisi & pH
   Author: shmukti

   Deskripsi:
     - Modul ini mengatur kendali ON/OFF pompa nutrisi (A & B)
       serta pompa penyesuaian pH (Up & Down) menggunakan relay.
     - Relay dikontrol secara digital, aktif pada logika LOW
       (artinya: LOW = ON, HIGH = OFF).

   Konfigurasi Pin:
     - PIN_RELAY_NA  = GPIO 19 → Pompa Nutrisi A
     - PIN_RELAY_NB  = GPIO 18 → Pompa Nutrisi B
     - PIN_RELAY_PHU = GPIO 17 → Pompa pH Up
     - PIN_RELAY_PHD = GPIO 16 → Pompa pH Down

   Fungsi:
     1. nyalakan_pompa_nutrisi_a() / matikan_pompa_nutrisi_a()
        - Menghidupkan / mematikan Pompa Nutrisi A.
        - Mengubah status_pompa_na dan set_status_pompa_na.

     2. nyalakan_pompa_nutrisi_b() / matikan_pompa_nutrisi_b()
        - Menghidupkan / mematikan Pompa Nutrisi B.
        - Mengubah status_pompa_nb dan set_status_pompa_nb.

     3. nyalakan_pompa_ph_up() / matikan_pompa_ph_up()
        - Menghidupkan / mematikan Pompa pH Up.
        - Mengubah status_pompa_phu dan set_status_pompa_phu.

     4. nyalakan_pompa_ph_down() / matikan_pompa_ph_down()
        - Menghidupkan / mematikan Pompa pH Down.
        - Mengubah status_pompa_phd dan set_status_pompa_phd.

     5. setup_pompa_nutrisi()
        - Dipanggil di setup().
        - Set semua pin relay sebagai OUTPUT.
        - Mematikan semua pompa di awal (relay HIGH).
        - Menampilkan pesan "pompa nutrisi siap digunakan...."
          ke Serial Monitor.

     6. update_status_pompa_nutrisi()
        - Sinkronisasi antara variabel target (set_status_pompa_x)
          dengan status aktual (status_pompa_x).
        - Jika ada perbedaan, panggil fungsi ON/OFF sesuai target.
        - Memastikan perubahan status pompa berjalan konsisten.

   Catatan:
     - Relay modul umumnya aktif LOW, sehingga:
         * digitalWrite(pin, LOW)  = ON (pompa hidup)
         * digitalWrite(pin, HIGH) = OFF (pompa mati)
     - status_pompa_x = kondisi pompa aktual
     - set_status_pompa_x = kondisi target (misalnya dari MQTT/LCD menu)
     - Fungsi update_status_pompa_nutrisi() cocok dipanggil di loop()
       agar setiap perubahan target langsung dieksekusi.

   Tujuan:
     - Mengendalikan pompa nutrisi & pH secara otomatis maupun manual.
     - Menjamin status aktual relay selalu sesuai dengan setpoint
       yang diberikan oleh sistem (menu, jadwal, atau MQTT).

  =========================================================
*/

// Definisi pin relay pompa nutrisi
#define PIN_RELAY_NA 19   // Pompa Nutrisi A
#define PIN_RELAY_NB 18   // Pompa Nutrisi B
#define PIN_RELAY_PHU 17  // Pompa pH Up
#define PIN_RELAY_PHD 16  // Pompa pH Down

void nyalakan_pompa_nutrisi_a() {
  digitalWrite(PIN_RELAY_NA, LOW);
  status_pompa_na = 1;
  set_status_pompa_na = 1;
}
void nyalakan_pompa_nutrisi_b() {
  digitalWrite(PIN_RELAY_NB, LOW);
  status_pompa_nb = 1;
  set_status_pompa_nb = 1;
}
void nyalakan_pompa_ph_up() {
  digitalWrite(PIN_RELAY_PHU, LOW);
  status_pompa_phu = 1;
  set_status_pompa_phu = 1;
}
void nyalakan_pompa_ph_down() {
  digitalWrite(PIN_RELAY_PHD, LOW);
  status_pompa_phd = 1;
  set_status_pompa_phd = 1;
}

void matikan_pompa_nutrisi_a() {
  digitalWrite(PIN_RELAY_NA, HIGH);
  status_pompa_na = 0;
  set_status_pompa_na = 0;
}
void matikan_pompa_nutrisi_b() {
  digitalWrite(PIN_RELAY_NB, HIGH);
  status_pompa_nb = 0;
  set_status_pompa_nb = 0;
}
void matikan_pompa_ph_up() {
  digitalWrite(PIN_RELAY_PHU, HIGH);
  status_pompa_phu = 0;
  set_status_pompa_phu = 0;
}
void matikan_pompa_ph_down() {
  digitalWrite(PIN_RELAY_PHD, HIGH);
  status_pompa_phd = 0;
  set_status_pompa_phd = 0;
}
void setup_pompa_nutrisi() {
  // Set semua pin relay sebagai output
  pinMode(PIN_RELAY_NA, OUTPUT);
  pinMode(PIN_RELAY_NB, OUTPUT);
  pinMode(PIN_RELAY_PHU, OUTPUT);
  pinMode(PIN_RELAY_PHD, OUTPUT);

  // Matikan semua pompa di awal (relay aktif LOW → HIGH = mati)
  matikan_pompa_nutrisi_a();
  matikan_pompa_nutrisi_b();
  matikan_pompa_ph_up();
  matikan_pompa_ph_down();

  Serial.println("pompa nutrisi siap digunakan....");
}
void update_status_pompa_nutrisi() {
  if (set_status_pompa_phd != status_pompa_phd) {
    if (set_status_pompa_phd == 1) {
      nyalakan_pompa_ph_down();
    }
    if (set_status_pompa_phd == 0) {
      matikan_pompa_ph_down();
    }
  }
  if (set_status_pompa_phu != status_pompa_phu) {
    if (set_status_pompa_phu == 1) {
      nyalakan_pompa_ph_up();
    }
    if (set_status_pompa_phu == 0) {
      matikan_pompa_ph_up();
    }
  }
  if (set_status_pompa_na != status_pompa_na) {
    if (set_status_pompa_na == 1) {
      nyalakan_pompa_nutrisi_a();
    }
    if (set_status_pompa_na == 0) {
      matikan_pompa_nutrisi_a();
    }
  }
  if (set_status_pompa_nb != status_pompa_nb) {
    if (set_status_pompa_nb == 1) {
      nyalakan_pompa_nutrisi_b();
    }
    if (set_status_pompa_nb == 0) {
      matikan_pompa_nutrisi_b();
    }
  }
}
