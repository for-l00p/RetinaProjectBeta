#pragma once
#include "stdafx.h"
#include "Neuron.h"
#ifndef PHOTORECEPTOR
#define PHOTORECEPTOR

class Photoreceptor : public Neuron {
protected:
	//double eccentricity;
	//double locationAngle; //Relative to straight up
	int photonsHit;
	int photonFrequency;

public:
	virtual const char getType() override; // returns the type 
	virtual const char getRGB(); // creates a virtual method which is overriden by rod's and cones
	Photoreceptor();
	void setInputs(int photons, int frequency, int lightAngle);
	virtual void update(float elapsedSeconds);
};

#endif