
#include <DHT11.h>
#include <Wire.h>
#include <AHT20.h>
AHT20 aht20;
DHT11 dht11(2);

void setup() {
    Serial.begin(9600);

    Wire.begin(); //Join I2C bus
  //Check if the AHT20 will acknowledge
  if (aht20.begin() == false)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1);
  }
  Serial.println("AHT20 acknowledged.");

}

void loop() {
    int DHT11_temperature = 0;
    int DHT11_humidity = 0;

    int result = dht11.readTemperatureHumidity(DHT11_temperature, DHT11_humidity);

    if (result == 0) {
        Serial.print("DHT11_Temperature: ");
        Serial.print(DHT11_temperature);
        Serial.print(" °C\t DHT11_Humidity: ");
        Serial.print(DHT11_humidity);
        Serial.println(" %");
        Serial.println(" ");
    } 

    if (aht20.available() == true)
  {
    //Get the new temperature and humidity value
    float AHT_temperature = aht20.getTemperature();
    float AHT_humidity = aht20.getHumidity();

    //Print the results
    Serial.print("AHT20_Temperature: ");
    Serial.print(AHT_temperature, 2);
    Serial.print(" C\t");
    Serial.print("AHT20_Humidity: ");
    Serial.print(AHT_humidity, 2);
    Serial.print("% RH");

    Serial.println();
  }
}
