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
  float presion = baro.getPressure();
  float altitud = baro.getAltitude();
  float temperatura = baro.getTemperature();
  float t = 237.15 + temperatura; // grados a kelvin
  float press = presion*100; // hecto pascales a pascales 
  float p = (press/(287.0500676*t)); // formula de la densidad de aire


  Serial.print("presión = "); Serial.print(presion); Serial.println(" hPa");
  Serial.print("altitud = "); Serial.print(altitud); Serial.println(" m");
  Serial.print("temperatura = "); Serial.print(temperatura); Serial.println(" C");
  Serial.print("densidad = "); Serial.print(p); Serial.println(" kg/m3 ");
  delay(6000);
}