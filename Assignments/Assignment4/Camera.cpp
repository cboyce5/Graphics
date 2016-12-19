#include "Camera.h"
#include <math.h>

Camera::Camera(float z) {
	zoom = z;
	theta = 3*M_PI / 2.0;
    phi = M_PI / 1.5;
	recomputeOrientation(0,2,0);
}

void Camera::recomputeOrientation(float carX, float carY, float carZ) {
	x = carX + zoom*sin(phi)*sin(theta);
	y = carY + zoom*(-1*cos(phi));
	z = carZ + zoom*(-1*cos(theta)*sin(phi));
}

float Camera::getX() {
	return x;
}

float Camera::getY() {
	return y;
}

float Camera::getZ() {
	return z;
}

float Camera::getZoom() {
	return zoom;
}

float Camera::getTheta() {
	return theta;
}

float Camera::getPhi() {
	return phi;
}

void Camera::setX(float newX) {
	x = newX;
}

void Camera::setY(float newY) {
	y = newY;
}

void Camera::setZ(float newZ) {
	z = newZ;
}

void Camera::setZoom(float z) {
	zoom = z;
	if (zoom < 0) {
		zoom = 0;
	}
}

void Camera::setPhi(float p) {
	phi = p;
	if (phi <= 0) {
		phi = 0.001;
	}
	else if (phi >= M_PI){
		phi = M_PI - 0.001;
	}
}

void Camera::setTheta(float t) {
	theta = t;
}