#pragma config(Sensor, S2,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard

#include "config.h"
#include "follow_line.c"
#include "compass.c"
#include "branch_count.c"
#include "types.h"
#include "stack.c"
#include "graph.c"
#include "exploreGraph.c"

void announceCan(int currentNode) {
    motor[left] = 0;
    motor[right] = 0;
    PlaySound(soundBeepBeep);
    nxtDisplayCenteredTextLine(3, "Can detected at");
    nxtDisplayCenteredTextLine(4, "node %i", currentNode);
    wait10Msec(500);
}

task main(){
  calibrateLight();
  calibrateCompass();
  ExploreStack stack;
  Graph graph;

  initStack(stack);
  initGraph(graph);
  Stub stub;

  int currentNode = -1;
  int canNode = -1;
  //go to node
  currentNode = exploreCurEdge(graph, stack, currentNode);
  if(detectCan()) {
      canNode = currentNode;
      announceCan(currentNode);
  }
  //while not empty
  while(!empty(stack)){
    pop(stack, stub);
		motor[left] = 0;
		motor[right] = 0;
    goToNode(graph, currentNode, stub.node);
    currentNode = stub.node;
    turnToAngle(stub.angle, 15);
    turnToLine();
    nxtDisplayCenteredTextLine(4, "Exploring...");
    int stackSize = stack.top;
    currentNode = exploreCurEdge(graph, stack, currentNode);
	  if(stackSize == stack.top && detectCan()) {
	      canNode = currentNode;
	      announceCan(currentNode);
	  }
  }
  motor[left] = 0;
  motor[right] = 0;
  eraseDisplay();
  nxtDisplayCenteredTextLine(3, "%i nodes found", graph.nNodes);
  wait10Msec(500);


  if(canNode >= 0) {
    goToNode(graph, currentNode, canNode);
	  motor[left] = 0;
	  motor[right] = 0;
	  eraseDisplay();
	  nxtDisplayCenteredTextLine(3, "Can was here");
	  wait10Msec(500);
  } else {
	  motor[left] = 0;
	  motor[right] = 0;
	  eraseDisplay();
	  PlaySound(soundLowBuzz);
	  nxtDisplayCenteredTextLine(3, "There was no can");
	  wait10Msec(500);
  }
}
