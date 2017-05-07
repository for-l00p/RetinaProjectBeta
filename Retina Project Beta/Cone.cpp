#include "stdafx.h"
#include "Cone.h"
#include "Photon.h"

Cone::Cone(ReceptorType t) {
	receptorType = t; // stores RGB value which is unique to the cone
}

Cone::Cone(ReceptorType t, double xPos, double yPos) {
	receptorType = t; // stores RGB value which is unique to the cone
	x = xPos;
	y = yPos;
}

 const char Cone::getRGB() {
	if (receptorType == RED) {
		return 'R';
	}
	else if (receptorType == BLUE) {
		return 'B';
	}
	return 'G';
}

double Cone::calculatePotential(int photonsHit, float elapsedSeconds) {
	double num = 1.0 / ((photonsHit / 200.0) + 1.0); //Arbitrary Numbers; needs real data
	num = 1.0 - num;
	return num*(cellMax - cellMin) + cellMin;
}

int Cone::update(float elapsedSeconds) {
	int photons = Photoreceptor::update(elapsedSeconds);
	
	cellPotential = calculatePotential(photons, elapsedSeconds);
	return cellPotential;
}

const char Cone::getType() {
	// ALLOWS for visual display of whether it is a rod or a cone being generated
	return 'C';
}
