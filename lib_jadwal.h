/*
  =========================================================
   Fungsi : loop_jadwal()
   Library: RTClib (untuk RTC DS3231/DS1307)

   Deskripsi:
     Fungsi ini menjalankan sistem penjadwalan otomatis 
     berdasarkan waktu RTC (jam, menit, detik) dan kondisi 
     sensor (TDS, pH). Jika jadwal aktif sesuai hari & waktu,
     maka pompa nutrisi/pH akan dinyalakan atau dimatikan.

   Alur utama:
     1. Ambil waktu saat ini dari RTC (now).
     2. Tentukan hari dalam seminggu (Senin–Minggu).
     3. Untuk setiap index jadwal (0..JUMLAH_JADWAL-1):
        - Periksa apakah jadwal aktif (jadwal_status).
        - Periksa apakah hari ini sesuai setting 
          (jadwal_hari_senin .. jadwal_hari_minggu).
        - Cocokkan jam, menit, detik dengan RTC.
        - Periksa kondisi sensor TDS/pH bila diaktifkan:
            * operasi_tds / operasi_ph:
                0 = lebih kecil dari limit
                1 = lebih besar dari limit
                2 = sama dengan limit
        - Jika semua kondisi terpenuhi → eksekusi jadwal.
     4. Eksekusi jadwal berupa:
        - Menyalakan / mematikan pompa nutrisi A & B.
        - Menyalakan / mematikan pompa pH UP & pH DOWN.
        - Menampilkan status di LCD (pesan + durasi).
        - Menjalankan pompa selama durasi (detik → ms).
        - Mematikan pompa kembali setelah delay selesai.

   Catatan:
     - lcd digunakan untuk menampilkan informasi status.
     - nilai_tds dan nilai_ph diasumsikan tersedia dari sensor.
     - Fungsi eksternal nyalakan_pompa_xx() dan matikan_pompa_xx()
       dipanggil untuk kontrol pompa.
     - Delay blocking digunakan (bisa diganti millis() untuk non-blocking).

   Author  : shmukti@jogjaprov.go.id
   Whatsapp: shmukti.ichibot.id
  =========================================================
*/

#include "RTClib.h"
void loop_jadwal() {
  int ada_jadwal = 0;
  DateTime now = rtc.now();
  //cek jadwal
  int hari_ini = now.dayOfTheWeek();
  for (int i = 0; i < JUMLAH_JADWAL; i++) {
    if (jadwal_status[i] == 1) {
      if (hari_ini == 1) {
        if (jadwal_hari_senin[i] == 1) {
          ada_jadwal = 1;
        }
      }
      if (hari_ini == 2) {
        if (jadwal_hari_selasa[i] == 1) {
          ada_jadwal = 1;
        }
      }
      if (hari_ini == 3) {
        if (jadwal_hari_rabu[i] == 1) {
          ada_jadwal = 1;
        }
      }
      if (hari_ini == 4) {
        if (jadwal_hari_kamis[i] == 1) {
          ada_jadwal = 1;
        }
      }
      if (hari_ini == 5) {
        if (jadwal_hari_jumat[i] == 1) {
          ada_jadwal = 1;
        }
      }
      if (hari_ini == 6) {
        if (jadwal_hari_sabtu[i] == 1) {
          ada_jadwal = 1;
        }
      }
      if (hari_ini == 7) {
        if (jadwal_hari_minggu[i] == 1) {
          ada_jadwal = 1;
        }
      }
    }

    if (ada_jadwal == 1) {
      ada_jadwal = 0;
      if (jadwal_jam[i] == now.hour()) {
        if (jadwal_menit[i] == now.minute()) {
          if (jadwal_detik[i] == now.second()) {
            //eksekusi jadwal
            ada_jadwal = 1;
          }
        }
      }
    }
    if (ada_jadwal == 1) {
      ada_jadwal = 0;
      if (jadwal_status_tds[i] == 1) {
        if (jadwal_operasi_tds[i] == 0) {
          if (nilai_tds < jadwal_limit_tds[i]) {
            ada_jadwal = 1;
          }
        }
        if (jadwal_operasi_tds[i] == 1) {
          if (nilai_tds > jadwal_limit_tds[i]) {
            ada_jadwal = 1;
          }
        }
        if (jadwal_operasi_tds[i] == 2) {
          if (nilai_tds == jadwal_limit_tds[i]) {
            ada_jadwal = 1;
          }
        }
      } else {
        ada_jadwal = 1;
      }
    }
    if (ada_jadwal == 1) {
      ada_jadwal = 0;
      if (jadwal_status_ph[i] == 1) {
        if (jadwal_operasi_ph[i] == 0) {
          if (nilai_ph < jadwal_limit_ph[i]) {
            ada_jadwal = 1;
          }
        }
        if (jadwal_operasi_ph[i] == 1) {
          if (nilai_ph > jadwal_limit_ph[i]) {
            ada_jadwal = 1;
          }
        }
        if (jadwal_operasi_ph[i] == 2) {
          if (nilai_ph == jadwal_limit_ph[i]) {
            ada_jadwal = 1;
          }
        }
      } else {
        ada_jadwal = 1;
      }
    }

    if (ada_jadwal == 1) {
      if (jadwal_set_pompa_na[i] == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pompa nutrisi A ON!");
        lcd.setCursor(0, 1);
        lcd.printf("Selama %d S", jadwal_timer_pompa_na[i]);
        nyalakan_pompa_nutrisi_a();
        long int duration = jadwal_timer_pompa_na[i] * 1000;
        delay(duration);
        matikan_pompa_nutrisi_a();
        lcd.clear();
      }
      if (jadwal_set_pompa_nb[i] == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pompa nutrisi B ON!");
        lcd.setCursor(0, 1);
        lcd.printf("Selama %d S", jadwal_timer_pompa_nb[i]);
        nyalakan_pompa_nutrisi_b();
        long int duration = jadwal_timer_pompa_nb[i] * 1000;
        delay(duration);
        matikan_pompa_nutrisi_b();
        lcd.clear();
      }
      if (jadwal_set_pompa_phu[i] == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pompa PH UP ON!");
        lcd.setCursor(0, 1);
        lcd.printf("Selama %d S", jadwal_timer_pompa_phu[i]);
        nyalakan_pompa_ph_up();
        long int duration = jadwal_timer_pompa_phu[i] * 1000;
        delay(duration);
        matikan_pompa_ph_up();
        lcd.clear();
      }
      if (jadwal_set_pompa_phd[i] == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pompa PH DOWN ON!");
        lcd.setCursor(0, 1);
        lcd.printf("Selama %d S", jadwal_timer_pompa_phd[i]);
        nyalakan_pompa_ph_down();
        long int duration = jadwal_timer_pompa_phd[i] * 1000;
        delay(duration);
        matikan_pompa_ph_down();
        lcd.clear();
      }

      if (jadwal_set_pompa_na[i] == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pompa nutrisi A OFF!");
        lcd.setCursor(0, 1);
        lcd.printf("Selama %d S", jadwal_timer_pompa_na[i]);

        matikan_pompa_nutrisi_a();
        long int duration = jadwal_timer_pompa_na[i] * 1000;
        delay(duration);
        lcd.clear();
      }
      if (jadwal_set_pompa_nb[i] == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pompa nutrisi B OFF!");
        lcd.setCursor(0, 1);
        lcd.printf("Selama %d S", jadwal_timer_pompa_nb[i]);

        matikan_pompa_nutrisi_b();
        long int duration = jadwal_timer_pompa_nb[i] * 1000;
        delay(duration);
        lcd.clear();
      }
      if (jadwal_set_pompa_phu[i] == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pompa PH UP OFF!");
        lcd.setCursor(0, 1);
        lcd.printf("Selama %d S", jadwal_timer_pompa_phu[i]);

        matikan_pompa_ph_up();
        long int duration = jadwal_timer_pompa_phu[i] * 1000;
        delay(duration);
        lcd.clear();
      }
      if (jadwal_set_pompa_phd[i] == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pompa PH DOWN OFF!");
        lcd.setCursor(0, 1);
        lcd.printf("Selama %d S", jadwal_timer_pompa_phd[i]);
        matikan_pompa_ph_down();
        long int duration = jadwal_timer_pompa_phd[i] * 1000;
        delay(duration);
        lcd.clear();
      }
    }
  }
}
