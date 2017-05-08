#pragma once

#ifndef GANGLION
#define GANGLION

#include "Neuron.h"
#include "Point.h"


class Ganglion : public Neuron {
private:
	Point location;
public:
	Ganglion(Point loc);
};

#endif