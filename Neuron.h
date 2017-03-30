#pragma once
#include "stdafx.h"
#include <vector>
#ifndef NEURON
#define NEURON

class Neuron {
protected:
	double cellPotential;
	double cellMin;
	double cellMax;
	bool isGraded;
	std::vector<Neuron*> inputCenterConnectedCells;
	std::vector<Neuron*> inputSurroundConnectedCells;
	std::vector<Neuron*> outputConnectedCells;

public:
	virtual const char getType(); // Allows for quick type checking of an object
	Neuron();
	Neuron(double potentialMin, double potentialMax);
	Neuron(double potentialMin, double potentialMax, bool graded);
	void addInputCellCenter(Neuron* n);
	void addInputCellSurround(Neuron* n);
	void resetConnections();
	std::vector<std::vector<double>> acquireInputs();
	void update(float elapsedSeconds);
	double getPotential();
};

#endif // NEURON
