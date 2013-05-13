#pragma config(Sensor, S1,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "config.h"
#include "follow_line.c"
#include "compass.c"
#include "branch_count.c"

task main() {
  calibrateLight();
  calibrateCompass();

  int found = FollowSegmentTilEnd();
  int branchCount = 0;
  if(found==FOUND_NODE){
      branchCount = countBranches();
  }
  motor[left] = 0;
  motor[right] = 0;
  nxtDisplayCenteredTextLine(3, "number of branches = %i", branchCount);
  wait10Msec(1000);
}
