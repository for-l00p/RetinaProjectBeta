#include "stdafx.h"
#include "Bipolar.h"
#include "Neuron.h"

Bipolar::Bipolar() : Neuron(-40, -65, true) {}

int Bipolar::update(float elapsedSeconds)
{
	double averageInputSurround = 0;
	double averageInputCenter = 0;
	std::vector<std::vector<double>> inputs = acquireInputs();
	
	for (int i = 0; i < inputs[0].size(); i++) {
		averageInputCenter += inputs[0][i];
	}
	
	for (int i = 0; i < inputs[1].size(); i++) {
		averageInputSurround += inputs[1][i];
	}

	averageInputCenter /= inputs[0].size();
	averageInputSurround /= inputs[1].size();

	cellPotential = averageInputCenter - averageInputSurround + cellMin;

	return cellPotential;
}