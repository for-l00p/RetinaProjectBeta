#include "stdafx.h"
#include "Photoreceptor.h"

const char Photoreceptor::getType() { return 'P'; } // returns the type 
const char Photoreceptor::getRGB() { return '0'; } // creates a virtual method which is overriden by rod's and cones
Photoreceptor::Photoreceptor() : Neuron(-40, -65, true) {}

double Photoreceptor::calculatePotential(int photonsHit, float elapsedSeconds) { return -40.0; }

bool Photoreceptor::isAbsored(Photon p, Photoreceptor::ReceptorType t) {
	return rand()%3<2; //TODO Implement probabilities (Stiles-Crawford, Spectral Sesnitivity, etc.)
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

int Photoreceptor::update(float elapsedSeconds) {
	int photonsAbsorbed = 0;
	for (int i = 0; i < photonQueue.size(); i++) {
		if (Photoreceptor::isAbsored(photonQueue[i], receptorType)) {
			photonsAbsorbed++;
		}
	}
	photonQueue.clear();
	return photonsAbsorbed;
}