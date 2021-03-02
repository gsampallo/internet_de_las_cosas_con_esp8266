#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "NETWORK_SDD";
const char* password = "PASSWORD";
const char* mqtt_server = "MQTT_SERVER"; // 198.41.30.241

WiFiClient espClient;
PubSubClient client(espClient);

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
  pinMode(2,INPUT);
}

void reconnect() {

  while (!client.connected()) {

    if (client.connect("cliente")) {
      Serial.println("connected");

      client.subscribe("experiencia13");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
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

void callback(char* topic, byte* payload, unsigned int length) {
  String s = String((char*)payload);
  if(s == "ABRIR") {
    abrir();
  } 

}

void abrir() {
    digitalWrite(2,HIGH);
    delay(5000);
    digitalWrite(2,LOW);
    client.publish("PUERTA","CERRAR");
}

void void loop() {
    
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int estadoBoton = digitalRead(2);

  if(estadoBoton == HIGH) {
      client.publish("PUERTA","ABRIR");
  }

  delay(100);

}