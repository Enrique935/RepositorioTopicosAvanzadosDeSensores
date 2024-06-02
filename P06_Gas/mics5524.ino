void setup() {
  Serial.begin(9600);
}

void loop() {
  //Lectura analógica del sensor
  int sensor = analogRead(A0);
  //Conversión del valor ADC a valor en volts 0 - 5V
  float volts = sensor * (5.0 / 1023.0);
  
  // Cálculo de la resistencia del sensor para Rload = 10kohms
  float RS = ((5.0 * 10.0) / volts) - 10.0;
  //Cálculo de concentraciones para cada gas:

  // Monóxido de carbono
    float COppm = 60.0 * pow(RS, -1.0);
  // Etanol
    float C2H6Oppm = 15.0 * pow(RS, -1.0);
  // Hidrógeno
    float H2ppm = 70.0 * pow(RS, -1.0);
  // Amoniaco
    float NH3ppm = 10.0 * pow(RS, -1.0);
  // Metano
    float CH4ppm = 30.0 * pow(RS, -1.0);
  // Imprimir valores de interés según el gas esperado en el entorno
  //Serial.print("CO: ");
  Serial.println(COppm);
  //Serial.println(" ppm");
/*
  Serial.print("C2H6O: ");
  Serial.print(C2H6Oppm);
  Serial.println(" ppm");

  Serial.print("H2: ");
  Serial.print(H2ppm);
  Serial.println(" ppm");

  Serial.print("NH3: ");
  Serial.print(NH3ppm);
  Serial.println(" ppm");

  Serial.print("CH4: ");
  Serial.print(CH4ppm);
  Serial.println(" ppm");
*/
  delay(1000); 
}