/*
  =========================================================
   Modul : MQTT Client (PubSubClient)
   Author: shmukti

   Deskripsi:
     - Modul ini mengatur koneksi ESP32 ke broker MQTT dan 
       menangani komunikasi publish/subscribe.
     - MQTT digunakan untuk mengirim data sensor (telemetry) 
       dan menerima perintah kontrol pompa.

   Konfigurasi:
     - MQTT_HOST : broker.mqtt.cool (dapat diubah dari memory/NVS)
     - MQTT_PORT : 1883 (default)
     - Interval reconnect : setiap 2000 ms (timer_mqtt)
     - Topik publish sensor:
         * TOPIC_SUHU_AIR          -> vsa
         * TOPIC_SUHU_UDARA        -> vsu
         * TOPIC_KELEMBABAN_UDARA  -> vku
         * TOPIC_TDS               -> vtds
         * TOPIC_PH                -> vph
     - Topik subscribe kontrol pompa:
         * TOPIC_POMPA_AIR -> kontrol pompa air
         * TOPIC_POMPA_NA  -> kontrol pompa nutrisi A
         * TOPIC_POMPA_NB  -> kontrol pompa nutrisi B
         * TOPIC_POMPA_PHU -> kontrol pompa pH UP
         * TOPIC_POMPA_PHD -> kontrol pompa pH DOWN

   Fungsi:
     1. onMqttMessage(topic, payload, length)
        - Callback ketika pesan masuk.
        - Mengubah payload ke String (mqtt_pesan).
        - Membandingkan dengan topik kontrol.
        - Jika mqtt_pesan == "1" → nyalakan pompa.
        - Jika mqtt_pesan == "0" → matikan pompa.
        - Menampilkan log ke Serial Monitor.

     2. connectMQTT()
        - Mengecek setiap 2 detik dengan timer_mqtt().
        - Set konfigurasi broker & callback.
        - Membuat clientId unik dari MAC ESP32.
        - Jika belum terhubung:
            * Mencoba koneksi.
            * Jika berhasil → subscribe ke topik kontrol pompa.
            * Jika gagal → tampilkan error dan coba lagi 2 detik.

     3. setup_mqtt()
        - Dipanggil di setup().
        - Menampilkan "MQTT terinisialisasi..." di Serial.
        - Memanggil connectMQTT() pertama kali.

     4. loop_mqtt()
        - Dipanggil di loop utama.
        - Jika koneksi MQTT putus → panggil connectMQTT().
        - Jika masih terhubung → jalankan mqtt.loop() 
          untuk menjaga komunikasi MQTT tetap hidup.

   Catatan:
     - Library yang dipakai: PubSubClient.
     - mqtt.loop() harus dipanggil sesering mungkin 
       agar komunikasi MQTT lancar.
     - Topik publish sensor diatur di modul telemetry 
       (lihat loop_telemetry()).
     - Username/password belum dipakai, 
       bisa ditambahkan jika broker membutuhkan autentikasi.

   Tujuan:
     - Menyediakan mekanisme komunikasi dua arah 
       (telemetry data sensor dan kontrol pompa).
     - Mendukung sistem monitoring dan kendali jarak jauh 
       berbasis MQTT.

  =========================================================
*/

#include <PubSubClient.h>

// KONFIGURASI MQTT
String MQTT_HOST = "broker.mqtt.cool";
String MQTT_PORT = "1883";

// TOPIK POMPA
String TOPIC_POMPA_NA = "na";
String TOPIC_POMPA_NB = "nb";
String TOPIC_POMPA_PHU = "phu";
String TOPIC_POMPA_PHD = "phd";
String TOPIC_POMPA_AIR = "air";
String TOPIC_SOLENOID = "sv";

// TOPIK SENSOR
String TOPIC_SUHU_AIR = "vsa";
String TOPIC_SUHU_UDARA = "vsu";
String TOPIC_KELEMBABAN_UDARA = "vku";
String TOPIC_TDS = "vtds";
String TOPIC_PH = "vph";
String TOPIC_SENSOR_CAHAYA = "vsc";

// TOPIK MODE KRAN ATAU POMPA AIR
String TOPIC_MODE_AIR = "mode_air";  // topik baru untuk ubah mode
// ------------------------------------------------------------

PubSubClient mqtt(espClient);

Every timer_mqtt(2000);  //setiap 2 detik

void onMqttMessage(char* topic, byte* payload, unsigned int length) {
  // Ubah topic ke String
  String mqtt_topik = String(topic);
  // Ubah payload ke String
  String mqtt_pesan;
  for (unsigned int i = 0; i < length; i++) {
    mqtt_pesan = mqtt_pesan + (char)payload[i];
  }
  // Hanya print topic & message
  Serial.print("[MQTT] Topic: ");
  Serial.print(mqtt_topik);
  Serial.print(" | Pesan: ");
  Serial.println(mqtt_pesan);
  String TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_AIR;
  if (mqtt_topik == TOPIC_SUB) {
    if (mqtt_pesan == "1") {
      nyalakan_pompa_air();
    }
    if (mqtt_pesan == "0") {
      matikan_pompa_air();
    }
  }
  TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_NA;
  if (mqtt_topik == TOPIC_SUB) {
    if (mqtt_pesan == "1") {
      nyalakan_pompa_nutrisi_a();
    }
    if (mqtt_pesan == "0") {
      matikan_pompa_nutrisi_a();
    }
  }
  TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_NB;
  if (mqtt_topik == TOPIC_SUB) {
    if (mqtt_pesan == "1") {
      nyalakan_pompa_nutrisi_b();
    }
    if (mqtt_pesan == "0") {
      matikan_pompa_nutrisi_b();
    }
  }

  TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_PHU;
  if (mqtt_topik == TOPIC_SUB) {
    if (mqtt_pesan == "1") {
      nyalakan_pompa_ph_up();
    }
    if (mqtt_pesan == "0") {
      matikan_pompa_ph_up();
    }
  }

  TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_PHD;
  if (mqtt_topik == TOPIC_SUB) {
    if (mqtt_pesan == "1") {
      nyalakan_pompa_ph_down();
    }
    if (mqtt_pesan == "0") {
      matikan_pompa_ph_down();
    }
  }

  TOPIC_SUB = set_prefix_telemetry + TOPIC_SOLENOID;
  if (mqtt_topik == TOPIC_SUB) {
    if (mqtt_pesan == "1") {
      nyalakan_solenoid();
    }
    if (mqtt_pesan == "0") {
      matikan_solenoid();
    }
  }

  // topik untuk konfigurasi auto atau manual pompa/ kran air
  TOPIC_SUB = set_prefix_telemetry + TOPIC_MODE_AIR;
  if (mqtt_topik == TOPIC_SUB) {
    if (mqtt_pesan == "auto") {
      set_waterlevel_automode = true;
      Serial.println("[MODE] Pompa air diatur ke AUTO (sensor aktif).");
    }
    if (mqtt_pesan == "manual") {
      set_waterlevel_automode = false;
      Serial.println("[MODE] Pompa air diatur ke MANUAL (kendali MQTT).");
    }
  }
}


void connectMQTT() {

  if (timer_mqtt()) {
    MQTT_HOST = set_mqtt_broker;
    MQTT_PORT = set_mqtt_port;
    mqtt.setServer(MQTT_HOST.c_str(), MQTT_PORT.toInt());
    mqtt.setCallback(onMqttMessage);

    String clientId = "ESP32-" + String((uint32_t)ESP.getEfuseMac(), HEX);

    if (!mqtt.connected()) {
      Serial.print("Menghubungkan MQTT sebagai ");
      Serial.print(clientId);
      Serial.print(" ... ");

      bool ok = mqtt.connect(clientId.c_str());
      if (ok) {
        Serial.println("TERHUBUNG.");
        Serial.print("Subscribe ke: ");

        String TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_AIR;
        mqtt.subscribe(TOPIC_SUB.c_str());
        Serial.println(TOPIC_SUB);
        TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_NA;
        mqtt.subscribe(TOPIC_SUB.c_str());
        Serial.println(TOPIC_SUB);
        TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_NB;
        mqtt.subscribe(TOPIC_SUB.c_str());
        Serial.println(TOPIC_SUB);
        TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_PHD;
        mqtt.subscribe(TOPIC_SUB.c_str());
        Serial.println(TOPIC_SUB);
        TOPIC_SUB = set_prefix_telemetry + TOPIC_POMPA_PHU;
        mqtt.subscribe(TOPIC_SUB.c_str());
        Serial.println(TOPIC_SUB);
        // MODE AUTO/MANUAL POMPA ATAU KRAN AIR
        TOPIC_SUB = set_prefix_telemetry + TOPIC_MODE_AIR;
        mqtt.subscribe(TOPIC_SUB.c_str());
        Serial.println(TOPIC_SUB);
      } else {
        Serial.print("Gagal (rc=");
        Serial.print(mqtt.state());
        Serial.println("), coba lagi 2 detik...");
      }
    }
  }
}

void setup_mqtt() {
  Serial.println("MQTT terinisialisasi...");
  connectMQTT();
}

void loop_mqtt() {
  if (!mqtt.connected()) {
    connectMQTT();
  } else {
    mqtt.loop();
  }
}
