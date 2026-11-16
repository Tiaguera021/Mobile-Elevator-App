#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "mqtt_manager.h"
#include "secrets.h"

static WiFiClient espClient;
static PubSubClient client(espClient);
static FloorCommandCallback onCommandReceived = nullptr;

static void internalMqttCallback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  int targetFloor = message.toInt();

  if (onCommandReceived != nullptr) {
    onCommandReceived(targetFloor);
  }
}

static void connectWiFi(const char* ssid, const char* password) {
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
}

static void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to HiveMQ broker...");
    String clientId = "ESP32_Elevator_" + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Connected!");
      client.subscribe(SECRET_TOPIC_COMMAND);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 2 seconds...");
      delay(2000);
    }
  }
}

void setupMqtt(const char* ssid, const char* password, FloorCommandCallback callback) {
  onCommandReceived = callback;
  connectWiFi(ssid, password);

  client.setServer(SECRET_BROKER_LINK, SECRET_BROKER_PORT);
  client.setCallback(internalMqttCallback);
}

void handleMqtt() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();
}

void publishCurrentFloor(int floor) {
  if (client.connected()) {
    String payload = String(floor);
    client.publish(SECRET_TOPIC_STATUS, payload.c_str(), true);
    Serial.println("Published current floor: " + payload);
  }
}