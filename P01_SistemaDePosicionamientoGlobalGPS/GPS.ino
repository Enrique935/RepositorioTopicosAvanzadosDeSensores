#include <SoftwareSerial.h>

//Configura los pines para la comunicacion con el modulo GPS
const int gpsTxPin =4; //Transmit Pin 
const int gpsRxPin =3; //Recive Pin

//Ininicializa un onjeto SofwareSerial para comunicarse con el modulo GPS
SoftwareSerial gpsSerial(gpsTxPin,gpsRxPin);

void setup() {
//Inicializa la comunicacion serial con la computadora
Serial.begin(9600);

//Inicializa la comunicacion serial con el modulo GPS
gpsSerial.begin(9600);

}

void loop(){
//Si hay datos disponibles en el modulo GPS leelos y envialos

while (gpsSerial.available() >0) {
char c = gpsSerial.read();
//Serial.write(c);
    // Variable para almacenar la línea actual
    static String currentLine = "";

    // Verifica si se ha completado una línea
    if (c == '\n') {
      // Procesa la línea si comienza con "$GPGGA"
      if (currentLine.startsWith("$GPGGA")) {
        // Busca la posición de las coordenadas en la línea
        int commaIndex = currentLine.indexOf(',');

        // Extrae la latitud y longitud como cadenas
        String latitudeStr = currentLine.substring(currentLine.indexOf(',', commaIndex + 1) + 1, currentLine.indexOf(',', currentLine.indexOf(',', commaIndex + 1) + 1));
        String longitudeStr = currentLine.substring(currentLine.indexOf(',', currentLine.indexOf(',', currentLine.indexOf(',', commaIndex + 1) + 1) + 1) + 1);
        int firstCommaPos = longitudeStr.indexOf(',');
        longitudeStr = longitudeStr.substring(0, firstCommaPos);

        // Imprime los valores (puedes comentar esta línea después de verificar)
        Serial.println(currentLine);
        Serial.print("Latitud:");
        Serial.println(latitudeStr);
        Serial.print("Longitud:");
        Serial.println(longitudeStr);

        // Limpia la línea actual para la próxima iteración
        currentLine = "";
      } else {
        // Si la línea no comienza con "$GPGGA", limpia la línea actual
        currentLine = "";
      }
    } else {
      // Agrega el carácter a la línea actual
      currentLine += c;
    }
}
}