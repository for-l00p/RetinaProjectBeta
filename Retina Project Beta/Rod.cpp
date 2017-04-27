#include "stdafx.h"
#include "Rod.h"

const char Rod::getType() {
	// ALLOWS for visual display of whether it is a rod or a cone being generated
	return 'R';
}

const char Rod::getRGB() {
	return ' ';
}

Rod::Rod() {
	receptorType = Photoreceptor::ROD;
}

Rod::Rod(int x, int y) {
	receptorType = Photoreceptor::ROD;
	Point position = Point(x, y);
}
const float Rod::getX() {
	return position.x;
}

const float Rod::getY() {
	return position.y;
}

 void Rod::update(float elapsedSeconds) {
	 Photoreceptor::update(elapsedSeconds);
}
