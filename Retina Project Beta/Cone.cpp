#include "stdafx.h"
#include "Cone.h"


Cone::Cone(ReceptorType t, int x, int y) {
	receptorType = t; // stores RGB value which is unique to the cone
	Point position = Point(x, y);
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

 const float Cone::getX() {
	 return position.x;
 }

 const float Cone::getY() {
	 return position.y;
 }

void Cone::update(float elapsedSeconds) {
	Photoreceptor::update(elapsedSeconds);
}

const char Cone::getType() {
	// ALLOWS for visual display of whether it is a rod or a cone being generated
	return 'C';
}
