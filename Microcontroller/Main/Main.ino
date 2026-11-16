#include "motor.h"
#include "mqtt_manager.h"
#include "secrets.h"

// You can actually use any of the GPIO available on your ESP32, these are used just as an example in the code (and because i'm using it haha)
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
  setupMqtt(SECRET_WIFI_SSID, SECRET_WIFI_PASS, onFloorRequested);

  handleMqtt();
  publishCurrentFloor(currentFloor);
}

void loop() {
  handleMqtt();
}
