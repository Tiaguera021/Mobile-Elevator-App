#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H 

// Define a new type of function wich will be called when a new floor is solicitated
typedef void (*FloorCommandCallback) (int targetFloor);

// Setup the connection
void setupMqtt(const char* ssid, const char* password, FloorCommandCallback callback);

// Keep the connection open, listening to the phone solicitations
void handleMqtt();

// Publish the new floor, so it can be updated on the phone too
void publishCurrentFloor(int floor);

#endif