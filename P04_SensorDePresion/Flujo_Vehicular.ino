#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include "BluetoothSerial.h"

Adafruit_MPL3115A2 baro;
BluetoothSerial SerialBT;

unsigned long tiempoAnterior = 0;
float umbral = 0.7; //Ajusta la sensibilidad de detección de paso.
float referencia = 0;
float diferencia = 0;
bool presionado = false;
float distancia = 2.448; // Distancia media entre ejes del automovil en metros 
char Estado = 'a';
unsigned long tiempoActual =0;
int carros =0;

void setup() {
    Serial.begin(9600);
    SerialBT.begin("Rendón_Industries"); // Asigna un nombre único para tu dispositivo Bluetooth

    if (!baro.begin()) {
        Serial.println("No se pudo encontrar el sensor");
        return;
    }
}

void loop() {
    float pascales = baro.getPressure();

    if (millis() - tiempoAnterior >= 3000) {
        referencia = pascales;
        tiempoAnterior = millis();
    }

    diferencia = pascales - referencia;

    if (diferencia > umbral) {
        presionado = true;
    } else {
        presionado = false;
    }

/////////////////////////MAQUINA DE ESTADOS //////////////////////////////////////////////
    if (presionado==true && Estado == 'a') {Estado = 'b';}

    if(Estado == 'b'){ if (presionado == false){ Estado = 'c'; } }

    if(Estado == 'c'){
        //Empieza a contar

      // Calcula el tiempo que tarda la perturbación en propagarse
        tiempoActual = millis();
        if(presionado == true){Estado = 'd';}

    }

    if(Estado == 'd'){

        float tiempoTranscurrido = (tiempoActual - tiempoAnterior) / 1000.0; // Convertir a segundos
        float velocidadKPH = (distancia / tiempoTranscurrido) * 3.6; // Convertir a km/h
        SerialBT.print("Velocidad: ");
        SerialBT.print(velocidadKPH);
        SerialBT.println(" km/h");

        Estado = 'a';
        carros ++;

    }   

////////////////////////// Fin de maquina de estados //////////////////////////////////

    

    delay(10); // Pequeña pausa para evitar bloqueos
    SerialBT.print(Estado);
    SerialBT.println(" Libre ");
    
    SerialBT.print("Carros: ");
    SerialBT.println(carros);
    

    

}
