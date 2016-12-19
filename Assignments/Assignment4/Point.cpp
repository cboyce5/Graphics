#include "Point.h"

Point::Point() {
	
}

Point::Point(float newX, float newY, float newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

float Point::getX() {
	return x;
}

float Point::getY() {
	return y;
}

float Point::getZ() {
	return z;
}


Point operator*( Point p, float f ) {
	return Point( p.getX() * f, p.getY() * f, p.getZ() * f );
}

Point operator*( float f, Point p ) {
	return Point( p.getX() * f, p.getY() * f, p.getZ() * f );
}

Point operator+( Point a, Point b ) {
	return Point( a.getX() + b.getX(), a.getY()+b.getY(), a.getZ()+b.getZ() );
}