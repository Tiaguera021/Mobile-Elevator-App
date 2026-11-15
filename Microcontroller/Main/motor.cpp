#include<Arduino.h>
#include "motor.h"

static int motorPin1;
static int motorPin2;

// This variable will be used while we have no sensor to notice when the elevator finish de movement
const unsigned long DIRECTION_TIME = 3000;
const unsigned long REVERSAL_PAUSE = 1000;
const unsigned long STOP_TIME = 2000;

void setupMotor(int pin1, int pin2){
  motorPin1 = pin1;
  motorPin2 = pin2;

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  stopMotor();
}

void stopMotor(){
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW)
}

int initMotor(int currentLevel, int desiredLevel){
  int position = currentLevel;
  int destiny = desiredLevel;

  if (destiny < 1 || destiny > 3){
    Serial.println("Floor doesn't exist.");
    return;
  }

  if (position < destiny){
    Serial.println("Going Up!");
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(DIRECTION_TIME);
    stopMotor(motorPin1, motorPin2);
    Serial.println("You have reached your floor!");
    return destiny;
  } else if (position > destiny) {
    Serial.println("Goind Down!");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    delay(DIRECTION_TIME);
    stopMotor(motorPin1, motorPin2);
    Serial.println("You have reached your floor!");
    return destiny;
  } else {
    Serial.println("You are already on the selected floor!");
    return position;
  }
}