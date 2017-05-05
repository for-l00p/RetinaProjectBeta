#pragma once
#include "stdafx.h"
#include "Photoreceptor.h"


const char Photoreceptor::getType() { return 'P'; } // returns the type 
const char Photoreceptor::getRGB() { return '0'; } // creates a virtual method which is overriden by rod's and cones
Photoreceptor::Photoreceptor(Point loc) : Neuron(-40, -65, true), location(loc) {}
Photoreceptor::Photoreceptor() : Neuron(-40, -65, true) {}

Point Photoreceptor::getPoint() {
	return location;
}

void Photoreceptor::setPoint(Point newLoc)
{
	location = newLoc;
}

bool Photoreceptor::isAbsored(Photon p, Photoreceptor::ReceptorType t) {
	return true; //TODO Implement probabilities (Stiles-Crawford, Spectral Sesnitivity, etc.)
}

void Photoreceptor::addPhotons(std::vector<Photon> newPhotons) {
	if (photonQueue.size() == 0)
		photonQueue = newPhotons;
	else {
		photonQueue.resize(photonQueue.size() + newPhotons.size());
		for (int i = 0; i < newPhotons.size(); i++) {
			photonQueue[photonQueue.size() + i] = newPhotons[i];
		}
	}
}

void Photoreceptor::update(float elapsedSeconds) {
	int photonsAbsorbed = 0;
	for (int i = 0; i < photonQueue.size(); i++) {
		if (Photoreceptor::isAbsored(photonQueue[i], receptorType)) {
			photonsAbsorbed++;
		}
	}
}