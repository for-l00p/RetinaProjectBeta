#pragma once
#ifndef PHOTON
#define PHOTON

class Photon {
private:
	int wavelength;
	float angle;

public:
	Photon();
	Photon(int f, float a);
	int getWavelength();
	float getAngle();

};

#endif 