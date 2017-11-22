//Bibliotecas
#include "DHT.h"
#include <Ultrasonic.h>

// Pino
#define DHTPIN 2

// Define o tipo do sensor 
#define DHTTYPE DHT11

// define o sensor dht
DHT dht(DHTPIN, DHTTYPE);

//cria o objeto do sensor ultrasonico
Ultrasonic ultrasonic(16, 0);

void setup() {
// Inicia a serial
Serial.begin(115200);

// Incia o DHT
dht.begin();

pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
digitalWrite(LED_BUILTIN, HIGH);

//le o ldr
int ldrValue = analogRead(A0); 
//float voltage = ldrValue * (3.3 / 1023.0);//Converte o input analogico(0-1023) para voltagem
//le a umidade
float h = dht.readHumidity();
// le a tempeartura
float t = dht.readTemperature();

// Mostra os dados na serial
Serial.print("Ultrasonico: ");
Serial.print(ultrasonic.distanceRead());
Serial.print("cm\t");

Serial.print("LDR: ");
Serial.print(ldrValue); 
Serial.print(" \t");

Serial.print("Umidade: ");
Serial.print(h);
Serial.print(" %\t");

Serial.print("Temperatura: ");
Serial.print(t);
Serial.println(" *C ");

// Tempo ate a proxima leitura

delay(1000);
}
