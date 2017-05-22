#pragma once
#include "stdafx.h"
#include "Photoreceptor.h"

const char Photoreceptor::getType() { return 'P'; } // returns the type 
const char Photoreceptor::getRGB() { return '0'; } // creates a virtual method which is overriden by rod's and cones
Photoreceptor::Photoreceptor() : Neuron(-40, -65, true) {}
double Photoreceptor::calculatePotential(int photonsHit, float elapsedSeconds) { return -40.0; }

bool Photoreceptor::isAbsored(Photon p, Photoreceptor::ReceptorType t) {
	if (rand() % 3 == 2) //TODO Implement probabilities (Stiles-Crawford, Spectral Sesnitivity, etc.)
		return false;
	if (t == ROD)        //NOT TRUE
		return true;
	if (t == RED && p.getWavelength() > 635 && p.getWavelength() < 700)
		return true;
	if (t == GREEN && p.getWavelength() > 520 && p.getWavelength() < 560)
		return true;
	if (t == BLUE && p.getWavelength() > 450 && p.getWavelength() < 490)
		return true;
	return false;
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