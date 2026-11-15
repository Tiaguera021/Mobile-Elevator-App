#ifndef MOTOR_H
#define MOTOR_H

void setupMotor(int pin1, int pin2);
int  initMotor(int currentLevel, int desiredLevel);
void stopMotor();

#endif