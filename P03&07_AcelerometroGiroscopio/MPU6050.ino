#include <Wire.h>
#include <MPU6050.h>
 
MPU6050 mpu;
 
void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Inicializar el sensor MPU6050
  mpu.initialize();
  
  // Configurar el rango de escala del giroscopio y acelerómetro
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
}
 
void loop() {
  // Leer los datos del sensor
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  // Convertir los datos en unidades de medida
  float accelX = ax / 16384.0; // Sensibilidad del acelerómetro para el rango de ±2g
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;
  
  float gyroX = gx / 131.0; // Sensibilidad del giroscopio para el rango de ±250°/s
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;
  
  // Mostrar los datos en el monitor serial
  Serial.print("Acelerómetro: ");
  Serial.print("X = "); Serial.print(accelX);
  Serial.print(" | Y = "); Serial.print(accelY);
  Serial.print(" | Z = "); Serial.println(accelZ);
  
  Serial.print("Giroscopio: ");
  Serial.print("X = "); Serial.print(gyroX);
  Serial.print(" | Y = "); Serial.print(gyroY);
  Serial.print(" | Z = "); Serial.println(gyroZ);
  
  delay(1000); // Esperar un poco antes de la próxima lectura
}