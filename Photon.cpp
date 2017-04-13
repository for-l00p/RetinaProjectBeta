#include "stdafx.h"
#include "Photon.h"

Photon::Photon(int f, float a) {
	frequency = f;
	angle = a;
}

int Photon::getFrequency() {
	return frequency;
}

float Photon::getAngle() {
	return angle;
}