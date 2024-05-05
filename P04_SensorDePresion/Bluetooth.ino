#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include "BluetoothSerial.h"

Adafruit_MPL3115A2 baro;
BluetoothSerial SerialBT;

void setup() {
    Serial.begin(9600);
    SerialBT.begin("Rendón_Industries"); 

    if (!baro.begin()) {
        Serial.println("No se pudo encontrar el sensor");
        return;
    }
}

void loop() {
    float pascales = baro.getPressure();
    Serial.print("Presión: ");
    Serial.println(pascales);
    SerialBT.print("Presión: ");
    SerialBT.println(pascales);

    float altitud = baro.getAltitude();
    Serial.print(altitud);
    Serial.println(" metros");
    SerialBT.print(altitud);
    SerialBT.println(" metros");

    float temp = baro.getTemperature();
    Serial.print(temp);
    Serial.println(" °C");
    SerialBT.print(temp);
    SerialBT.println(" °C");

    Serial.println(" ");
    Serial.println(" ");
    SerialBT.println(" ");
    SerialBT.println(" ");

    delay(50);
}

