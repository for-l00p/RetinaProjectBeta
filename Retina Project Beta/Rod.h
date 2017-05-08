#pragma once
#include "stdafx.h"
#include "Photoreceptor.h"
#ifndef RODCELL
#define RODCELL

class Rod : public Photoreceptor {
protected:
	virtual double calculatePotential(int photons, float elapsedSeconds) override;
public:
	Rod();
	virtual const char getType() override;
	virtual const char getRGB() override;
	Rod(Point loc);
	virtual Point getPoint();
	virtual void setPoint(Point newLoc);
	virtual int update(float elapsedSeconds) override;
};

#endif