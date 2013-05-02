#pragma config(Sensor, S1,     light,          sensorLightActive)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#ifndef COMPASS_C
#define COMPASS_C

#include "config.h"
#include "light_sensor.c"

float encoder_k;

void saveCalib(float k) {
  TFileHandle calibFile;
  TFileIOResult result;
  int size = 8;
  string name = "encoderCalib.dat";
  Delete(name, result);
  OpenWrite(calibFile, result, name, size);
  WriteFloat(calibFile, result, k);
  Close(calibFile, result);
}

void performCompassCalibration() {
  bool wasDark;
  motor[left] = SPEED;
  motor[right] = -SPEED;


  for(;;) {
    wasDark = isDark();
    nxtDisplayString(0, "%i", SensorValue[light]);
    if(!wasDark && isDark()) break;
  }

  int startLeftWheel = nMotorEncoder[left];
  int startRightWheel = nMotorEncoder[right];

  time1[T1] = 0;

  for(;;) {
    wasDark = isDark();
    nxtDisplayString(1, "%i", SensorValue[light]);
    if(!wasDark && isDark()) break;
  }

  motor[right] = 0;
  motor[left] = 0;
  int endLeftWheel = nMotorEncoder[left];
  int endRightWheel = nMotorEncoder[right];

  int elapsed = time1[T1];

  float k = ((endLeftWheel - startLeftWheel)
          - (endRightWheel - startRightWheel))/360.0;
  nxtDisplayBigTextLine(3, "%.2f", k);

  saveCalib(k);
  encoder_k = k;
}

void readCompassCalibration() {
  float k;
  string calibFileName = "encoderCalib.dat";

  TFileHandle calibFile;
  TFileIOResult result;
  int size = 8;
  OpenRead(calibFile, result, calibFileName, size);
  ReadFloat(calibFile, result, k);
  Close(calibFile, result);
  encoder_k = k;
}

void calibrateCompass(){

  nMotorEncoder[left] = 0;
  nMotorEncoder[right] = 0;

  string calibFileName = "encoderCalib.dat";

  TFileHandle calibFile;
  TFileIOResult result;
  int size = 8;
  FindFirstFile(calibFile, result, calibFileName, calibFileName, size);

  if(result==0){
    readCompassCalibration();
  } else{
    performCompassCalibration();
  }
}

float getCompass(float k) {
 return ((nMotorEncoder[left] - nMotorEncoder[right])/k);
}

int currentDirection(void) {
	int comp = (int) getCompass(encoder_k);
	while( comp < 0 ) comp += 360;
	return comp; 
}

/**
 * Return the angle of a with respect to b,
 * (In degrees, between -180 and 180
 */
int angleDifference(int a, int b) {
  int ab = (a - b);
  while(ab > 180) ab -= 360;
  while(ab < -180) ab += 360;
  return ab;
}

#endif
