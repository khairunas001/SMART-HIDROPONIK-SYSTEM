#define PIN_LDR 36
void setup_sensor_cahaya(){

  pinMode(PIN_LDR,INPUT);
}

int read_sensor_cahaya(){
  int value = analogRead(PIN_LDR);
  return value;
}

void loop_sensor_cahaya(){
  
}