// Importa as biblitecas
#include "ESP8266WiFi.h"
#include <aREST.h>
#include "DHT.h"

// DHT11
#define DHTPIN 0
#define DHTTYPE DHT11

// Cria a instancia rest
aREST rest = aREST();

// Inicia o sensor
DHT dht(DHTPIN, DHTTYPE, 15);

// Parametros do WiFi 
const char* ssid = "WIFIDOBOM";
const char* password = "ronaldopele";
 
//A porta a escutar para conecoes TCP
#define LISTEN_PORT  80

// Cria uma instancia do servidor na porta definida
WiFiServer server(LISTEN_PORT);

// Variaveis da a serem usadas na API
int temperature;
int humidity;

void setup(void){  
  // Inicia a serial
  Serial.begin(115200);
  
  // inicia o DHT 
  dht.begin();

  //Inicia as variaveis e expoe elas a API REST
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
    
  // Da um nome e um id ao ESP 
  rest.set_id("1");
  rest.set_name("sensor_module");
  
  // Conecta ao WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Deu bom, WiFi conectado");
 
  // Inicia o servidor
  server.begin();
  Serial.println("Servidor iniciado");
  
  // Mostra o endereco IP
  Serial.println(WiFi.localIP());
  
}

void loop() {
  
  // Le a temperatura e umidade
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  // lida com as chamadas REST
  // Verifica se o cliente esta conectado e envia os dados
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
 
}
