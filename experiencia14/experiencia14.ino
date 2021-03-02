#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

const char* ssid = "NETWORK_SDD";
const char* password = "PASSWORD";

char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = NNNNNN;
char* writeAPIKey = "MMMMMMMMMMMMMMMM";
unsigned int campo = 1;  
const unsigned long postingInterval = 12 * 1000;
long lastUpdateTime = 0; 

WiFiClient client;  
int contador = 0;

void setup() {
  while (WiFi.status() != WL_CONNECTED) { 
    WiFi.begin( ssid, password );
    delay(2500);
  } 
  ThingSpeak.begin(client);
}

void loop() {
  if (millis() - lastUpdateTime >=  postingInterval) {
    lastUpdateTime = millis();
    int  writeSuccess = ThingSpeak.writeField( channelID, campo, contador, writeAPIKey );
  }

  contador++;
  delay(1000);
}
