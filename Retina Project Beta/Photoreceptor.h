#pragma once
#include "stdafx.h"
#include "Neuron.h"
#include "Photon.h"
#include <vector>
#include "Point.h"

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
	Point location;
	//double eccentricity;
	//double locationAngle; //Relative to straight up
	std::vector<Photon> photonQueue;
	ReceptorType receptorType;

	virtual double calculatePotential(int photons, float elapsedSeconds);

public:
	virtual const char getType() override; // returns the type 
	virtual const char getRGB(); // creates a virtual method which is overriden by rods and cones
	virtual Point getPoint();
	virtual void setPoint(Point newLoc);
	static bool isAbsored(Photon p, ReceptorType t);
	Photoreceptor();
	Photoreceptor(Point loc);
	void addPhotons(std::vector<Photon> newPhotons);
	virtual int update(float elapsedSeconds);
};

#endif