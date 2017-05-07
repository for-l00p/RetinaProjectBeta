#pragma once
#include "stdafx.h"
#include "Neuron.h"
#include "Photon.h"
#include <vector>

#ifndef PHOTORECEPTOR
#define PHOTORECEPTOR

class Photoreceptor : public Neuron {
public:
	enum ReceptorType {
		RED,
		GREEN,
		BLUE,
		ROD,
	};
protected:
	//double eccentricity;
	//double locationAngle; //Relative to straight up
	double x, y;
	std::vector<Photon> photonQueue;
	ReceptorType receptorType;

	virtual double calculatePotential(int photons, float elapsedSeconds);

public:
	virtual const char getType() override; // returns the type 
	virtual const char getRGB(); // creates a virtual method which is overriden by rods and cones
	double getX();
	double getY();
	static bool isAbsored(Photon p, ReceptorType t);
	Photoreceptor();
	void addPhotons(std::vector<Photon> newPhotons);
	virtual int update(float elapsedSeconds);
};

#endif