#include <CayenneMQTTESP8266.h>

char ssid[] = "NETWORK_SDD";
char wifiPassword[] = "PASSWORD";

char username[] = "username";
char password[] = "password";
char clientID[] = "client_id";

unsigned long lastMillis = 0;

int contador = 0;

void setup() {
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}



void loop() {
  Cayenne.loop();
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    Cayenne.virtualWrite(0, contador);
  }

  contador++;

  delay(1000);

}
