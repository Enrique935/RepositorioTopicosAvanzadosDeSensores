#include <Servo.h>
#include "Adafruit_VL53L0X.h"

// Crear una instancia del sensor VL53L0X
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
//Servomotor
Servo myServo;

void setup() {
  myServo.attach(9);
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
  myServo.write(0);
  delay(1000);
  VL53L0X_RangingMeasurementData_t measure; //Toma de distancia para cada angulo del servomotor
  //Muestreo de la distancia a partir de los ángulos del servo
  for(int i = 0; i <= 180; i+=3){
    myServo.write(i);
    delay(500);
  // Realizar una medición con el sensor
  lox.rangingTest(&measure, false); // 'true' para obtener datos de depuración
  // Verificar si la medición es válida
  if (measure.RangeStatus != 4) {  // Los fallos de fase tienen datos incorrectos
    // Calcular el valor filtrado usando el filtro EMA
    Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range "); // Mensaje si el objeto está fuera de rango
    }  
  delay(1000); // Retardo entre mediciones
  }
}
