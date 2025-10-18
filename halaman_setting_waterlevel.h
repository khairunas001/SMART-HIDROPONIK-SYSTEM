

void halaman_setting_waterlevel() {

  HALAMAN_AWAL = 8001;
  HALAMAN_AKHIR = 8001;

  // ===== Halaman 8001 =====
  if (halaman == 8001) {
    lcd.setCursor(0, 0);
    lcd.print("Automatic Mode:");
    lcd.setCursor(0, 1);
    lcd.print(">" + txt_on_off[set_waterlevel_automode]);
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
   
    navigasi_button_value(set_waterlevel_automode, 1, 0, 1);
    navigasi_button_ok_back(8001, 8);
    navigasi_button_up_down(HALAMAN_AWAL, HALAMAN_AKHIR);
  }
}
