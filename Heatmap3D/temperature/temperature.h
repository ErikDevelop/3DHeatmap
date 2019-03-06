#pragma once

class Temperature
{
public:
	Temperature(float x, float y, float z, float celsius);
	float getXPosition();
	float getYPosition();
	float getZPosition();
	float getTemperature();
private:
	float XPos;
	float YPos;
	float ZPos;
	float Celsius;
};