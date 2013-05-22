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

string graphName = "Map.txt";
TFileHandle graphfile;
TFileIOResult result;
short size = 1024;

void writeGraph(Graph & graph) {
	string graphName = "Map.txt";
	TFileHandle graphfile;
	TFileIOResult result;
	short size = 1024;
	OpenWrite(graphfile, result, graphName, size);
	string buff = "";
	string header = "nNode\t| Neighbours\n";
	string lineStart = "%i\t\t| ";
	string line = " %i";
	WriteText(graphfile, result, header);
	for(int i = 0; i<graph.nNodes; i++){
		StringFormat(buff, lineStart, i);
		WriteText(graphfile, result, buff);
		for(int j = 0;j<graph.nNodes; j++){
			if(graph.adjacency[i][j].length>0){
				StringFormat(buff, line, j);
				WriteText(graphfile, result, buff);
			}
		}
		WriteText(graphfile, result, "\n")
	}
	Close(graphfile, result);
}



task main(){
	calibrateLight();
	calibrateCompass();
	Delete(graphName,result);
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
		currentNode = exploreNewNode(graph, stack, currentNode, lastEdge);
	}
	motor[left] = 0;
	motor[right] = 0;
	writeGraph(graph);
	nxtDisplayCenteredTextLine(3, "Wrote graph to file");
	wait10Msec(1000);

}