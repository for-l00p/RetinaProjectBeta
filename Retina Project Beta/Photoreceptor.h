#pragma once
#include "stdafx.h"
#include "Neuron.h"
#include "Photon.h"
#include <vector>
#include "Quadtree.h"

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
	std::vector<Photon> photonQueue;
	ReceptorType receptorType;
	Point position = Point();

public:
	virtual const char getType() override; // returns the type 
	virtual const char getRGB(); // creates a virtual method which is overriden by rods and cones
	static bool isAbsored(Photon p, ReceptorType t);
	Photoreceptor();
	void addPhotons(std::vector<Photon> newPhotons);
	virtual void update(float elapsedSeconds);
};

#endif