/*
  =========================================================
   Modul : Halaman Setting Jadwal Detail
   Author: shmukti

   Deskripsi:
     - Modul ini mengatur detail jadwal berdasarkan index_jadwal (0–4).
     - Setiap jadwal bisa diaktifkan/nonaktifkan, diatur hari, jam, 
       kondisi TDS/PH, serta aksi pompa dengan durasi.
     - Navigasi berbasis multi-halaman (1101..1902).

   Variabel:
     - index_jadwal : indeks jadwal aktif (0–4).
     - txt_on_off[] : representasi status ON/OFF.
     - txt_operasi[]: simbol operasi pembanding ("<", ">", "=").
     - kode_hari()  : helper untuk menampilkan singkatan hari aktif.
     - jadwal_xxx[] : array konfigurasi (status, jam, limit, pompa, dsb).

   Alur Fungsi (ringkas):
     1. Halaman 1101–1109 → Ringkasan kondisi jadwal
        - 1101 : status ON/OFF
        - 1102 : pemilihan hari aktif
        - 1103 : jam/menit/detik
        - 1104 : kondisi TDS
        - 1105 : kondisi PH
        - 1106–1109 : aksi pompa (NA, NB, PHU, PHD)

     2. Halaman 1201–1207 → Pilihan hari (Senin–Minggu)
        - Toggle tiap hari (0/1).
        - Navigasi per-hari dengan tombol UP/DOWN.

     3. Halaman 1301–1303 → Jam, Menit, Detik
        - Atur waktu eksekusi jadwal (0–23 jam, 0–59 menit/detik).

     4. Halaman 1401–1403 → Kondisi TDS
        - 1401 : aktif/diabaikan
        - 1402 : limit TDS (ppm, 0–2000)
        - 1403 : operator (<, >, =)

     5. Halaman 1501–1503 → Kondisi PH
        - 1501 : aktif/diabaikan
        - 1502 : limit PH (0–10)
        - 1503 : operator (<, >, =)

     6. Halaman 1601–1902 → Kontrol pompa
        - 1601–1602 : Pompa NA (ON/OFF, durasi 0–600s)
        - 1701–1702 : Pompa NB
        - 1801–1802 : Pompa PHU
        - 1901–1902 : Pompa PHD

   Navigasi:
     - navigasi_button_ok_back(nextHalaman, backHalaman)
       → Tombol OK lanjut ke halaman detail berikutnya,
         Tombol BACK kembali ke halaman ringkasan (100x/110x).
     - navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR)
       → pindah antar sub-menu dalam kategori.
     - navigasi_button_value(var, step, min, max)
       → mengubah nilai variabel dengan tombol VALUE UP/DOWN.

   Catatan:
     - Struktur halaman dibuat bertingkat:
       * 110x = ringkasan jadwal
       * 120x = setting hari
       * 130x = setting jam/menit/detik
       * 140x–150x = kondisi sensor
       * 160x–190x = aksi pompa
     - Semua nilai disimpan ke variabel global,
       dan akan dipermanenkan via simpan_memory().
     - Tampilan LCD 20x4 dimanfaatkan maksimal
       untuk ringkasan informasi (hari, waktu, kondisi, aksi).
     - txt_on_off dan txt_operasi memudahkan display status.

   Tujuan:
     - Memberikan antarmuka detail untuk pengaturan jadwal
       hidroponik berbasis RTC, TDS, PH, dan pompa.
     - Menyediakan kontrol penuh agar jadwal lebih fleksibel:
       bisa berdasarkan waktu, kondisi sensor, dan pompa tertentu.

   Peningkatan yang bisa dilakukan:
     - Highlight tampilan lebih jelas (misal blink di item aktif).
     - Non-blocking delay saat simulasi eksekusi jadwal.
     - Optimasi navigasi agar tidak terlalu banyak halaman.

  =========================================================
*/

String txt_operasi[3] = { "<", ">", "=" };

String kode_hari(int index_jadwal) {
  String txt = "";
  if (jadwal_hari_senin[index_jadwal]) {
    txt.concat("S");
  } else {
    txt.concat(" ");
  }
  if (jadwal_hari_selasa[index_jadwal]) {
    txt.concat("S");
  } else {
    txt.concat(" ");
  }
  if (jadwal_hari_rabu[index_jadwal]) {
    txt.concat("R");
  } else {
    txt.concat(" ");
  }
  if (jadwal_hari_kamis[index_jadwal]) {
    txt.concat("K");
  } else {
    txt.concat(" ");
  }
  if (jadwal_hari_jumat[index_jadwal]) {
    txt.concat("J");
  } else {
    txt.concat(" ");
  }
  if (jadwal_hari_sabtu[index_jadwal]) {
    txt.concat("S");
  } else {
    txt.concat(" ");
  }
  if (jadwal_hari_minggu[index_jadwal]) {
    txt.concat("M");
  } else {
    txt.concat(" ");
  }
  return txt;
};

void halaman_setting_jadwal_detail() {
  HALAMAN_AWAL = 1101;
  HALAMAN_AKHIR = 1109;

  if (halaman == 1101) {
    lcd.setCursor(0, 0);
    lcd.printf(">set  Jadwal %d:%S", index_jadwal + 1, txt_on_off[jadwal_status[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(" tiap Hari (%S)", kode_hari(index_jadwal));
    lcd.setCursor(0, 2);
    lcd.printf(" tiap Jam (%.2d:%.2d:%.2d)", jadwal_jam[index_jadwal], jadwal_menit[index_jadwal], jadwal_detik[index_jadwal]);
    lcd.setCursor(0, 3);
    if (jadwal_status_tds[index_jadwal] == 0) {
      lcd.print(" jika TDS diabaikan");
    } else {
      lcd.printf(" jika TDS %s %.4dppm", txt_operasi[jadwal_operasi_tds[index_jadwal]], jadwal_limit_tds[index_jadwal]);
    }
    navigasi_button_value(jadwal_status[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1101, 1001);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1102) {
    lcd.setCursor(0, 0);
    lcd.printf(" set  Jadwal %d:%S", index_jadwal + 1, txt_on_off[jadwal_status[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(">tiap Hari (%S)", kode_hari(index_jadwal));
    lcd.setCursor(0, 2);
    lcd.printf(" tiap Jam (%.2d:%.2d:%.2d)", jadwal_jam[index_jadwal], jadwal_menit[index_jadwal], jadwal_detik[index_jadwal]);
    lcd.setCursor(0, 3);
    if (jadwal_status_tds[index_jadwal] == 0) {
      lcd.print(" jika TDS diabaikan");
    } else {
      lcd.printf(" jika TDS %s %.4dppm", txt_operasi[jadwal_operasi_tds[index_jadwal]], jadwal_limit_tds[index_jadwal]);
    }
    navigasi_button_ok_back(1202, 1001);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1103) {
    lcd.setCursor(0, 0);
    lcd.printf(" set  Jadwal %d:%S", index_jadwal + 1, txt_on_off[jadwal_status[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(" tiap Hari (%S)", kode_hari(index_jadwal));
    lcd.setCursor(0, 2);
    lcd.printf(">tiap Jam (%.2d:%.2d:%.2d)", jadwal_jam[index_jadwal], jadwal_menit[index_jadwal], jadwal_detik[index_jadwal]);
    lcd.setCursor(0, 3);
    if (jadwal_status_tds[index_jadwal] == 0) {
      lcd.print(" jika TDS diabaikan");
    } else {
      lcd.printf(" jika TDS %s %.4dppm", txt_operasi[jadwal_operasi_tds[index_jadwal]], jadwal_limit_tds[index_jadwal]);
    }
    navigasi_button_ok_back(1301, 1001);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1104) {
    lcd.setCursor(0, 0);
    lcd.printf(" set  Jadwal %d:%S", index_jadwal + 1, txt_on_off[jadwal_status[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(" tiap Hari (%S)", kode_hari(index_jadwal));
    lcd.setCursor(0, 2);
    lcd.printf(" tiap Jam (%.2d:%.2d:%.2d)", jadwal_jam[index_jadwal], jadwal_menit[index_jadwal], jadwal_detik[index_jadwal]);
    lcd.setCursor(0, 3);
    if (jadwal_status_tds[index_jadwal] == 0) {
      lcd.print(">jika TDS diabaikan");
    } else {
      lcd.printf(">jika TDS %s %.4dppm", txt_operasi[jadwal_operasi_tds[index_jadwal]], jadwal_limit_tds[index_jadwal]);
    }
    navigasi_button_ok_back(1401, 1001);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1105) {
    lcd.setCursor(0, 0);
    lcd.printf(" tiap Hari (%S)", kode_hari(index_jadwal));
    lcd.setCursor(0, 1);
    lcd.printf(" tiap Jam (%.2d:%.2d:%.2d)", jadwal_jam[index_jadwal], jadwal_menit[index_jadwal], jadwal_detik[index_jadwal]);
    lcd.setCursor(0, 2);
    if (jadwal_status_tds[index_jadwal] == 0) {
      lcd.print(" jika TDS diabaikan");
    } else {
      lcd.printf(" jika TDS %s %.4dppm", txt_operasi[jadwal_operasi_tds[index_jadwal]], jadwal_limit_tds[index_jadwal]);
    }
    lcd.setCursor(0, 3);
    if (jadwal_status_ph[index_jadwal] == 0) {
      lcd.print(">jika PH  diabaikan");
    } else {
      lcd.printf(">jika PH  %s %.2d", txt_operasi[jadwal_operasi_ph[index_jadwal]], jadwal_limit_ph[index_jadwal]);
    }
    navigasi_button_ok_back(1501, 1001);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1106) {
    lcd.setCursor(0, 0);
    lcd.printf(" tiap Jam (%.2d:%.2d:%.2d)", jadwal_jam[index_jadwal], jadwal_menit[index_jadwal], jadwal_detik[index_jadwal]);
    lcd.setCursor(0, 1);
    if (jadwal_status_tds[index_jadwal] == 0) {
      lcd.print(" jika TDS diabaikan");
    } else {
      lcd.printf(" jika TDS %s %.2d", txt_operasi[jadwal_operasi_tds[index_jadwal]], jadwal_limit_tds[index_jadwal]);
    }
    lcd.setCursor(0, 2);
    if (jadwal_status_ph[index_jadwal] == 0) {
      lcd.print(" jika PH  diabaikan");
    } else {
      lcd.printf(" jika PH  %s %.2d", txt_operasi[jadwal_operasi_ph[index_jadwal]], jadwal_limit_ph[index_jadwal]);
    }
    lcd.setCursor(0, 3);
    lcd.printf(">maka NA  %S %.3d S", txt_on_off[jadwal_set_pompa_na[index_jadwal]], jadwal_timer_pompa_na[index_jadwal]);
    navigasi_button_ok_back(1601, 1001);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1107) {
    lcd.setCursor(0, 0);
    if (jadwal_status_tds[index_jadwal] == 0) {
      lcd.print(" jika TDS diabaikan");
    } else {
      lcd.printf(" jika TDS %s %.2d", txt_operasi[jadwal_operasi_tds[index_jadwal]], jadwal_limit_tds[index_jadwal]);
    }
    lcd.setCursor(0, 1);
    if (jadwal_status_ph[index_jadwal] == 0) {
      lcd.print(" jika PH  diabaikan");
    } else {
      lcd.printf(" jika PH  %s %.2d", txt_operasi[jadwal_operasi_ph[index_jadwal]], jadwal_limit_ph[index_jadwal]);
    }
    lcd.setCursor(0, 2);
    lcd.printf(" maka NA  %S %.3d S", txt_on_off[jadwal_set_pompa_na[index_jadwal]], jadwal_timer_pompa_na[index_jadwal]);
    lcd.setCursor(0, 3);
    lcd.printf(">maka NB  %S %.3d S", txt_on_off[jadwal_set_pompa_nb[index_jadwal]], jadwal_timer_pompa_nb[index_jadwal]);
    navigasi_button_ok_back(1701, 1001);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1108) {
    lcd.setCursor(0, 0);
    if (jadwal_status_ph[index_jadwal] == 0) {
      lcd.print(" jika PH  diabaikan");
    } else {
      lcd.printf(" jika PH  %s %.2d", txt_operasi[jadwal_operasi_ph[index_jadwal]], jadwal_limit_ph[index_jadwal]);
    }
    lcd.setCursor(0, 1);
    lcd.printf(" maka NA  %S %.3d S", txt_on_off[jadwal_set_pompa_na[index_jadwal]], jadwal_timer_pompa_na[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(" maka NB  %S %.3d S", txt_on_off[jadwal_set_pompa_nb[index_jadwal]], jadwal_timer_pompa_nb[index_jadwal]);
    lcd.setCursor(0, 3);
    lcd.printf(">maka PHU %S %.3d S", txt_on_off[jadwal_set_pompa_phu[index_jadwal]], jadwal_timer_pompa_phu[index_jadwal]);
    navigasi_button_ok_back(1801, 1001);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1109) {
    lcd.setCursor(0, 0);
    lcd.printf(" maka NA  %S %.3d S", txt_on_off[jadwal_set_pompa_na[index_jadwal]], jadwal_timer_pompa_na[index_jadwal]);
    lcd.setCursor(0, 1);
    lcd.printf(" maka NB  %S %.3d S", txt_on_off[jadwal_set_pompa_nb[index_jadwal]], jadwal_timer_pompa_nb[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(" maka PHU %S %.3d S", txt_on_off[jadwal_set_pompa_phu[index_jadwal]], jadwal_timer_pompa_phu[index_jadwal]);
    lcd.setCursor(0, 3);
    lcd.printf(">maka PHD %S %.3d S", txt_on_off[jadwal_set_pompa_phd[index_jadwal]], jadwal_timer_pompa_phd[index_jadwal]);
    navigasi_button_ok_back(1901, 1001);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  HALAMAN_AWAL = 1201;
  HALAMAN_AKHIR = 1207;


  if (halaman == 1201) {
    lcd.setCursor(0, 0);
    lcd.printf(">Senin:%S Jumat:%S",
               txt_on_off[jadwal_hari_senin[index_jadwal]], txt_on_off[jadwal_hari_jumat[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(" Selsa:%S Sabtu:%S",
               txt_on_off[jadwal_hari_selasa[index_jadwal]], txt_on_off[jadwal_hari_sabtu[index_jadwal]]);

    lcd.setCursor(0, 2);
    lcd.printf(" Rabu :%S Mnggu:%S",
               txt_on_off[jadwal_hari_rabu[index_jadwal]], txt_on_off[jadwal_hari_minggu[index_jadwal]]);

    lcd.setCursor(0, 3);
    lcd.printf(" Kamis:%S ", txt_on_off[jadwal_hari_kamis[index_jadwal]]);
    navigasi_button_value(jadwal_hari_senin[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1202, 1102);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1202) {
    lcd.setCursor(0, 0);
    lcd.printf(" Senin:%S Jumat:%S",
               txt_on_off[jadwal_hari_senin[index_jadwal]], txt_on_off[jadwal_hari_jumat[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(">Selsa:%S Sabtu:%S",
               txt_on_off[jadwal_hari_selasa[index_jadwal]], txt_on_off[jadwal_hari_sabtu[index_jadwal]]);

    lcd.setCursor(0, 2);
    lcd.printf(" Rabu :%S Mnggu:%S",
               txt_on_off[jadwal_hari_rabu[index_jadwal]], txt_on_off[jadwal_hari_minggu[index_jadwal]]);

    lcd.setCursor(0, 3);
    lcd.printf(" Kamis:%S ", txt_on_off[jadwal_hari_kamis[index_jadwal]]);
    navigasi_button_value(jadwal_hari_selasa[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1203, 1102);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1203) {
    lcd.setCursor(0, 0);
    lcd.printf(" Senin:%S Jumat:%S",
               txt_on_off[jadwal_hari_senin[index_jadwal]], txt_on_off[jadwal_hari_jumat[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(" Selsa:%S Sabtu:%S",
               txt_on_off[jadwal_hari_selasa[index_jadwal]], txt_on_off[jadwal_hari_sabtu[index_jadwal]]);

    lcd.setCursor(0, 2);
    lcd.printf(">Rabu :%S Mnggu:%S",
               txt_on_off[jadwal_hari_rabu[index_jadwal]], txt_on_off[jadwal_hari_minggu[index_jadwal]]);

    lcd.setCursor(0, 3);
    lcd.printf(" Kamis:%S ", txt_on_off[jadwal_hari_kamis[index_jadwal]]);
    navigasi_button_value(jadwal_hari_rabu[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1204, 1102);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1204) {
    lcd.setCursor(0, 0);
    lcd.printf(" Senin:%S Jumat:%S",
               txt_on_off[jadwal_hari_senin[index_jadwal]], txt_on_off[jadwal_hari_jumat[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(" Selsa:%S Sabtu:%S",
               txt_on_off[jadwal_hari_selasa[index_jadwal]], txt_on_off[jadwal_hari_sabtu[index_jadwal]]);

    lcd.setCursor(0, 2);
    lcd.printf(" Rabu :%S Mnggu:%S",
               txt_on_off[jadwal_hari_rabu[index_jadwal]], txt_on_off[jadwal_hari_minggu[index_jadwal]]);

    lcd.setCursor(0, 3);
    lcd.printf(">Kamis:%S ", txt_on_off[jadwal_hari_kamis[index_jadwal]]);
    navigasi_button_value(jadwal_hari_kamis[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1205, 1102);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1205) {
    lcd.setCursor(0, 0);
    lcd.printf(" Senin:%S>Jumat:%S",
               txt_on_off[jadwal_hari_senin[index_jadwal]], txt_on_off[jadwal_hari_jumat[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(" Selsa:%S Sabtu:%S",
               txt_on_off[jadwal_hari_selasa[index_jadwal]], txt_on_off[jadwal_hari_sabtu[index_jadwal]]);

    lcd.setCursor(0, 2);
    lcd.printf(" Rabu :%S Mnggu:%S",
               txt_on_off[jadwal_hari_rabu[index_jadwal]], txt_on_off[jadwal_hari_minggu[index_jadwal]]);

    lcd.setCursor(0, 3);
    lcd.printf(" Kamis:%S ", txt_on_off[jadwal_hari_kamis[index_jadwal]]);
    navigasi_button_value(jadwal_hari_jumat[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1206, 1102);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1206) {
    lcd.setCursor(0, 0);
    lcd.printf(" Senin:%S Jumat:%S",
               txt_on_off[jadwal_hari_senin[index_jadwal]], txt_on_off[jadwal_hari_jumat[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(" Selsa:%S>Sabtu:%S",
               txt_on_off[jadwal_hari_selasa[index_jadwal]], txt_on_off[jadwal_hari_sabtu[index_jadwal]]);

    lcd.setCursor(0, 2);
    lcd.printf(" Rabu :%S Mnggu:%S",
               txt_on_off[jadwal_hari_rabu[index_jadwal]], txt_on_off[jadwal_hari_minggu[index_jadwal]]);

    lcd.setCursor(0, 3);
    lcd.printf(" Kamis:%S ", txt_on_off[jadwal_hari_kamis[index_jadwal]]);
    navigasi_button_value(jadwal_hari_sabtu[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1207, 1102);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1207) {
    lcd.setCursor(0, 0);
    lcd.printf(">Senin:%S Jumat:%S",
               txt_on_off[jadwal_hari_senin[index_jadwal]], txt_on_off[jadwal_hari_jumat[index_jadwal]]);
    lcd.setCursor(0, 1);
    lcd.printf(" Selsa:%S Sabtu:%S",
               txt_on_off[jadwal_hari_selasa[index_jadwal]], txt_on_off[jadwal_hari_sabtu[index_jadwal]]);

    lcd.setCursor(0, 2);
    lcd.printf(" Rabu :%S>Mnggu:%S",
               txt_on_off[jadwal_hari_rabu[index_jadwal]], txt_on_off[jadwal_hari_minggu[index_jadwal]]);

    lcd.setCursor(0, 3);
    lcd.printf(" Kamis:%S ", txt_on_off[jadwal_hari_kamis[index_jadwal]]);
    navigasi_button_value(jadwal_hari_minggu[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1208, 1102);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  HALAMAN_AWAL = 1301;
  HALAMAN_AKHIR = 1303;

  if (halaman == 1301) {
    lcd.setCursor(0, 0);
    lcd.printf(">Jam  :%.2d", jadwal_jam[index_jadwal]);
    lcd.setCursor(0, 1);
    lcd.printf(" Menit:%.2d", jadwal_menit[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(" Detik:%.2d", jadwal_detik[index_jadwal]);
    navigasi_button_value(jadwal_jam[index_jadwal], 1, 0, 23);
    navigasi_button_ok_back(1301, 1103);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1302) {
    lcd.setCursor(0, 0);
    lcd.printf(" Jam  :%.2d", jadwal_jam[index_jadwal]);
    lcd.setCursor(0, 1);
    lcd.printf(">Menit:%.2d", jadwal_menit[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(" Detik:%.2d", jadwal_detik[index_jadwal]);
    navigasi_button_value(jadwal_menit[index_jadwal], 1, 0, 59);
    navigasi_button_ok_back(1302, 1103);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1303) {
    lcd.setCursor(0, 0);
    lcd.printf(" Jam  :%.2d", jadwal_jam[index_jadwal]);
    lcd.setCursor(0, 1);
    lcd.printf(" Menit:%.2d", jadwal_menit[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(">Detik:%.2d", jadwal_detik[index_jadwal]);
    navigasi_button_value(jadwal_detik[index_jadwal], 1, 0, 59);
    navigasi_button_ok_back(1303, 1103);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }


  HALAMAN_AWAL = 1401;
  HALAMAN_AKHIR = 1403;

  if (halaman == 1401) {
    lcd.setCursor(0, 0);
    lcd.printf(">TDS    :%S", jadwal_status_tds[index_jadwal] ? "ON       " : "Diabaikan");
    lcd.setCursor(0, 1);
    lcd.printf(" Limit  :%.4d ppm", jadwal_limit_tds[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(" Operasi: '%s' ", txt_operasi[jadwal_operasi_tds[index_jadwal]]);
    navigasi_button_value(jadwal_status_tds[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1401, 1104);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1402) {
    lcd.setCursor(0, 0);
    lcd.printf(" TDS    :%S", jadwal_status_tds[index_jadwal] ? "ON       " : "Diabaikan");
    lcd.setCursor(0, 1);
    lcd.printf(">Limit  :%.4d ppm", jadwal_limit_tds[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(" Operasi: '%s'", txt_operasi[jadwal_operasi_tds[index_jadwal]]);
    navigasi_button_value(jadwal_limit_tds[index_jadwal], 5, 0, 2000);
    navigasi_button_ok_back(1402, 1104);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1403) {
    lcd.setCursor(0, 0);
    lcd.printf(" TDS    :%S", jadwal_status_tds[index_jadwal] ? "ON       " : "Diabaikan");
    lcd.setCursor(0, 1);
    lcd.printf(" Limit  :%.4d ppm", jadwal_limit_tds[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(">Operasi: '%s'", txt_operasi[jadwal_operasi_tds[index_jadwal]]);
    navigasi_button_value(jadwal_operasi_tds[index_jadwal], 1, 0, 2);
    navigasi_button_ok_back(1403, 1104);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  HALAMAN_AWAL = 1501;
  HALAMAN_AKHIR = 1503;

  if (halaman == 1501) {
    lcd.setCursor(0, 0);
    lcd.printf(">PH     :%S", jadwal_status_ph[index_jadwal] ? "ON       " : "Diabaikan");
    lcd.setCursor(0, 1);
    lcd.printf(" Limit  :%.2d", jadwal_limit_ph[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(" Operasi: '%s' ", txt_operasi[jadwal_operasi_ph[index_jadwal]]);
    navigasi_button_value(jadwal_status_ph[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1501, 1105);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  if (halaman == 1502) {
    lcd.setCursor(0, 0);
    lcd.printf(" PH     :%S", jadwal_status_ph[index_jadwal] ? "ON       " : "Diabaikan");
    lcd.setCursor(0, 1);
    lcd.printf(">Limit  :%.2d", jadwal_limit_ph[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(" Operasi: '%s' ", txt_operasi[jadwal_operasi_ph[index_jadwal]]);
    navigasi_button_value(jadwal_limit_ph[index_jadwal], 1, 0, 14);
    navigasi_button_ok_back(1502, 1105);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1503) {
    lcd.setCursor(0, 0);
    lcd.printf(" PH     :%S", jadwal_status_ph[index_jadwal] ? "ON       " : "Diabaikan");
    lcd.setCursor(0, 1);
    lcd.printf(" Limit  :%.2d", jadwal_limit_ph[index_jadwal]);
    lcd.setCursor(0, 2);
    lcd.printf(">Operasi: '%s' ", txt_operasi[jadwal_operasi_ph[index_jadwal]]);
    navigasi_button_value(jadwal_operasi_ph[index_jadwal], 1, 0, 14);
    navigasi_button_ok_back(1503, 1105);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  HALAMAN_AWAL = 1601;
  HALAMAN_AKHIR = 1602;

  if (halaman == 1601) {
    lcd.setCursor(0, 0);
    lcd.printf(">POMPA NA:%S", jadwal_set_pompa_na[index_jadwal] ? "ON " : "OFF");
    lcd.setCursor(0, 1);
    lcd.printf(" DURASI  :%.3d S", jadwal_timer_pompa_na[index_jadwal]);
    navigasi_button_value(jadwal_set_pompa_na[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1601, 1106);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1602) {
    lcd.setCursor(0, 0);
    lcd.printf(" POMPA NA:%S", jadwal_set_pompa_na[index_jadwal] ? "ON " : "OFF");
    lcd.setCursor(0, 1);
    lcd.printf(">DURASI  :%.3d S", jadwal_timer_pompa_na[index_jadwal]);
    navigasi_button_value(jadwal_timer_pompa_na[index_jadwal], 1, 0, 600);
    navigasi_button_ok_back(1602, 1106);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  HALAMAN_AWAL = 1701;
  HALAMAN_AKHIR = 1702;

  if (halaman == 1701) {
    lcd.setCursor(0, 0);
    lcd.printf(">POMPA NB:%S", jadwal_set_pompa_nb[index_jadwal] ? "ON " : "OFF");
    lcd.setCursor(0, 1);
    lcd.printf(" DURASI  :%.3d S", jadwal_timer_pompa_nb[index_jadwal]);
    navigasi_button_value(jadwal_set_pompa_nb[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1701, 1107);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1702) {
    lcd.setCursor(0, 0);
    lcd.printf(" POMPA NB:%S", jadwal_set_pompa_nb[index_jadwal] ? "ON " : "OFF");
    lcd.setCursor(0, 1);
    lcd.printf(">DURASI  :%.3d S", jadwal_timer_pompa_nb[index_jadwal]);
    navigasi_button_value(jadwal_timer_pompa_nb[index_jadwal], 1, 0, 600);
    navigasi_button_ok_back(1702, 1107);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  HALAMAN_AWAL = 1801;
  HALAMAN_AKHIR = 1802;

  if (halaman == 1801) {
    lcd.setCursor(0, 0);
    lcd.printf(">POMPA PHU:%S", jadwal_set_pompa_phu[index_jadwal] ? "ON " : "OFF");
    lcd.setCursor(0, 1);
    lcd.printf(" DURASI   :%.3d S", jadwal_timer_pompa_phu[index_jadwal]);
    navigasi_button_value(jadwal_set_pompa_phu[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1801, 1108);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1802) {
    lcd.setCursor(0, 0);
    lcd.printf(" POMPA PHU:%S", jadwal_set_pompa_phu[index_jadwal] ? "ON " : "OFF");
    lcd.setCursor(0, 1);
    lcd.printf(">DURASI   :%.3d S", jadwal_timer_pompa_phu[index_jadwal]);
    navigasi_button_value(jadwal_timer_pompa_phu[index_jadwal], 1, 0, 600);
    navigasi_button_ok_back(1802, 1108);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  HALAMAN_AWAL = 1901;
  HALAMAN_AKHIR = 1902;

  if (halaman == 1901) {
    lcd.setCursor(0, 0);
    lcd.printf(">POMPA PHD:%S", jadwal_set_pompa_phd[index_jadwal] ? "ON " : "OFF");
    lcd.setCursor(0, 1);
    lcd.printf(" DURASI   :%.3d S", jadwal_timer_pompa_phd[index_jadwal]);
    navigasi_button_value(jadwal_set_pompa_phd[index_jadwal], 1, 0, 1);
    navigasi_button_ok_back(1901, 1109);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
  if (halaman == 1902) {
    lcd.setCursor(0, 0);
    lcd.printf(" POMPA PHD:%S", jadwal_set_pompa_phd[index_jadwal] ? "ON " : "OFF");
    lcd.setCursor(0, 1);
    lcd.printf(">DURASI   :%.3d S", jadwal_timer_pompa_phd[index_jadwal]);
    navigasi_button_value(jadwal_timer_pompa_phd[index_jadwal], 1, 0, 600);
    navigasi_button_ok_back(1902, 1109);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
}