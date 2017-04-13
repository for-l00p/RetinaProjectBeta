#pragma once
#include "Photoreceptor.h"
#include "Photon.h"

#ifndef CONE
#define CONE

class Cone : public Photoreceptor {
public:
	static constexpr double PEAK_DENSITY() { return 199.2f; }
	static constexpr double PERIPHERY_DENSITY() { return 3.6f; }
	static constexpr double MEAN_DENSITY_CONSTANT() { return 15; } //Ignore these for now

	Cone(ReceptorType t);
	virtual const char getRGB() override;
	virtual void update(float elapsedSeconds) override;
	virtual const char getType() override;
};

#endif 