#pragma config(Sensor, S2,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "compass.c"
#include "light_sensor.c"
#include "types.h"

int countBranches( BranchAngles &branchAngles ) {
	//start spin
	PlaySound(soundFastUpwardTones);

	hogCPU();
  direction = RIGHT;
	spinInDirection();

	int startDirection = currentDirection();
	bool halfway = false;
	int nodeCount = 0;
	bool wasDark = isDark();

	while(!halfway || (angleDifference(currentDirection(), startDirection) < 0)){

		if(!halfway && (angleDifference(currentDirection(), startDirection) < -90)){
			halfway = true;
		}

		if(!wasDark && isDark()) {
		  PlaySound(soundBlip);
		  branchAngles.angles[nodeCount] = currentDirection();
			nodeCount++;
		}
		wasDark = isDark();
		abortTimeslice();
	}
	releaseCPU();

	return nodeCount;
}
