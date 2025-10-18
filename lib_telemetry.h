/*
  =========================================================
   Modul : Telemetry MQTT
   Author: shmukti

   Deskripsi:
     - Modul ini bertanggung jawab mengatur pengiriman data 
       sensor secara periodik (telemetry) ke broker MQTT.
     - Interval pengiriman ditentukan oleh variabel global 
       set_timer_telemetry (dalam milidetik).
     - Timer non-blocking digunakan (Every timer_telemetry).

   Fungsi:
     1. setup_telemetry()
        - Reset / set ulang timer_telemetry dengan nilai terbaru 
          dari set_timer_telemetry.
        - Timer akan otomatis aktif setelah reset.

     2. loop_telemetry()
        - Dijalankan di dalam loop utama program.
        - Mengecek apakah timer_telemetry sudah "jatuh tempo".
        - Jika ya, dan koneksi MQTT aktif:
            * Ambil nilai sensor:
                - nilai_suhu_udara
                - nilai_kelembaban_udara
                - nilai_suhu_air
                - nilai_tds
                - nilai_ph
            * Ubah nilai menjadi String (payload).
            * Publish payload ke topic MQTT yang sesuai:
                - TOPIC_SUHU_UDARA
                - TOPIC_KELEMBABAN_UDARA
                - TOPIC_SUHU_AIR
                - TOPIC_TDS
                - TOPIC_PH
            * Cetak log ke Serial Monitor untuk debugging.

   Catatan:
     - timer_telemetry adalah objek dari library "Every" 
       (atau sejenis timer non-blocking).
     - mqtt adalah instance client MQTT (harus sudah terhubung).
     - Publish hanya dilakukan jika mqtt.connected() == true.
     - Interval dapat diubah dari menu setting (halaman 2001/2101),
       lalu dipanggil setup_telemetry() untuk apply perubahan.

   Tujuan:
     - Memastikan data sensor terkirim ke server secara periodik.
     - Menghindari blocking (tidak menggunakan delay).
     - Memberikan transparansi ke Serial Monitor untuk debugging.

  =========================================================
*/

Every timer_telemetry(5000);

void setup_telemetry() {
  timer_telemetry.reset(set_timer_telemetry.toInt(), true);
}

void loop_telemetry() {
  if (timer_telemetry()) {
    if (mqtt.connected()) {
      String payload = String(nilai_suhu_udara);
      String TOPIC_PUBLISH = set_prefix_telemetry + TOPIC_SUHU_UDARA;
      mqtt.publish(TOPIC_PUBLISH.c_str(), payload.c_str());
      Serial.print("[PUB] ");
      Serial.print(TOPIC_PUBLISH);
      Serial.print(" -> ");
      Serial.println(payload);

      payload = String(nilai_kelembaban_udara);
      TOPIC_PUBLISH = set_prefix_telemetry + TOPIC_KELEMBABAN_UDARA;
      mqtt.publish(TOPIC_PUBLISH.c_str(), payload.c_str());
      Serial.print("[PUB] ");
      Serial.print(TOPIC_PUBLISH);
      Serial.print(" -> ");
      Serial.println(payload);

      payload = String(nilai_suhu_air);
      TOPIC_PUBLISH = set_prefix_telemetry + TOPIC_SUHU_AIR;
      mqtt.publish(TOPIC_PUBLISH.c_str(), payload.c_str());
      Serial.print("[PUB] ");
      Serial.print(TOPIC_PUBLISH);
      Serial.print(" -> ");
      Serial.println(payload);

      payload = String(nilai_tds);
      TOPIC_PUBLISH = set_prefix_telemetry + TOPIC_TDS;
      mqtt.publish(TOPIC_PUBLISH.c_str(), payload.c_str());
      Serial.print("[PUB] ");
      Serial.print(TOPIC_PUBLISH);
      Serial.print(" -> ");
      Serial.println(payload);

      payload = String(nilai_ph);
      TOPIC_PUBLISH = set_prefix_telemetry + TOPIC_PH;
      mqtt.publish(TOPIC_PUBLISH.c_str(), payload.c_str());
      Serial.print("[PUB] ");
      Serial.print(TOPIC_PUBLISH);
      Serial.print(" -> ");
      Serial.println(payload);


      int cahaya = read_sensor_cahaya();

      payload = String(cahaya);
      TOPIC_PUBLISH = set_prefix_telemetry + TOPIC_SENSOR_CAHAYA;
      mqtt.publish(TOPIC_PUBLISH.c_str(), payload.c_str());
      Serial.print("[PUB] ");
      Serial.print(TOPIC_PUBLISH);
      Serial.print(" -> ");
      Serial.println(payload);
    }
  }
}