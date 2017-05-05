#pragma once
#include "stdafx.h"
#include "Cone.h"


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

void Cone::update(float elapsedSeconds) {
	Photoreceptor::update(elapsedSeconds);
}

const char Cone::getType() {
	// ALLOWS for visual display of whether it is a rod or a cone being generated
	return 'C';
}
