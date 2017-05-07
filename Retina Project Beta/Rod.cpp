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

Rod::Rod(Point loc) {
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

void Rod::update(float elapsedSeconds) {
	 Photoreceptor::update(elapsedSeconds);
}
