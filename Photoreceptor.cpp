#include "stdafx.h"
#include "Photoreceptor.h"

const char Photoreceptor::getType() { return 'P'; } // returns the type 
const char Photoreceptor::getRGB() { return '0'; } // creates a virtual method which is overriden by rod's and cones
Photoreceptor::Photoreceptor() : Neuron(-40, -65, true) {}

void Photoreceptor::setInputs(int photons, int frequency, int lightAngle) {
	photonsHit = photons;
	photonFrequency = frequency;
	//TODO: light angle/Stiles-Crawford Effect
}

void Photoreceptor::update(float elapsedSeconds) {
	//double num = 1.0f / photonsHit;
	//num = 1.0f - num;
	//cellPotential = num*(cellMax - cellMin) + cellMin;
}