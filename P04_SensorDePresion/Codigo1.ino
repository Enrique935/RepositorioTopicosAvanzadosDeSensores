#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro;

void setup() {
  Serial.begin(9600);

  if (!baro.begin()) {
    Serial.println("No se pudo encontrar el sensor");
    return;
  }
}

void loop() {
  

  float pascales = baro.getPressure();
  Serial.print(pascales);
  Serial.println(" Pascales");

  float altitud = baro.getAltitude();
  Serial.print(altitud);
  Serial.println(" metros");

  float temp = baro.getTemperature();
  Serial.print(temp);
  Serial.println(" °C");

  delay(6000);
}
