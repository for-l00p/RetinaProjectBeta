#include "stdafx.h"
#include "Neuron.h"
#include <vector>

const char Neuron::getType() { return 'N'; } // Allows for quick type checking of an object
Neuron::Neuron() {
	cellMin = -40;
	cellMax = -65;
	cellPotential = cellMin;
	isGraded = false;

}

Neuron::Neuron(double potentialMin, double potentialMax) {
	cellMin = potentialMin;
	cellMax = potentialMax;
	cellPotential = cellMin;
	isGraded = false;
}

Neuron::Neuron(double potentialMin, double potentialMax, bool graded) {
	cellMin = potentialMin;
	cellMax = potentialMax;
	cellPotential = cellMin;
	isGraded = graded;
}

void Neuron::addInputCellCenter(Neuron* n) {
	inputCenterConnectedCells.resize(inputCenterConnectedCells.size() + 1);
	inputCenterConnectedCells[inputCenterConnectedCells.size() - 1] = n;
}

Point Neuron::getPoint()
{
	return location;
}

void Neuron::addInputCellSurround(Neuron* n) {
	inputSurroundConnectedCells.resize(inputSurroundConnectedCells.size() + 1);
	inputSurroundConnectedCells[inputSurroundConnectedCells.size() - 1] = n;
}

void Neuron::resetConnections() {
	inputCenterConnectedCells = std::vector<Neuron*>{};
	inputSurroundConnectedCells = std::vector<Neuron*>{};
}

std::vector<std::vector<double>> Neuron::acquireInputs() {
	std::vector<double> centerPotentials = std::vector<double>{};
	for (int i = 0; i < inputCenterConnectedCells.size(); ++i) {
		centerPotentials.resize(i + 1);
		centerPotentials[i] = inputCenterConnectedCells[i]->getPotential();
	}
	std::vector<double> surroundPotentials = std::vector<double>{};
	for (int i = 0; i < inputSurroundConnectedCells.size(); ++i) {
		centerPotentials.resize(i + 1);
		centerPotentials[i] = inputSurroundConnectedCells[i]->getPotential();
	}

	return std::vector<std::vector<double>> {centerPotentials, surroundPotentials};
}

void Neuron::update(float elapsedSeconds)
{
	double averageInput = 0;
	std::vector<std::vector<double>> inputs = acquireInputs();
	for (int i = 0; i < inputs.size(); i++) {
		for (int j = 0; j < inputs[i].size(); j++) {
			averageInput += inputs[i][j];
		}
	}
	averageInput /= inputs[0].size() + inputs[1].size();

	cellPotential = averageInput;
}

double Neuron::getPotential() {
	return cellPotential;
}
