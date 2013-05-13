#include "map.c"
#include "config.h"

#define delCost 100
#define insCost 100


int subCost(Edge &frm, Edge &to){
	 return abs(frm.length - to.length) + abs(angleDifference(frm.angle, to.angle));
}

int min(int a, int b, int c){
	if( a < b && a < c) {
		return a;
	} else {
		return (b < c) ? b : c;
	}
}

int editDistance(Island &fromIsl, Island &toIsl){
	int costTable[ISLAND_SIZE][ISLAND_SIZE];
	
	//Initialisation
	for(int i=0;i<fromIsl.length; i++){
		costTable[i][0] = i*insCost;
	}
	
	for(int j = 0; j < toIsl.length; j++) {
		costTable[0][j] = j*delCost;
	}
	
	//Fill the table
	for(int i = 1; i < fromIsl.length; i++) {
		for(int j = 1; j < toIsl.length; j++) {
			int cost = min(
				costTable[i-1][j-1] + subCost(fromIsl.edges[i], toIsl.edges[j]),
				costTable[i][j-1] + insCost,
				costTable[i-1][j] + delCost
			);
			costTable[i][j] = cost;
		}
	}
	
	return costTable[fromIsl.length][toIsl.length];
}
