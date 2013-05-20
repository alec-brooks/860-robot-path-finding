#pragma config(Sensor, S1,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "config.h"
#include "follow_line.c"
#include "compass.c"
#include "light_sensor.c"

task main() {
  calibrateLight();
  calibrateCompass();
  wait10Msec(100);

  int found = FOUND_ERROR;
  /*while(found != FOUND_HOTEL) {
    found = FollowSegmentTilEnd();
    if(FOUND_CAN) {
      nxtDisplayCenteredTextLine(3, "CAN");
    } else if(FOUND_NODE) {
      nxtDisplayCenteredTextLine(3, "NODE");
		  motor[left] = 0;
		  motor[right] = 0;
	    //wait10Msec(200);
    }
  }*/
  found = FollowLineTilHotel();
  motor[left] = 0;
  motor[right] = 0;
  eraseDisplay();
  PlaySound(soundBeepBeep);
  nxtDisplayCenteredTextLine(3, "At the hotel");
  wait10Msec(1000);
}
