#pragma config(Sensor, S1,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "config.h"

typedef struct{
  int angle;//in degrees
  int length;//in pivots
} Edge;

typedef struct{
  Edge edges[ISLAND_SIZE];
  int length;
} Island;
