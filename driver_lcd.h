/*
  =========================================================
   Modul : LCD I2C (LiquidCrystal_I2C)
   Author: shmukti

   Deskripsi:
     - Modul ini digunakan untuk menampilkan informasi ke LCD 
       berbasis I2C (contoh: 20x4, 16x2).
     - Library yang digunakan:
         * Wire.h  -> komunikasi I2C
         * LiquidCrystal_I2C.h -> kontrol LCD via I2C backpack

   Konfigurasi:
     - Alamat I2C umum: 0x27 atau 0x3F 
       (perlu dicek dengan I2C Scanner sebelum dipakai).
     - Format inisialisasi: LiquidCrystal_I2C lcd(alamat, kolom, baris)
       Contoh:
         * lcd(0x27, 20, 4) -> LCD 20x4 dengan alamat 0x27
         * lcd(0x3F, 16, 2) -> LCD 16x2 dengan alamat 0x3F

   Fungsi:
     1. setup_lcd()
        - Dipanggil sekali di setup().
        - Inisialisasi komunikasi dengan LCD.
        - Menyalakan backlight (lampu latar).
        - Menampilkan pesan status ke Serial Monitor:
          "lcd siap digunakan...."

   Catatan:
     - lcd.init() wajib dipanggil sebelum menggunakan fungsi lcd.print().
     - lcd.backlight() menyalakan lampu latar, bisa dimatikan dengan lcd.noBacklight().
     - Untuk posisi kursor:
         lcd.setCursor(kolom, baris); 
         contoh: lcd.setCursor(0, 1); // kolom 0, baris 1
     - Cocok untuk menampilkan menu navigasi, data sensor, dan status sistem.

   Tujuan:
     - Memberikan antarmuka visual sederhana pada sistem berbasis ESP32.
     - Memudahkan user memantau data sensor & status perangkat.

  =========================================================
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Alamat I2C LCD biasanya 0x27 atau 0x3F (cek dulu dengan I2C scanner)
// Format: (alamat, jumlah kolom, jumlah baris)
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup_lcd() {
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();  // Hidupkan lampu latar
  Serial.println("lcd siap digunakan....");
}