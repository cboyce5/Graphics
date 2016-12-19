#pragma once

class Point {
private: 
	float x;
	float y;
	float z;

public:
	Point();
	Point(float newX, float newY, float newZ);
	float getX();
	float getY();
	float getZ();
};

Point operator*( Point p, float f ); // multiplies a Point by a float
Point operator*( float f, Point p ); // multiplies a float by a Point
Point operator+( Point a, Point b ); // adds two Points together