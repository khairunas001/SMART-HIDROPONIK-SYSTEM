
String txt_on_off[2] = { "OFF", "ON " };
void halaman_setting_jadwal() {

  HALAMAN_AWAL = 1001;
  HALAMAN_AKHIR = 1005;

  // ===== Halaman 1001 =====
  if (halaman == 1001) {
    lcd.setCursor(0, 0);
    lcd.print(">Jadwal 1 (" + txt_on_off[jadwal_status[0]] + ")");
    lcd.setCursor(0, 1);
    lcd.print(" Jadwal 2 (" + txt_on_off[jadwal_status[1]] + ")");
    lcd.setCursor(0, 2);
    lcd.print(" Jadwal 3 (" + txt_on_off[jadwal_status[2]] + ")");
    lcd.setCursor(0, 3);
    lcd.print(" Jadwal 4 (" + txt_on_off[jadwal_status[3]] + ")");
    index_jadwal = 0;
    navigasi_button_ok_back(1101, 1);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  // ===== Halaman 1002 =====
  if (halaman == 1002) {
    lcd.setCursor(0, 0);
    lcd.print(" Jadwal 1 (" + txt_on_off[jadwal_status[0]] + ")");
    lcd.setCursor(0, 1);
    lcd.print(">Jadwal 2 (" + txt_on_off[jadwal_status[1]] + ")");
    lcd.setCursor(0, 2);
    lcd.print(" Jadwal 3 (" + txt_on_off[jadwal_status[2]] + ")");
    lcd.setCursor(0, 3);
    lcd.print(" Jadwal 4 (" + txt_on_off[jadwal_status[3]] + ")");
    index_jadwal = 1;
    navigasi_button_ok_back(1102, 1);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  // ===== Halaman 1003 =====
  if (halaman == 1003) {
    lcd.setCursor(0, 0);
    lcd.print(" Jadwal 1 (" + txt_on_off[jadwal_status[0]] + ")");
    lcd.setCursor(0, 1);
    lcd.print(" Jadwal 2 (" + txt_on_off[jadwal_status[1]] + ")");
    lcd.setCursor(0, 2);
    lcd.print(">Jadwal 3 (" + txt_on_off[jadwal_status[2]] + ")");
    lcd.setCursor(0, 3);
    lcd.print(" Jadwal 4 (" + txt_on_off[jadwal_status[3]] + ")");
    index_jadwal = 2;
    navigasi_button_ok_back(1103, 1);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  // ===== Halaman 1004 =====
  if (halaman == 1004) {
    lcd.setCursor(0, 0);
    lcd.print(" Jadwal 1 (" + txt_on_off[jadwal_status[0]] + ")");
    lcd.setCursor(0, 1);
    lcd.print(" Jadwal 2 (" + txt_on_off[jadwal_status[1]] + ")");
    lcd.setCursor(0, 2);
    lcd.print(" Jadwal 3 (" + txt_on_off[jadwal_status[2]] + ")");
    lcd.setCursor(0, 3);
    lcd.print(">Jadwal 4 (" + txt_on_off[jadwal_status[3]] + ")");
    index_jadwal = 3;
    navigasi_button_ok_back(1104, 1);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }

  // ===== Halaman 1005 =====
  if (halaman == 1005) {
    lcd.setCursor(0, 0);
    lcd.print(" Jadwal 2 (" + txt_on_off[jadwal_status[1]] + ")");
    lcd.setCursor(0, 1);
    lcd.print(" Jadwal 3 (" + txt_on_off[jadwal_status[2]] + ")");
    lcd.setCursor(0, 2);
    lcd.print(" Jadwal 4 (" + txt_on_off[jadwal_status[3]] + ")");
    lcd.setCursor(0, 3);
    lcd.print(">Jadwal 5 (" + txt_on_off[jadwal_status[4]] + ")");
    index_jadwal = 4;
    navigasi_button_ok_back(1105, 1);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
}
