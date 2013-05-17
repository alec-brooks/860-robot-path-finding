#pragma config(Sensor, S1,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "config.h"
#include "follow_line.c"
#include "compass.c"
#include "light_sensor.c"
#include "branch_count.c"
#include "types.h"
#include "string_distance.c"
#include "error.c"
#include "hotel.c"

void makeMap(Island &island, int currentIsland){
  int baseDirection = currentDirection();
  bool atLeaf = false;
  int currentEdge = 0;
  while(!atLeaf){
        FollowSegmentTilEnd(island.edges[currentEdge]);
        island.edges[currentEdge].angle -= baseDirection;
        nxtDisplayCenteredTextLine(4, "(%i, %i)", island.edges[currentEdge].angle, island.edges[currentEdge].length);

        BranchAngles ba;
        int branches = countBranches(ba);
        motor[left] = 0;
        motor[right] = 0;
        if(branches == 1) {
          atLeaf = true;
        } else {
          //nxtDisplayCenteredTextLine(4, "%i", branches);
          if(branches < 1 ) {
            panic("No branches");
          } else if(branches > 2) {
            panic("Too many branches");
          }
	        int nextAngle = 9001;
	        for(int i = 0; i < branches; i++) { //Look at possible branches and decide where to go
	            nxtDisplayCenteredTextLine(2, "%i", ba.angles[i] + baseDirection);

	            if( !isOppositeDirection(ba.angles[i], island.edges[currentEdge].angle + baseDirection)) {
								nextAngle = ba.angles[i];
								break;
	            }
	        }
					if(nextAngle > 9000) {
						panic("No new branches");
					}
					PlaySound(soundBeepBeep);
					nxtDisplayCenteredTextLine(6, "Turning to %i", nextAngle);
					//Don't turn all the way, because we might overshoot
					turnToAngle(nextAngle - sgn(angleDifference(nextAngle, currentDirection()))*10 );
					//Make sure we are actully at the line
					turnToLine();
      }
      currentEdge++;
    }
    island.length = currentEdge;
}

task main(){
  calibrateLight();
  calibrateCompass();
  turnToLine();
  Island islands[maxIslands];
  int currentIsland = 0;
  int revisited = -1;

  openLogFile();
  eraseDisplay();

  while(revisited < 0){

    nxtDisplayCenteredTextLine(3, "On island %i", currentIsland+1);
    //find hotel
    FollowLineTilHotel();
    //turnToAngle(currentDirection() + 180);
    turnToLine();

    //make map
    makeMap(islands[currentIsland], currentIsland);
    //Check if same as map 1
    for(int i = 0; i < currentIsland; i++) {
	    if( (editDistance(islands[i], islands[currentIsland]) < ISLAND_THRESHOLD)) {
	      revisited = i;
	    }
	  }
	  if(revisited < 0) {
	    nxtDisplayCenteredTextLine(3, "Travelling!");
	    //wait10Msec(100);
	    travel();
	  }
	  currentIsland++;
  }
  closeLogFile();
  PlaySound(soundBeepBeep);
  nxtDisplayCenteredTextLine(3, "Back on island %i", revisited+1);
  wait10Msec(1000);

}
