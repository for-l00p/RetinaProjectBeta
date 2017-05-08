#pragma once
#include "stdafx.h"
#include "Cone.h"


Cone::Cone(ReceptorType t) {
	receptorType = t; // stores RGB value which is unique to the cone
	location = Point(0,0);
}

Cone::Cone(ReceptorType t, Point loc){
	receptorType = t; // stores RGB value which is unique to the cone
	location = loc;
}

Point Cone::getPoint()
{
	return location;
}

void Cone::setPoint(Point newLoc)
{
	location = newLoc;
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
