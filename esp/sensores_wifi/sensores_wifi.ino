// Importa as biblitecas
#include "ESP8266WiFi.h"
#include <aREST.h>
#include "DHT.h"
#include <Ultrasonic.h>

// DHT11
#define DHTPIN 13 //D7
#define DHTTYPE DHT11

// cria o objeto do sensor
DHT dht(DHTPIN, DHTTYPE, 15);

//cria o objeto do sensor ultrasonico (D0, D3)
Ultrasonic ultrasonic(16, 0);

// Cria a instancia rest
aREST rest = aREST();

// Parametros do WiFi 
const char* ssid = "";
const char* password = "";
 
//A porta a escutar para conecoes TCP
#define LISTEN_PORT 80

// Cria uma instancia do servidor na porta definida
WiFiServer server(LISTEN_PORT);

// Variaveis da a serem usadas na API
int temperature;
int humidity;
int ldrValue;
int distance;


void setup(void){  
  // Inicia a serial
  Serial.begin(115200);
  
  // inicia o DHT 
  dht.begin();

  //Inicia as variaveis e expoe elas a API REST
  temperature = 30;
  humidity = 40;
  ldrValue = 100;
  distance = 5; 
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
  rest.variable("ldr", &ldrValue);
  rest.variable("distance", &distance);
  
    
  // Da um nome e um id ao ESP 
  rest.set_id("1");
  rest.set_name("sensors");
  
  // Conecta ao WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
 
  // Inicia o servidor
  server.begin();
  Serial.println("Servidor iniciado");
  
  // Mostra o endereco IP
  Serial.println(WiFi.localIP());

  pinMode(BUILTIN_LED, OUTPUT);  
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);

  //le o ldr
  ldrValue = analogRead(A0); 

  //le o ultrasonico
  distance = ultrasonic.distanceRead();
    
  // Le a temperatura e umidade
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  // lida com as chamadas REST
  // Verifica se o cliente esta conectado e envia os dados
  WiFiClient client = server.available();
  /*
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  */
  rest.handle(client);
  Serial.println("Dados enviados!");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
 
}
