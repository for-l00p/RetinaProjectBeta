#include "stdafx.h"
#include "Rod.h"

const char Rod::getType() {
	// ALLOWS for visual display of whether it is a rod or a cone being generated
	return 'R';
}

const char Rod::getRGB() {
	return ' ';
}

//void Rod::setInputs(int lightIntensity, int lightFrequency, int lightAngle) {
//TODO: Actually do something with this
//}

 void Rod::update(float elapsedSeconds) {
	double num = 1.0 / ((photonsHit / 25.0) + 1.0); //Arbitrary Numbers; needs real data
	num = 1.0 - num;
	cellPotential = num*(cellMax - cellMin) + cellMin;
}
