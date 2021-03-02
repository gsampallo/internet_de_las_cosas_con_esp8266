#include <ESP8266WiFi.h>

const char* ssid = "your-ssid";
const char* password = "your-password";

WiFiServer server(80);

void setup(void) {

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }   

    Serial.println("");
    Serial.print("WiFi Connected");     

    server.begin();
    Serial.println("Server started");

    Serial.println(WiFi.localIP());
}

void loop() {
    // Check if a client has connected
    WiFiClient client = server.available();
    if(!client) {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while (!client.available()) {
        delay(1);
    }    

    // Read the first line of the request
    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();

    // Match the request
    int val;
    if (req.indexOf("/gpio/0") != -1) {
        val = 0;
    } else if (req.indexOf("/gpio/1") != -1) {
        val = 1;
    } else {
        Serial.println("invalid request");
        client.stop();
        return;
    }    

    // Set GPIO2 according to the request
    digitalWrite(2, val);

    client.flush();

    // Prepare the response
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
    s += (val) ? "high" : "low";
    s += "</html>\n";   

    // Send the response to the client
    client.print(s);
    delay(1);
    Serial.println("Client disconnected");     
}