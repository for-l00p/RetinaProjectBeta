#pragma once
#include "stdafx.h"
#include "Photoreceptor.h"
#ifndef ROD
#define ROD

class Rod : public Photoreceptor {
public:
	virtual const char getType() override;
	virtual const char getRGB() override;
	//void setInputs(int lightIntensity, int lightFrequency, int lightAngle);
	virtual void update(float elapsedSeconds) override;
};

#endif