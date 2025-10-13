#ifndef DRIVER_WATER_LEVEL_H
#define DRIVER_WATER_LEVEL_H

#include <Arduino.h>
#include "driver_pompa_air.h"  // supaya bisa panggil nyalakan/matikan pompa

// ========================================================
// Driver : Water Level Switch (Float Switch Stainless)
// Board  : ESP32
// ========================================================

// perlu konfigurasi
#define PIN_WATER_LEVEL 39  // pin sensor float switch

bool isWaterHigh = false;   // true = air tinggi
int waterLevelValue = 0;

// --------------------------------------------------------
// Inisialisasi sensor
// --------------------------------------------------------
void setup_water_level() {
  pinMode(PIN_WATER_LEVEL, INPUT);
  Serial.println("[WATER_LEVEL] Sensor float switch siap...");
}

// --------------------------------------------------------
// Loop pembacaan sensor + kontrol pompa otomatis
// --------------------------------------------------------
// void loop_water_level() {
//   Serial.println(digitalRead(PIN_WATER_LEVEL));
//   waterLevelValue = digitalRead(PIN_WATER_LEVEL);

//   // LOW berarti air penuh (tergantung orientasi pelampung)
//   if (waterLevelValue == 0) {
//     // isWaterHigh = true;,,,,
//     matikan_pompa_air(); // 🔹 saat air naik, relay close (mati)
//   } else {
//     // isWaterHigh = false;
//     nyalakan_pompa_air(); // 🔹 saat air turun, relay open (hidup)
//   }

//   // Debug opsional
//   // Serial.printf("[WATER_LEVEL] %s | Relay: %s\n",
//   //               isWaterHigh ? "Air PENUH" : "Air RENDAH",
//   //               isWaterHigh ? "CLOSE (OFF)" : "OPEN (ON)");
// }

void loop_water_level() {
  // Jika mode manual, jangan ubah status pompa
  if (!autoMode) return;  // ⛔ jika bukan auto mode, keluar dari fungsi

  // Baca nilai sensor
  waterLevelValue = digitalRead(PIN_WATER_LEVEL);

  // Debug cepat (bisa dihapus jika tidak perlu)
  Serial.println(waterLevelValue);

  // LOW berarti air penuh (tergantung orientasi pelampung)
  if (waterLevelValue == 0) {
    //isWaterHigh = true;
    matikan_pompa_air(); // 🔹 saat air naik, relay close (mati)
  } else {
    //isWaterHigh = false;
    nyalakan_pompa_air(); // 🔹 saat air turun, relay open (hidup)
  }

  // Debug opsional agar tidak terlalu sering
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 1000) {
    lastPrint = millis();
    Serial.printf("[WATER_LEVEL] Mode: %s | Status: %s | Nilai: %d\n",
                  autoMode ? "AUTO" : "MANUAL",
                  isWaterHigh ? "Air PENUH (Pompa OFF)" : "Air RENDAH (Pompa ON)",
                  waterLevelValue);
  }
}



// //-------------------jika perlu fitur manual / auto pompa atau kran air
// void loop_water_level() {
//   if (!autoMode) return;  // ⛔ jika bukan auto mode, jangan ubah pompa

//   waterLevelValue = digitalRead(PIN_WATER_LEVEL);

//   if (waterLevelValue == LOW) {
//     isWaterHigh = true;
//     matikan_pompa_air(); // saat air tinggi, matikan pompa
//   } else {

//     isWaterHigh = false;
//     nyalakan_pompa_air(); // saat air rendah, hidupkan pompa
//   }
// }

#endif
