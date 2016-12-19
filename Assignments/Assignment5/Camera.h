#pragma once

class Camera {
	private:
		float x;
		float y;
		float z;
		float phi;
		float theta;
		float zoom;
	public:
		Camera(float z);
		void recomputeOrientation(float carX, float carY, float carZ);
		float getX();
		float getY();
		float getZ();
		float getZoom();
		float getTheta();
		float getPhi();
		void setX(float newX);
		void setY(float newY);
		void setZ(float newZ);
		void setZoom(float z);
		void setPhi(float p);
		void setTheta(float t);
};