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

int exploreCurEdge(Graph & graph, ExploreStack & stack, int currentNode){
  Edge curEdge;
  BranchAngles branches;
  Stub stub;
  FollowSegmentTilEnd(curEdge);
  int nextNode = addNode(graph);
  nxtDisplayCenteredTextLine(3, "New node %i", nextNode);
  if(currentNode>=0){
    addEdge(graph, currentNode, nextNode, curEdge);
  }

  int nBranches = countBranches(branches);

  for(int i =0; i<nBranches; i++){
    if(!isOppositeDirection(branches.angles[i], curEdge.angle) || currentNode<0){
		    stub.node = nextNode;
		    stub.angle = branches.angles[i];
		    push(stack, stub);
    }
  }
  return nextNode;
}
