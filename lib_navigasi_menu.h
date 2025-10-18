#include "Arduino.h"

void navigasi_button_ok_back(int target_halaman_ok, int target_halaman_back) {
  if (BTN_OK) {
    lcd.clear();
    halaman = target_halaman_ok;
    beep();
  }
  if (BTN_BACK) {
    lcd.clear();
    halaman = target_halaman_back;
    beep();
  }
}

void navigasi_button_up_down(int awal, int akhir) {
  if (BTN_NAV_UP) {
    halaman = halaman + 1;
    if (halaman > akhir) {
      halaman = awal;
    }

    beep();
    lcd.clear();
    Serial.print("awal:");
    Serial.print(awal);
    Serial.print(" akhir:");
    Serial.print(akhir);
    Serial.print(" halaman:");
    Serial.println(halaman);
  }
  if (BTN_NAV_DOWN) {
    halaman = halaman - 1;
    if (halaman < awal) {
      halaman = akhir;
    }
    beep();
    lcd.clear();
    Serial.print("awal:");
    Serial.print(awal);
    Serial.print(" akhir:");
    Serial.print(akhir);
    Serial.print(" halaman:");
    Serial.println(halaman);
  }
}

void navigasi_button_value(int &var, int step, int minVal, int maxVal) {
  if (BTN_VAL_UP) {  // tombol ditekan (LOW aktif)
    var = var + step;
    if (var > maxVal) {
      var = minVal;
    }
    simpan_memory();
    beep();
  }
  if (BTN_VAL_DOWN) {
    var = var - step;
    if (var < minVal) {
      var = maxVal;
    }
    simpan_memory();
    beep();
  }
}

void navigasi_button_value(byte &var, int step, int minVal, int maxVal) {
  if (BTN_VAL_UP) {  // tombol ditekan (LOW aktif)
    var = var + step;
    if (var > maxVal) {
      var = minVal;
    }
    simpan_memory();
    beep();
  }
  if (BTN_VAL_DOWN) {
    var = var - step;
    if (var < minVal) {
      var = maxVal;
    }
    simpan_memory();
    beep();
  }
}
// Array angka
char number_code[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
int jumlahAngka = sizeof(number_code) / sizeof(number_code[0]);

// Variabel global
int cursor_position = 0;
int char_index[20] = { 0 };  // cukup untuk max_length 20

// Fungsi trim (buang spasi kanan)
String rtrim(const String &s) {
  int end = s.length() - 1;
  while (end >= 0 && s[end] == ' ') {
    end--;
  }
  return s.substring(0, end + 1);
}

// Fungsi input khusus angka
void input_text_nomor(String Name, String &Value, int max_length = 18) {
  // Auto padding dengan spasi
  while (Value.length() < max_length) {
    Value += " ";
  }

  lcd.setCursor(0, 0);
  lcd.print(" ");
  lcd.print(Name);
  lcd.setCursor(1, 1);
  lcd.print(Value);

  // tanda kursor
  lcd.setCursor(1 + cursor_position, 2);
  lcd.print("^");

  // Navigasi posisi kursor
  if (BTN_NAV_UP) {
    cursor_position++;
    if (cursor_position >= max_length) cursor_position = 0;
    beep();
    lcd.clear();
  }
  if (BTN_NAV_DOWN) {
    cursor_position--;
    if (cursor_position < 0) cursor_position = max_length - 1;
    beep();
    lcd.clear();
  }

  // Hapus karakter jadi spasi
  if (BTN_OK) {
    Value.setCharAt(cursor_position, ' ');
    beep();
    lcd.clear();
  }

  // Ubah nilai karakter dengan tombol VAL
  if (BTN_VAL_UP) {
    char_index[cursor_position]++;
    if (char_index[cursor_position] >= jumlahAngka)
      char_index[cursor_position] = 0;

    Value.setCharAt(cursor_position, number_code[char_index[cursor_position]]);

    beep();
  }
  if (BTN_VAL_DOWN) {
    char_index[cursor_position]--;
    if (char_index[cursor_position] < 0)
      char_index[cursor_position] = jumlahAngka - 1;

    Value.setCharAt(cursor_position, number_code[char_index[cursor_position]]);

    beep();
  }
  // Pastikan output final nanti tidak ada spasi kanan
  Value = rtrim(Value);
}

// Array lengkap alpabet
char alpabet[] = {
  // angka
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  // huruf besar
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y', 'Z',
  // huruf kecil
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z',
  // simbol umum
  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
  '-', '_', '=', '+', '[', ']', '{', '}', ';',
  ':', '\'', '"', '\\', '|', ',', '.', '/', '<', '>', '?',
  // spasi
  ' '
};
int jumlahAlpabet = sizeof(alpabet) / sizeof(alpabet[0]);


// Fungsi input khusus alpabet
void input_text_alpabet(String Name, String &Value, int max_length = 18) {
  // Auto padding dengan spasi
  while (Value.length() < max_length) {
    Value += " ";
  }

  lcd.setCursor(0, 0);
  lcd.print(" ");
  lcd.print(Name);
  lcd.setCursor(1, 1);
  lcd.print(Value);

  // tanda kursor
  lcd.setCursor(1 + cursor_position, 2);
  lcd.print("^");

  // Navigasi posisi kursor
  if (BTN_NAV_UP) {
    cursor_position++;
    if (cursor_position >= max_length) cursor_position = 0;
    beep();
    lcd.clear();
  }
  if (BTN_NAV_DOWN) {
    cursor_position--;
    if (cursor_position < 0) cursor_position = max_length - 1;
    beep();
    lcd.clear();
  }

  // Hapus karakter jadi spasi
  if (BTN_OK) {
    Value.setCharAt(cursor_position, ' ');
    beep();
    lcd.clear();
  }

  // Ubah karakter dengan tombol VAL
  if (BTN_VAL_UP) {
    char_index[cursor_position]++;
    if (char_index[cursor_position] >= jumlahAlpabet)
      char_index[cursor_position] = 0;

    Value.setCharAt(cursor_position, alpabet[char_index[cursor_position]]);
    beep();
  }
  if (BTN_VAL_DOWN) {
    char_index[cursor_position]--;
    if (char_index[cursor_position] < 0)
      char_index[cursor_position] = jumlahAlpabet - 1;

    Value.setCharAt(cursor_position, alpabet[char_index[cursor_position]]);
    beep();
  }
  // Pastikan output final nanti tidak ada spasi kanan
  Value = rtrim(Value);
}
