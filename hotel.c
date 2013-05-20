<<<<<<< HEAD
#pragma config(Sensor, S1,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "types.h"
#include "config.h"
#include "follow_line.c"
#include "light_sensor.c"

bool followingSegments = false;
bool finishedFollowingSegments = false;

task FollowSegments(){
  Edge edge;
  followingSegments = true;
  finishedFollowingSegments = false;
  while(followingSegments){
    FollowSegmentTilEnd(edge);
    if(followingSegments) {
	    turnToLine();
	    if( isOppositeDirection(currentDirection(), edge.angle) ){
	      spinInDirection();
	      wait10Msec(40);
	      turnToLine();
	    }
	  } else {
	    turnToAngle(currentDirection() + 150); //Almost turn around
	    turnToLine();
	  }
  }
  finishedFollowingSegments = true;
}

void travel(void){
  motor[left] = TRAVEL_SPEED;
  motor[right] = TRAVEL_SPEED;
  while(!isDark()){
    wait1Msec(1);
  }
  motor[left] = 0;
  motor[right] = 0;
  moveToSensor();
  turnToLine();
}

int FollowLineTilHotel(void) {
  StartTask(FollowSegments);
	bool greyBuffer[8];
	for(int i = 0; i < 8; i++) {
	  greyBuffer[i] = false;
  }
	int index = 0;
	for(;;) {
	  greyBuffer[ (index++) & 0x7 ] = isGrey(); //index modulo 8 (bitmask trick)
		if(isGrey()) {
		  PlaySound(soundBlip);
			bool isAllGrey = true;
			for(int i = 0; i < 8; i++) {
			  if(!greyBuffer[i]) {
			    isAllGrey = false;
			    break;
			  }
		  }
		  if(isAllGrey) {
		    followingSegments = false;
		    break;
		  }
		 }
		wait10Msec(5);
	}
  PlaySound(soundDownwardTones);
	while(!finishedFollowingSegments){
	  wait1Msec(1);
	}
	return FOUND_HOTEL;
}
=======
#pragma config(Sensor, S1,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "types.h"
#include "config.h"
#include "follow_line.c"
#include "light_sensor.c"

bool followingSegments = false;
bool finishedFollowingSegments = false;

task FollowSegments(){
  Edge edge;
  followingSegments = true;
  finishedFollowingSegments = false;
  while(followingSegments){
    FollowSegmentTilEnd(edge);
    if(followingSegments) {
	    turnToLine();
	    if( isOppositeDirection(currentDirection(), edge.angle) ){
	      spinInDirection();
	      wait10Msec(40);
	      turnToLine();
	    }
	  } else {
	    turnToAngle(currentDirection() + 150); //Almost turn around
	    turnToLine();
	  }
  }
  finishedFollowingSegments = true;
}

void travel(void){
  motor[left] = TRAVEL_SPEED;
  motor[right] = TRAVEL_SPEED;
  while(!isDark()){
    wait1Msec(1);
  }
  motor[left] = 0;
  motor[right] = 0;
  moveToSensor();
  turnToLine();
}

int FollowLineTilHotel(void) {
  StartTask(FollowSegments);
	bool greyBuffer[8];
	for(int i = 0; i < 8; i++) {
	  greyBuffer[i] = false;
  }
	int index = 0;
	for(;;) {
	  greyBuffer[ (index++) & 0x7 ] = isGrey(); //index modulo 8 (bitmask trick)
		if(isGrey()) {
		  PlaySound(soundBlip);
			bool isAllGrey = true;
			for(int i = 0; i < 8; i++) {
			  if(!greyBuffer[i]) {
			    isAllGrey = false;
			    break;
			  }
		  }
		  if(isAllGrey) {
		    followingSegments = false;
		    break;
		  }
		 }
		wait10Msec(5);
	}
  PlaySound(soundDownwardTones);
	while(!finishedFollowingSegments){
	  wait1Msec(1);
	}
	return FOUND_HOTEL;
}
>>>>>>> 16a7e5657e89aca3b6604cf288755a9fa1eb314d
