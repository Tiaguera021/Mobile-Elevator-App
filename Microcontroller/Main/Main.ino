#include "motor.h"
#include "network.h"
#include "secrets.h"

const char* WIFI_SSID = WIFI_SSID;
const char* WIFI_PASS = WIFI_PASS;

const int MOTOR_PIN_1 = 25;
const int MOTOR_PIN_2 = 26;

int currentFloor = 0;

void onFloorRequested(int targetFloor){
  Serial.printf("Request received: move from %d to %d\n", currentFloor, targetFloor);

  currentFloor = initMotor(currentFloor, targetFloor);
  publishCurrentFloor(currentFloor);
}

void setup() {
  Serial.begin(115200);
  
  setupMotor(MOTOR_PIN_1, MOTOR_PIN_2);
  setupMqtt(WIFI_SSID, WIFI_PASS, onFloorRequested);

  handleMqtt();
  publishCurrentFloor(currentFloor);
}

void loop() {
  handleMqtt();
}
