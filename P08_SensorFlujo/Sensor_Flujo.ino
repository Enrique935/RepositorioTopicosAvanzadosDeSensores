const int Sensor = 2;  // Pin para la interrupción
volatile int Contador_pulsos = 0;  // Contador de pulsos
float Flujo_l_min = 0.0;  // Tasa de flujo en L/min
float Flujo_Litros = 0.0; // Tasa de flujo en litros
unsigned int Flujo_ml = 0;  // Flujo acumulado en mL
unsigned long mililitros_Totales = 0;  // Flujo total acumulado en mL
unsigned long UltimoTiempo = 0;  // Tiempo desde la última medición

void setup()
{
  pinMode(Sensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Sensor), Contador_pulsoser, FALLING);
  Serial.begin(9600);
}
void loop()
{
  unsigned long currentTime = millis();
  if ((currentTime - UltimoTiempo) > 1000)  
  {
    detachInterrupt(digitalPinToInterrupt(Sensor));
    Flujo_l_min = Contador_pulsos / 7.5;  // Cálculo de la tasa de flujo en L/min
    Flujo_ml = (Flujo_l_min / 60) * 1000;  // Cálculo del flujo acumulado en mL
    Flujo_Litros = (Flujo_l_min/60); // Cálculo del dlujo acumulado en litros
    mililitros_Totales += Flujo_ml;  // Acumulación del flujo total en mL
    Contador_pulsos = 0;  // Reiniciar el contador de pulsos
    UltimoTiempo = currentTime;  // Actualizar el tiempo anterior
    
    Serial.print("Tasa de flujo: ");
    Serial.print(Flujo_l_min);
    Serial.print(" L/min - Flujo acumulado: ");
    Serial.print(mililitros_Totales);
    Serial.println(" mL");
    attachInterrupt(digitalPinToInterrupt(Sensor), Contador_pulsoser, FALLING);
  }
}
void Contador_pulsoser()
{
  Contador_pulsos++;
}