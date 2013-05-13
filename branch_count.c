#pragma config(Sensor, S1,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "compass.c"
#include "light_sensor.c"

int countBranches(void) {
	//start spin
	motor[left] = -SPEED;
	motor[right] = SPEED;
	int startDirection = currentDirection();
	bool halfway = false;
	int nodeCount = 0;
	bool wasDark = isDark();
	while(!halfway || (angleDifference(currentDirection(), startDirection) < 0)){
		if(!halfway && (angleDifference(currentDirection(), startDirection) < 0)){
			halfway = true;
		}
		if(!wasDark && isDark()){
			nodeCount++;
		}
		wasDark = isDark();
	}
	return nodeCount;
}