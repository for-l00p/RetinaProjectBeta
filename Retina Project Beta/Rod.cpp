#pragma once
#include "stdafx.h"
#include "Rod.h"

const char Rod::getType() {
	// ALLOWS for visual display of whether it is a rod or a cone being generated
	return 'R';
}

const char Rod::getRGB() {
	return ' ';
}

double Rod::calculatePotential(int photonsHit, float elapsedSeconds) {
	double num = 1.0 / ((photonsHit / 25.0) + 1.0); //Arbitrary Numbers; needs real data
	num = 1.0 - num;
	return num*(cellMax - cellMin) + cellMin;
}

Rod::Rod() {
	receptorType = Photoreceptor::ROD;
}

Rod::Rod(Point loc){
	receptorType = Photoreceptor::ROD;
	location = loc;
}

Point Rod::getPoint()
{
	return location;
}

void Rod::setPoint(Point newLoc)
{
	location = newLoc;
}

int Rod::update(float elapsedSeconds) {
	int photons = Photoreceptor::update(elapsedSeconds);
	cellPotential = calculatePotential(photons, elapsedSeconds);
	return cellPotential;
}

