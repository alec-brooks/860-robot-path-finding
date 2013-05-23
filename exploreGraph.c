#pragma config(Sensor, S2,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "follow_line.c"

#include "branch_count.c"
#include "types.h"
#include "stack.c"
#include "graph.c"
#include "compass.c"
#include "cartesian.c"

void goToNode(Graph & graph, int from, int to){
	Path path;
	Edge dummy;
	nxtDisplayCenteredTextLine(4, "Going to %i", to);
	//perform dij on graph
	int steps = dijkstra(graph, from, to, path);
	//follow path until node reached
	for(int i = 0; i < steps; i++){
		nxtDisplayCenteredTextLine(3, "Known node %i", path.branches[i].node);
		turnToAngle(path.branches[i].angle, 15);
		turnToLine();
		FollowSegmentTilEnd(dummy);
	}
	nxtDisplayCenteredTextLine(3, "Known node %i", to);
	nxtDisplayCenteredTextLine(4, "Got to %i", to);

}

int exploreNewNode(Graph & graph, ExploreStack & stack, int lastNode, Edge & lastEdge){
	BranchAngles branches;
	Stub stub;
	int newNode = addNode(graph);
	nxtDisplayCenteredTextLine(3, "New node %i", newNode);
	if(lastNode>=0){
		addEdge(graph, lastNode, newNode, lastEdge);
	}

	int nBranches = countBranches(branches);

	for(int i =0; i<nBranches; i++){
		if(!isOppositeDirection(branches.angles[i], lastEdge.angle) || lastNode<0){
			stub.node = newNode;
			stub.angle = branches.angles[i];
			push(stack, stub);
		}
	}
	return newNode;
}

void recordMove(Trail & trail, Edge & newEdge, int newNode) {
	trail.nodes[trail.length] = newNode;
	if(trail.length > 0) {
		Point relative;
		edgeToPoint(newEdge, relative);
	  addPoints(relative, trail.moves[trail.length-1], trail.moves[trail.length]);
	} else {
	  edgeToPoint(newEdge, trail.moves[trail.length]);
  }
	trail.length++;
}

int isVisitedNode(Locations & locs, Trail & trail, Point & new) {
	for(int i = trail.length-1; i >= 0; i++) {
		if(isSamePoint(new, locs.points[trail.nodes[i]])) {
			return trail.nodes[i];
		}
	}
	return -1;
}
