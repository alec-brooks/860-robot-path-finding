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

task main(){
	calibrateLight();
	calibrateCompass();
	ExploreStack stack;
	Graph graph;

	initStack(stack);
	initGraph(graph);
	Stub stub;
	Edge lastEdge;

	int currentNode = -1;
	//go to node
	FollowSegmentTilEnd(lastEdge);
	currentNode = exploreNewNode(graph, stack, currentNode, lastEdge);
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
		FollowSegmentTilEnd(lastEdge);
		currentNode = exploreNewNode(graph, stack, currentNode, lastEdge);
	}
	motor[left] = 0;
	motor[right] = 0;
	eraseDisplay();
	nxtDisplayCenteredTextLine(3, "%i nodes found", graph.nNodes);
	wait10Msec(1000);
}
