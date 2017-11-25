// Importa as biblitecas
#include "ESP8266WiFi.h"
#include <aREST.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 2  //D4
#define RST_PIN 15 

//Cria uma instancia MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Cria a instancia rest
aREST rest = aREST();

// Parametros do WiFi 
const char* ssid = "";
const char* password = "";

//A porta a escutar para conecoes TCP
#define LISTEN_PORT  80

// Cria uma instancia do servidor na porta definida
WiFiServer server(LISTEN_PORT);

String uid, acess;

void setup(){
   
    Serial.begin(115200);  //Inicia a comunicação serial
    SPI.begin();        //Inicia o SPI
    mfrc522.PCD_Init();//Inicia o MFRC522 

    //Inicia as variaveis e expoe elas a API REST
    rest.variable("uid", &uid);
    rest.variable("acess", &acess);

    // Da um nome e um id ao ESP 
    rest.set_id("2");
    rest.set_name("rfid");

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

void loop(){
    digitalWrite(LED_BUILTIN, LOW);

    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()){
        return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()){
        return;
    }
    //Show UID on serial monitor
    Serial.println();
    Serial.print("UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    uid = content;
    Serial.println();
    if (content.substring(1) == "21 29 B0 A9" || content.substring(1) == "74 C6 45 7D"){//change UID of the card that you want to give access
        acess = "Acesso Permitido";
        Serial.println(acess);
        Serial.println("Welcome Mr.Robot ");
        Serial.println("Have FUN ");
        //delay(1000);
    }
    
    else{
        acess = "Acesso Negado";
        Serial.println(acess);
        //delay(1000);
    }

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
