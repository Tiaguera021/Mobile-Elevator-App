#ifndef NETWORK_H
#define NETWORK_H

// Define a new type of function wich will be called as a new floor is solicitated
typedef void (*FloorCommandCallback) (int targetFloor);

// Setup the connection
void setupMqtt(const char* ssid, const char* password, FloorCommandCallback callback);

// Keep the connection open, listening to the phone solicitations
void handleMqtt();

// Publish the new floor, so it can be updated on the phone too
void publichCurrentFloor(int floor);

#endif