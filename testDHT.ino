//Biblioteca 
#include "DHT.h"

// Pino
#define DHTPIN 5

// Define o tipo do sensor 
#define DHTTYPE DHT11

// Inicia o sensor 
DHT dht(DHTPIN, DHTTYPE, 15);

void setup() {

// Inicia a serial
Serial.begin(115200);

// Incia o DHT
dht.begin();
}

void loop() {

//le a umidade
float h = dht.readHumidity();
// le a tempeartura
float t = dht.readTemperature();

// Mostra os dados na serial 
Serial.print("Umidade: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperatura: ");
Serial.print(t);
Serial.println(" *C ");

// Tempo ate a proxima leitura
delay(1000);

}
