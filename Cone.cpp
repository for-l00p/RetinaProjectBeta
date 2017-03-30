#include "stdafx.h"
#include "Cone.h"

Cone::Cone(ConeType t) {
	coneType = t; // stores RGB value which is unique to the cone

}
 const char Cone::getRGB() {
	if (coneType == RED) {
		return 'R';
	}
	else if (coneType == BLUE) {
		return 'B';
	}
	return 'G';
}
//void Cone::setInputs(int lightIntensity, int lightFrequency, int lightAngle) {
//TODO: Actually do something with this
//}

void Cone::update(float elapsedSeconds) {
	double num = 1.0 / ((photonsHit / 200.0) + 1.0); //Arbitrary Numbers; needs real data
	num = 1.0 - num;
	cellPotential = num*(cellMax - cellMin) + cellMin;
}

const char Cone::getType() {
	// ALLOWS for visual display of whether it is a rod or a cone being generated
	return 'C';
}
