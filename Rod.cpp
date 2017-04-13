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

 void Rod::update(float elapsedSeconds) {
	 Photoreceptor::update(elapsedSeconds);
}
