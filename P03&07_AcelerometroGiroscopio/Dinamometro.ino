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
  
  //Calculo de la magnitud del vector aceleración
  float acelMag = sqrt(pow(accelX - 1, 2) + pow(accelY, 2) + pow(accelZ, 2)); //Se calibra para ignorar la gravedad
  //Calculo de la fuerza
  float f = 0.280 * (acelMag * 9.81) - 0.2; //Conversión de g a m/s^2
  Serial.println(f);
  delay(200); 
}