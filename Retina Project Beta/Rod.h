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
	Rod(int x, int y);
	virtual const float getX();
	virtual const float getY();
	virtual void update(float elapsedSeconds) override;
};

#endif