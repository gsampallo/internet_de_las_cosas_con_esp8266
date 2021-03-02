#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "xxxxxxxxxxxx";

// Your WiFi credentials.
char ssid[] = "NETWORK_SSD";
char pass[] = "PASSWORD";

void setup() {
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}

