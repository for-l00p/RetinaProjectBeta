#include "stdafx.h"
#include "Cone.h"
#include "Photon.h"

Cone::Cone(ReceptorType t) {
	receptorType = t; // stores RGB value which is unique to the cone
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

void Cone::update(float elapsedSeconds) {
	Photoreceptor::update(elapsedSeconds);
}

const char Cone::getType() {
	// ALLOWS for visual display of whether it is a rod or a cone being generated
	return 'C';
}
