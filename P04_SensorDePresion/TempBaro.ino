#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  baro.begin();
}

void loop() {
  float temp = baro.getTemperature(); 

  Serial.println(temp);

  delay(1000);
}