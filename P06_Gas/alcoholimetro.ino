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
  // Etanol concentración
    float C2H6Oppm = 15.0 * pow(RS, -1.0);
  //Nivel de alcohol en la sangre
    float BAC = C2H6Oppm*0.004;
    //Serial.println(BAC);
    Serial.println(C2H6Oppm);
  delay(1000); 
}
