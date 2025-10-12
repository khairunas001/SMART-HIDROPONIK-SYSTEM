/*
  =========================================================
   Modul : Input Tombol Navigasi
   Author: shmukti

   Deskripsi:
     - Modul ini mengatur input dari enam buah tombol 
       untuk navigasi menu dan pengaturan nilai di LCD.
     - Tombol terhubung ke pin ESP32 dengan konfigurasi
       INPUT_PULLDOWN (default = LOW, ditekan = HIGH).
     - Makro BTN_XXX memudahkan pembacaan status tombol.

   Konfigurasi Pin:
     - PIN_OK : 27 -> Tombol OK / Enter
     - PIN_NO : 23 -> Tombol Back / Cancel
     - PIN_NM : 13 -> Tombol Navigasi Menu Down
     - PIN_NP : 14 -> Tombol Navigasi Menu Up
     - PIN_VM : 15 -> Tombol Value Down
     - PIN_VP : 5  -> Tombol Value Up

   Definisi Makro:
     - BTN_OK       : true jika tombol OK ditekan
     - BTN_BACK     : true jika tombol Back ditekan
     - BTN_NAV_UP   : true jika tombol navigasi menu Up ditekan
     - BTN_NAV_DOWN : true jika tombol navigasi menu Down ditekan
     - BTN_VAL_UP   : true jika tombol Value Up ditekan
     - BTN_VAL_DOWN : true jika tombol Value Down ditekan

   Fungsi:
     1. setup_button()
        - Dipanggil sekali di setup().
        - Mengatur semua pin tombol sebagai INPUT_PULLDOWN.
        - Menampilkan pesan "tombol siap digunakan...."
          di Serial Monitor.

   Catatan:
     - Dengan INPUT_PULLDOWN, pastikan rangkaian tombol:
         * Salah satu kaki tombol ke pin GPIO.
         * Kaki satunya ke VCC (3.3V).
     - HIGH = tombol ditekan, LOW = tombol dilepas.
     - Disarankan implementasi debounce (software atau hardware)
       untuk menghindari pembacaan ganda saat tombol ditekan.

   Tujuan:
     - Memberikan kontrol navigasi untuk menu LCD.
     - Memungkinkan user mengatur nilai, berpindah halaman,
       dan melakukan konfirmasi (OK/Back).

  =========================================================
*/

// Pin tombol
#define PIN_OK 27
#define PIN_NO 23
#define PIN_NM 13
#define PIN_NP 14
#define PIN_VM 15
#define PIN_VP 5

#define BTN_OK        digitalRead(PIN_OK) == HIGH
#define BTN_BACK      digitalRead(PIN_NO) == HIGH

#define BTN_NAV_UP    digitalRead(PIN_NP) == HIGH
#define BTN_NAV_DOWN  digitalRead(PIN_NM) == HIGH

#define BTN_VAL_UP    digitalRead(PIN_VP) == HIGH
#define BTN_VAL_DOWN  digitalRead(PIN_VM) == HIGH


void setup_button() {
  // Set semua pin tombol sebagai input pull-down
  pinMode(PIN_OK, INPUT_PULLDOWN);
  pinMode(PIN_NO, INPUT_PULLDOWN);
  pinMode(PIN_NM, INPUT_PULLDOWN);
  pinMode(PIN_NP, INPUT_PULLDOWN);
  pinMode(PIN_VM, INPUT_PULLDOWN);
  pinMode(PIN_VP, INPUT_PULLDOWN);

  Serial.println("tombol siap digunakan....");
}

