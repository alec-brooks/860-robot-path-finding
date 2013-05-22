
#include "types.h"
#include "config.h"

void edgeToPoint(Edge & e, Point & p) {
	p.x = e.length * sinDegrees(e.angle);
	p.y = e.length * cosDegrees(e.angle);
}

void addPoints(Point & a, Point & b, Point & sum) {
	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
}

float pointDistance(Point & a, Point & b) {
	return sqrt( pow(b.x - a.x, 2) + pow(b.y - a.y, 2) );
}

bool isSamePoint(Point & a, Point & b) {
	return pointDistance(a, b) < MIN_NODE_DISTANCE;
}
