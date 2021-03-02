#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "NETWORK_SDD";
const char* password = "PASSWORD";
const char* mqtt_server = "MQTT_SERVER"; // 198.41.30.241

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
  pinMode(2,OUTPUT);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String s = String((char*)payload);
  if(s == "On") {
    digitalWrite(2,HIGH);
  } else if(s == "Off") {
    digitalWrite(2,LOW);
  }
  
}

void reconnect() {

  while (!client.connected()) {

    if (client.connect("cliente")) {
      Serial.println("connected");

      client.subscribe("experiencia12");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void destellar(int destellos) {
  digitalWrite(2,LOW);
  for(int c = 0; c<destellos; c++) {
    digitalWrite(2,HIGH);
    delay(200);
    digitalWrite(2,LOW);
    delay(200);
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
