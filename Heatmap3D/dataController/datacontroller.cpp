#include "datacontroller.h"

json DataController::content;
std::vector<Temperature> DataController::environmentalTemperatures;
std::vector<Temperature> DataController::componentTemperatures;
float DataController::tempX;
float DataController::tempY;
float DataController::tempZ;
float DataController::tempCelsius;
Temperature DataController::tempTemperature = Temperature(0, 0, 0, 0);

int DataController::loadData(const std::string fileName) {
	if (!loadFileContents(&fileName)) {
		std::cout << "ERROR!: opening stream failed: " << std::endl;
		std::cout << strerror(errno) << std::endl;

		return -1;
	}

	deserialiseContents();

	return 0;
};

int DataController::loadFileContents(const std::string* fileName) {
	std::ifstream ifs(*fileName);

	if (ifs.fail()) return -1;

	ifs >> content;

	return 0;
};

int DataController::deserialiseContents() {
	for (json::iterator it = content["data"].begin(); it != content["data"].end(); ++it) {
		tempX = ::atof((it.value()["position"]["x"].get<std::string>()).c_str());
		tempY = ::atof((it.value()["position"]["y"].get<std::string>()).c_str());
		tempZ = ::atof((it.value()["position"]["z"].get<std::string>()).c_str());
		tempCelsius = ::atof((it.value()["celsius"].get<std::string>()).c_str());

		tempTemperature = Temperature(tempX, tempY, tempZ, tempCelsius);

		if (it.value()["type"] == "Component") insertTemperature(&componentTemperatures, &tempTemperature);
		else insertTemperature(&environmentalTemperatures, &tempTemperature);
	}

	return 0;
};

int DataController::insertTemperature(std::vector<Temperature>* targetVector, Temperature* temperature) {
	(*targetVector).resize((*targetVector).size() + 1, *temperature);
	return 0;
};

std::vector<Temperature>* DataController::getEnvironmentalTemperatures() {
	return &environmentalTemperatures;
};

std::vector<Temperature>* DataController::getComponentTemperatures() {
	return &componentTemperatures;
};