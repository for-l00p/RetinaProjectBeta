#pragma once
#ifndef PHOTON
#define PHOTON

class Photon {
private:
	int frequency;
	float angle;

public:
	Photon(int f, float a);
	int getFrequency();
	float getAngle();

};

#endif PHOTON