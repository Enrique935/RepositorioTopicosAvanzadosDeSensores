#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

float tempMax = -100.0;
float tempMin = 100.0;
float tempSum = 0.0;
int count = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  baro.begin();
}

void loop() {
  float temp = baro.getTemperature(); 

  if (temp > tempMax) {  tempMax = temp;  }
  if (temp < tempMin) {  tempMin = temp;  }
  tempSum += temp; 
  count++; 

  delay(1000);

  if (count == 28800) { // Cuenta aproximada para 8 horas
    float tempAvg = tempSum / count; //temperatura promedio del dia 
    float unidadesCalor = (tempMax + tempMin) / 2.0 - 10.0; // unidades de calor para el frijol
    Serial.print("Temperatura máxima: ");
    Serial.print(tempMax);
    Serial.println(" °C");
    Serial.print("Temperatura mínima: ");
    Serial.print(tempMin);
    Serial.println(" °C");
    Serial.print("Temperatura promedio: ");
    Serial.print(tempAvg);
    Serial.println(" °C");
    Serial.print("Unidades de calor: ");
    Serial.println(unidadesCalor);
    if (unidadesCalor >= 153.24) {
      Serial.println("La planta está en maduración");
    } else if (unidadesCalor >= 112.77) {
      Serial.println("La planta está en llenado de vainas");
    } else if (unidadesCalor >= 99.31) {
      Serial.println("La planta está en formación de vaina");
    } else if (unidadesCalor >= 91.33) {
      Serial.println("La planta está en floración");
    } else if (unidadesCalor >= 64.41) {
      Serial.println("La planta está en formación de guías");
    } else if (unidadesCalor >= 12.89) {
      Serial.println("La planta está en estado de emergencia");
    } else {
      Serial.println("La planta está en estado de dormancia");
    }

    /////////// Reinicia las temperaturas al finalizar el día /////////////////////////
    tempMax = -100.0; 
    tempMin = 100.0; 
    tempSum = 0.0;  
    count = 0; 
  }
}