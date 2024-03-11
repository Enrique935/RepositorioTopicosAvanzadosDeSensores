#include "Adafruit_VL53L0X.h"

// Crear una instancia del sensor VL53L0X
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Variables para almacenar las lecturas del sensor y el valor filtrado
double anterior = 0;
double filtrada;
double alpha = 0.25; // Factor de suavizado para el filtro EMA

void setup() {
  Serial.begin(9600);

  // Esperar a que el puerto serie se abra para dispositivos USB nativos
  while (!Serial) {
    delay(1);
  }
  
 // Serial.println("Adafruit VL53L0X test");
  // Iniciar el sensor VL53L0X
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1); // Mantener el programa en un bucle infinito si el sensor no se inicia
  }
  // Mensaje de inicio
  //Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  
  //for(int i = 0; i <= 180; i++){}
  // Realizar una medición con el sensor
  lox.rangingTest(&measure, false); // 'true' para obtener datos de depuración

  // Verificar si la medición es válida
  if (measure.RangeStatus != 4) {  // Los fallos de fase tienen datos incorrectos
    // Calcular el valor filtrado usando el filtro EMA
    filtrada = alpha * measure.RangeMilliMeter + (1 - alpha) * anterior; 
    Serial.println(filtrada); // Imprimir el valor filtrado
    anterior = filtrada; // Actualizar el valor anterior con el valor filtrado
    delay(400);
  } else {
    Serial.println(" out of range "); // Mensaje si el objeto está fuera de rango
  }
    
  delay(100); // Retardo entre mediciones
}