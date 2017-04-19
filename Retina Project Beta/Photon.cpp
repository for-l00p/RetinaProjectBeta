#include "stdafx.h"
#include "Photon.h"

Photon::Photon() {
	wavelength = 720;
	angle = 0;
}

Photon::Photon(int f, float a) {
	wavelength = f;
	angle = a;
}

int Photon::getWavelength() {
	return wavelength;
}

float Photon::getAngle() {
	return angle;
}