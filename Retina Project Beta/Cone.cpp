#pragma once
#include "stdafx.h"
#include "Cone.h"


Cone::Cone(ReceptorType t, double x, double y) {
	receptorType = t; // stores RGB value which is unique to the cone
	xc = x;
	yc = y;
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

 const double Cone::getX() {
	 return xc;
 }

 const double Cone::getY() {
	 return yc;
 }

void Cone::update(float elapsedSeconds) {
	Photoreceptor::update(elapsedSeconds);
}

const char Cone::getType() {
	// ALLOWS for visual display of whether it is a rod or a cone being generated
	return 'C';
}
