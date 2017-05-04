#pragma once
#include "stdafx.h"
#include "Photoreceptor.h"
#ifndef RODCELL
#define RODCELL

class Rod : public Photoreceptor {
public:
	//Rod();
	virtual const char getType() override;
	virtual const char getRGB() override;
	Rod(double x, double y);
	virtual const double getX();
	virtual const double getY();
	virtual void update(float elapsedSeconds) override;
};

#endif