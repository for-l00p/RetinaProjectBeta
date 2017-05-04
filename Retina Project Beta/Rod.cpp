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

Rod::Rod(double x, double y) {
	receptorType = Photoreceptor::ROD;
	xc = x;
	yc = y;
}
const double Rod::getX() {
	return xc;
}

const double Rod::getY() {
	return yc;
}

 void Rod::update(float elapsedSeconds) {
	 Photoreceptor::update(elapsedSeconds);
}
