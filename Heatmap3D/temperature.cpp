#include "pch.h"
#include "temperature.h"

Temperature::Temperature(float x, float y, float z, float celsius) {
	XPos = x;
	YPos = y;
	ZPos = z;
	Celsius = celsius;
};

float Temperature::getXPosition() {
	return XPos;
};

float Temperature::getYPosition() {
	return YPos;
};

float Temperature::getZPosition() {
	return ZPos;
};

float Temperature::getTemperature() {
	return Celsius;
};