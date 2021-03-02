#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "NETWORK_SSID";
const char* password = "PASSWORD";
const char* mqtt_server = "MQTT_SERVER";

WiFiClient espClient;
PubSubClient client(espClient);

int i = 0;

void setup() {
  Serial.begin (9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());    

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}

void reconnect() {

  while (!client.connected()) {

    if (client.connect("cliente")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  client.publish("TOPICO1",String(i).c_str());   
  i++; 
  delay(1000);
}
