#ifndef SECRETS_EXAMPLE_H
#define SECRETS_EXAMPLE_H

// We must connect the ESP32 to an internet so he can connect to the MQTT server
static const char* SECRET_WIFI_SSID = "Your internet SSID here";
static const char* SECRET_WIFI_PASS = "Your internet password here";

static const char* SECRET_BROKER_LINK = "The server adress of your broker MQTT";
static const int SECRET_BROKER_PORT = 0;
static const char* SECRET_TOPIC_COMMAND = "The publish command directory. Example: test/move_elevator";
static const char* SECRET_TOPIC_STATUS = "The subscribe command directory. Example: test/watch_elevator";

#endif