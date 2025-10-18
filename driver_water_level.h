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


void loop_water_level() {
  // Jika mode manual, jangan ubah status pompa
  if (!set_waterlevel_automode) return ;
    if (halaman != 0 ) return; 

  // Baca nilai sensor
  waterLevelValue = digitalRead(PIN_WATER_LEVEL);

  // Debug cepat (bisa dihapus jika tidak perlu)
  Serial.println(waterLevelValue);

  // LOW berarti air penuh (tergantung orientasi pelampung)
  if (waterLevelValue == 1) {
    //isWaterHigh = true;
    matikan_solenoid(); // 🔹 saat air naik, relay close (mati)
  } else {
    //isWaterHigh = false;
    nyalakan_solenoid(); // 🔹 saat air turun, relay open (hidup)
  }

  // Debug opsional agar tidak terlalu sering
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 1000) {
    lastPrint = millis();
    Serial.printf("[WATER_LEVEL] Mode: %s | Status: %s | Nilai: %d\n",
                  set_waterlevel_automode ? "AUTO" : "MANUAL",
                  isWaterHigh ? "Air PENUH (solenoid OFF)" : "Air RENDAH (solenoid ON)",
                  waterLevelValue);
  }
}



// //-------------------jika perlu fitur manual / auto pompa atau kran air
// void loop_water_level() {
//   if (!set_waterlevel_automode) return;  // ⛔ jika bukan auto mode, jangan ubah pompa

//   waterLevelValue = digitalRead(PIN_WATER_LEVEL);

//   if (waterLevelValue == LOW) {
//     isWaterHigh = true;
//     matikan_pompa_air(); // saat air tinggi, matikan pompa
//   } else {

//     isWaterHigh = false;
//     nyalakan_pompa_air(); // saat air rendah, hidupkan pompa
//   }
// }
