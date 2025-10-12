/*
  =========================================================
   Project : ESP32 Konfigurasi + Jadwal dengan NVS Storage
   Author  : shmukti@jogjaprov.go.id
   Whatsapp: shmukti.ichibot.id
   Deskripsi:
     - Menyimpan konfigurasi MQTT, WiFi, dan timer telemetry
       ke dalam memory NVS (Non-Volatile Storage) ESP32.
     - Data tetap tersimpan walaupun ESP32 di-reset / power off.
     - Variabel utama:
         * set_mqtt_broker
         * set_mqtt_port
         * set_wifi_ssid
         * set_wifi_password
         * set_timer_telemetry
     - Variabel jadwal (array dengan JUMLAH_JADWAL):
         * jadwal_status
         * jadwal_hari_senin ... jadwal_hari_minggu
         * jadwal_jam, jadwal_menit, jadwal_detik
         * jadwal_limit_tds, jadwal_status_tds, jadwal_operasi_tds
         * jadwal_status_ph, jadwal_limit_ph, jadwal_operasi_ph
         * jadwal_timer_pompa_na, nb, phu, phd
         * jadwal_set_pompa_na, nb, phu, phd
     - Fungsi utama:
         * baca_memory()   -> membaca konfigurasi & jadwal dari NVS
         * simpan_memory() -> menyimpan konfigurasi & jadwal ke NVS
                            (hanya jika ada perubahan data)
  =========================================================
*/


#include <Preferences.h>

Preferences preferences;


// === Fungsi untuk baca memory (ambil dari flash/NVS) ===
void baca_memory() {
  preferences.begin("config", false);

  set_mqtt_broker = preferences.getString("mqtt_broker", set_mqtt_broker);
  set_mqtt_port = preferences.getString("mqtt_port", set_mqtt_port);
  set_wifi_ssid = preferences.getString("wifi_ssid", set_wifi_ssid);
  set_wifi_password = preferences.getString("wifi_pass", set_wifi_password);
  set_timer_telemetry = preferences.getString("timer_tel", set_timer_telemetry);
  set_prefix_telemetry = preferences.getString("prefix_tel", set_prefix_telemetry);
  // --- variabel jadwal ---
  for (int i = 0; i < JUMLAH_JADWAL; i++) {
    jadwal_status[i] = preferences.getInt(("jadwal_status_" + String(i)).c_str(), jadwal_status[i]);
    jadwal_hari_senin[i] = preferences.getInt(("jadwal_senin_" + String(i)).c_str(), jadwal_hari_senin[i]);
    jadwal_hari_selasa[i] = preferences.getInt(("jadwal_selasa_" + String(i)).c_str(), jadwal_hari_selasa[i]);
    jadwal_hari_rabu[i] = preferences.getInt(("jadwal_rabu_" + String(i)).c_str(), jadwal_hari_rabu[i]);
    jadwal_hari_kamis[i] = preferences.getInt(("jadwal_kamis_" + String(i)).c_str(), jadwal_hari_kamis[i]);
    jadwal_hari_jumat[i] = preferences.getInt(("jadwal_jumat_" + String(i)).c_str(), jadwal_hari_jumat[i]);
    jadwal_hari_sabtu[i] = preferences.getInt(("jadwal_sabtu_" + String(i)).c_str(), jadwal_hari_sabtu[i]);
    jadwal_hari_minggu[i] = preferences.getInt(("jadwal_minggu_" + String(i)).c_str(), jadwal_hari_minggu[i]);

    jadwal_jam[i] = preferences.getInt(("jadwal_jam_" + String(i)).c_str(), jadwal_jam[i]);
    jadwal_menit[i] = preferences.getInt(("jadwal_menit_" + String(i)).c_str(), jadwal_menit[i]);
    jadwal_detik[i] = preferences.getInt(("jadwal_detik_" + String(i)).c_str(), jadwal_detik[i]);

    jadwal_limit_tds[i] = preferences.getInt(("jadwal_lim_tds_" + String(i)).c_str(), jadwal_limit_tds[i]);
    jadwal_status_tds[i] = preferences.getInt(("jadwal_sts_tds_" + String(i)).c_str(), jadwal_status_tds[i]);
    jadwal_operasi_tds[i] = preferences.getInt(("jadwal_ops_tds_" + String(i)).c_str(), jadwal_operasi_tds[i]);

    jadwal_status_ph[i] = preferences.getInt(("jadwal_sts_ph_" + String(i)).c_str(), jadwal_status_ph[i]);
    jadwal_limit_ph[i] = preferences.getInt(("jadwal_lim_ph_" + String(i)).c_str(), jadwal_limit_ph[i]);
    jadwal_operasi_ph[i] = preferences.getInt(("jadwal_ops_ph_" + String(i)).c_str(), jadwal_operasi_ph[i]);

    jadwal_timer_pompa_na[i] = preferences.getInt(("jadwal_tmr_na_" + String(i)).c_str(), jadwal_timer_pompa_na[i]);
    jadwal_timer_pompa_nb[i] = preferences.getInt(("jadwal_tmr_nb_" + String(i)).c_str(), jadwal_timer_pompa_nb[i]);
    jadwal_timer_pompa_phu[i] = preferences.getInt(("jadwal_tmr_phu_" + String(i)).c_str(), jadwal_timer_pompa_phu[i]);
    jadwal_timer_pompa_phd[i] = preferences.getInt(("jadwal_tmr_phd_" + String(i)).c_str(), jadwal_timer_pompa_phd[i]);

    jadwal_set_pompa_na[i] = preferences.getInt(("jadwal_set_na_" + String(i)).c_str(), jadwal_set_pompa_na[i]);
    jadwal_set_pompa_nb[i] = preferences.getInt(("jadwal_set_nb_" + String(i)).c_str(), jadwal_set_pompa_nb[i]);
    jadwal_set_pompa_phu[i] = preferences.getInt(("jadwal_set_phu_" + String(i)).c_str(), jadwal_set_pompa_phu[i]);
    jadwal_set_pompa_phd[i] = preferences.getInt(("jadwal_set_phd_" + String(i)).c_str(), jadwal_set_pompa_phd[i]);


    preferences.end();

    Serial.println("=== Konfigurasi dibaca dari memory ===");
  }
}

// === Fungsi untuk simpan memory (hanya kalau beda) ===
void simpan_memory() {
  preferences.begin("config", false);

  if (preferences.getString("mqtt_broker", "") != set_mqtt_broker) {
    preferences.putString("mqtt_broker", set_mqtt_broker);
    Serial.println("Update broker: " + set_mqtt_broker);
  }

  if (preferences.getString("mqtt_port", "") != set_mqtt_port) {
    preferences.putString("mqtt_port", set_mqtt_port);
    Serial.println("Update port: " + set_mqtt_port);
  }

  if (preferences.getString("wifi_ssid", "") != set_wifi_ssid) {
    preferences.putString("wifi_ssid", set_wifi_ssid);
    Serial.println("Update SSID: " + set_wifi_ssid);
  }

  if (preferences.getString("wifi_pass", "") != set_wifi_password) {
    preferences.putString("wifi_pass", set_wifi_password);
    Serial.println("Update Password: " + set_wifi_password);
  }

  if (preferences.getString("timer_tel", "") != set_timer_telemetry) {
    preferences.putString("timer_tel", set_timer_telemetry);
    Serial.println("Update Timer Telemetry: " + set_timer_telemetry);
  }

  if (preferences.getString("prefix_tel", "") != set_prefix_telemetry) {
    preferences.putString("prefix_tel", set_prefix_telemetry);
    Serial.println("Update Prefix Telemetry: " + set_prefix_telemetry);
  }

  // --- variabel jadwal ---
  for (int i = 0; i < JUMLAH_JADWAL; i++) {
    if (preferences.getInt(("jadwal_status_" + String(i)).c_str(), -1) != jadwal_status[i]) {
      preferences.putInt(("jadwal_status_" + String(i)).c_str(), jadwal_status[i]);
    }

    if (preferences.getInt(("jadwal_senin_" + String(i)).c_str(), -1) != jadwal_hari_senin[i]) {
      preferences.putInt(("jadwal_senin_" + String(i)).c_str(), jadwal_hari_senin[i]);
    }

    if (preferences.getInt(("jadwal_selasa_" + String(i)).c_str(), -1) != jadwal_hari_selasa[i]) {
      preferences.putInt(("jadwal_selasa_" + String(i)).c_str(), jadwal_hari_selasa[i]);
    }

    if (preferences.getInt(("jadwal_rabu_" + String(i)).c_str(), -1) != jadwal_hari_rabu[i]) {
      preferences.putInt(("jadwal_rabu_" + String(i)).c_str(), jadwal_hari_rabu[i]);
    }

    if (preferences.getInt(("jadwal_kamis_" + String(i)).c_str(), -1) != jadwal_hari_kamis[i]) {
      preferences.putInt(("jadwal_kamis_" + String(i)).c_str(), jadwal_hari_kamis[i]);
    }

    if (preferences.getInt(("jadwal_jumat_" + String(i)).c_str(), -1) != jadwal_hari_jumat[i]) {
      preferences.putInt(("jadwal_jumat_" + String(i)).c_str(), jadwal_hari_jumat[i]);
    }

    if (preferences.getInt(("jadwal_sabtu_" + String(i)).c_str(), -1) != jadwal_hari_sabtu[i]) {
      preferences.putInt(("jadwal_sabtu_" + String(i)).c_str(), jadwal_hari_sabtu[i]);
    }

    if (preferences.getInt(("jadwal_minggu_" + String(i)).c_str(), -1) != jadwal_hari_minggu[i]) {
      preferences.putInt(("jadwal_minggu_" + String(i)).c_str(), jadwal_hari_minggu[i]);
    }

    if (preferences.getInt(("jadwal_jam_" + String(i)).c_str(), -1) != jadwal_jam[i]) {
      preferences.putInt(("jadwal_jam_" + String(i)).c_str(), jadwal_jam[i]);
    }

    if (preferences.getInt(("jadwal_menit_" + String(i)).c_str(), -1) != jadwal_menit[i]) {
      preferences.putInt(("jadwal_menit_" + String(i)).c_str(), jadwal_menit[i]);
    }

    if (preferences.getInt(("jadwal_detik_" + String(i)).c_str(), -1) != jadwal_detik[i]) {
      preferences.putInt(("jadwal_detik_" + String(i)).c_str(), jadwal_detik[i]);
    }

    if (preferences.getInt(("jadwal_lim_tds_" + String(i)).c_str(), -1) != jadwal_limit_tds[i]) {
      preferences.putInt(("jadwal_lim_tds_" + String(i)).c_str(), jadwal_limit_tds[i]);
    }

    if (preferences.getInt(("jadwal_sts_tds_" + String(i)).c_str(), -1) != jadwal_status_tds[i]) {
      preferences.putInt(("jadwal_sts_tds_" + String(i)).c_str(), jadwal_status_tds[i]);
    }

    if (preferences.getInt(("jadwal_ops_tds_" + String(i)).c_str(), -1) != jadwal_operasi_tds[i]) {
      preferences.putInt(("jadwal_ops_tds_" + String(i)).c_str(), jadwal_operasi_tds[i]);
    }

    if (preferences.getInt(("jadwal_sts_ph_" + String(i)).c_str(), -1) != jadwal_status_ph[i]) {
      preferences.putInt(("jadwal_sts_ph_" + String(i)).c_str(), jadwal_status_ph[i]);
    }

    if (preferences.getInt(("jadwal_lim_ph_" + String(i)).c_str(), -1) != jadwal_limit_ph[i]) {
      preferences.putInt(("jadwal_lim_ph_" + String(i)).c_str(), jadwal_limit_ph[i]);
    }

    if (preferences.getInt(("jadwal_ops_ph_" + String(i)).c_str(), -1) != jadwal_operasi_ph[i]) {
      preferences.putInt(("jadwal_ops_ph_" + String(i)).c_str(), jadwal_operasi_ph[i]);
    }

    if (preferences.getInt(("jadwal_tmr_na_" + String(i)).c_str(), -1) != jadwal_timer_pompa_na[i]) {
      preferences.putInt(("jadwal_tmr_na_" + String(i)).c_str(), jadwal_timer_pompa_na[i]);
    }

    if (preferences.getInt(("jadwal_tmr_nb_" + String(i)).c_str(), -1) != jadwal_timer_pompa_nb[i]) {
      preferences.putInt(("jadwal_tmr_nb_" + String(i)).c_str(), jadwal_timer_pompa_nb[i]);
    }

    if (preferences.getInt(("jadwal_tmr_phu_" + String(i)).c_str(), -1) != jadwal_timer_pompa_phu[i]) {
      preferences.putInt(("jadwal_tmr_phu_" + String(i)).c_str(), jadwal_timer_pompa_phu[i]);
    }

    if (preferences.getInt(("jadwal_tmr_phd_" + String(i)).c_str(), -1) != jadwal_timer_pompa_phd[i]) {
      preferences.putInt(("jadwal_tmr_phd_" + String(i)).c_str(), jadwal_timer_pompa_phd[i]);
    }

    if (preferences.getInt(("jadwal_set_na_" + String(i)).c_str(), -1) != jadwal_set_pompa_na[i]) {
      preferences.putInt(("jadwal_set_na_" + String(i)).c_str(), jadwal_set_pompa_na[i]);
    }

    if (preferences.getInt(("jadwal_set_nb_" + String(i)).c_str(), -1) != jadwal_set_pompa_nb[i]) {
      preferences.putInt(("jadwal_set_nb_" + String(i)).c_str(), jadwal_set_pompa_nb[i]);
    }

    if (preferences.getInt(("jadwal_set_phu_" + String(i)).c_str(), -1) != jadwal_set_pompa_phu[i]) {
      preferences.putInt(("jadwal_set_phu_" + String(i)).c_str(), jadwal_set_pompa_phu[i]);
    }

    if (preferences.getInt(("jadwal_set_phd_" + String(i)).c_str(), -1) != jadwal_set_pompa_phd[i]) {
      preferences.putInt(("jadwal_set_phd_" + String(i)).c_str(), jadwal_set_pompa_phd[i]);
    }
  }
  preferences.end();
  Serial.println("Konfigurasi & Jadwal berhasil disimpan (hanya yang berubah).");
}

void setup_memory() {
  // Baca dari memory saat startup
  baca_memory();
}
