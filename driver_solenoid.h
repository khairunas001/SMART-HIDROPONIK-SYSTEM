#define PIN_RELAY_SV 4

void matikan_solenoid() {
  //matikan pompa
  digitalWrite(PIN_RELAY_SV, HIGH);
  status_solenoid = 0;
  set_status_solenoid = 0;
}
void nyalakan_solenoid() {
  //nyalakan pompa
  digitalWrite(PIN_RELAY_SV, LOW);
  status_solenoid = 1;
  set_status_solenoid = 1;
}

void setup_solenoid() {
  //set pin relay pompa sebagai output
  pinMode(PIN_RELAY_SV, OUTPUT);
  //defaultnya adalah pompa hidup
  matikan_solenoid();

  Serial.println("Solenoid siap digunakan....");
}

void update_status_solenoid() {
  if (set_status_solenoid != status_solenoid) {
    if (set_status_solenoid == 1) {
      nyalakan_solenoid();
    }
    if (set_status_solenoid == 0) {
      matikan_solenoid();
    }
  }
}
