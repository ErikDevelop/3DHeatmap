#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <errno.h>
#include <nlohmann/json.hpp>

#include "temperature.h"

using json = nlohmann::json;

class DataController
{
public:
	static int loadData(std::string fileName);
	static std::vector<Temperature>* getEnvironmentalTemperatures();
	static std::vector<Temperature>* getComponentTemperatures();
private:
	static json content;
	static std::vector<Temperature> environmentalTemperatures;
	static std::vector<Temperature> componentTemperatures;
	static float tempX;
	static float tempY;
	static float tempZ;
	static float tempCelsius;
	static Temperature tempTemperature;

	static int loadFileContents(std::string* fileName);
	static int deserialiseContents();
	static int insertTemperature(std::vector<Temperature>* targetVector, Temperature* temperature);
};