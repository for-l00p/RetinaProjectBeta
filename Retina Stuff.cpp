// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include "Neuron.h"
#include "Photoreceptor.h"
#include "Cone.h"
#include "Rod.h"
#include "Bipolar.h"
#include "Ganglion.h"

Photoreceptor* builder(int num) {
	// Method creates seqeuncial Rods and Cones depending position in the matrix
	if (num % 2 == 0) {
		Photoreceptor* p = new Rod(); // creates a new rod which is then returned
		return p;
	}
	else {
		static int count = 1; // allows for quick alteration of RGB cones being created 
		if (count % 3 == 1) {
			Photoreceptor* p = new Cone(Cone::RED);
			count++;
			return p;
		}
		else if (count % 3 == 2) {
			Photoreceptor* p = new Cone(Cone::BLUE);
			count++;
			return p;
		}
		else {
			Photoreceptor* p = new Cone(Cone::GREEN);
			count++;
			return p;
		}
	}
}


int main()
{
	srand(std::time(0));
	rand();

	const int rows = 12;
	const int cols = 12;
	const int bipolarRange = 3; // I've arbitrarily made the receptive fields a 3x3 square for the purposes of this test


	//std::vector<Photoreceptor> receptors; // will be implemented in the future
	//std::vector<Bipolar> bipolars; 
	//std::vector<Ganglion> ganglia;


	Photoreceptor* x[rows][cols] = {};// call a method which returns a list filled in with all the inputs;
	Bipolar* y[rows / bipolarRange][cols / bipolarRange] = {}; 

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			x[i][j] = builder(i + j);
		}
	}

	std::cout << "Display of Rod and Cone Generator : \n\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << x[i][j]->getType();
		}
		std::cout << '\n';
	}

	std::cout << "\n\nDisplay the type of Cone that is created : \n\n";

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << x[i][j]->getRGB();
		}
		std::cout << '\n';
	}

	//Low Light
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			//x[i][j]->addPhotons();
			x[i][j]->update(0);
		}
	}

	for (int i = 0; i < rows / bipolarRange; i++) {
		for (int j = 0; j < cols / bipolarRange; j++) {
			y[i][j] = new Bipolar();
			for (int k = -(bipolarRange / 2); k < (bipolarRange / 2) + 1; k++) {
				for (int m = -(bipolarRange / 2); m < (int)(bipolarRange / 2) + 1; m++) {
					if (m != 0 || k != 0)
						y[i][j]->addInputCellSurround(x[i*bipolarRange + (bipolarRange / 2) - k][j*bipolarRange + (bipolarRange / 2) - m]);
					else
						y[i][j]->addInputCellCenter(x[i*bipolarRange + (bipolarRange / 2) - k][j*bipolarRange + (bipolarRange / 2) - m]);
				}
			}
		}
	}

	std::cout << "\n\nLow Light:\n\n";
	std::cout << "\nRod Potentials: \n\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = i%2; j < cols; j+=2) {
			std::cout << "[" << x[i][j]->getPotential() << "] ";
		}
		std::cout << '\n';
	}

	std::cout << "\nCone Potentials: \n\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = (i+1)%2; j < cols; j+=2) {
			std::cout << "[" << x[i][j]->getPotential() << "] ";
		}
		std::cout << '\n';
	}
	
	std::cout << "\nBipolar Potentials: \n\n";
	for (int i = 0; i < rows / bipolarRange; i++) {
		for (int j = 0; j < cols / bipolarRange; j++) {
			y[i][j]->update(0);
			std::cout << "[" << y[i][j]->getPotential() << "] ";
		}
		std::cout << '\n';
	}

	std::cout << "\n\nHeavy Light:\n\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			//x[i][j]->addPhotons();
			x[i][j]->update(0);
		}
	}

	std::cout << "\nRod Potentials: \n\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = i % 2; j < cols; j += 2) {
			std::cout << "[" << x[i][j]->getPotential() << "] ";
		}
		std::cout << '\n';
	}

	std::cout << "\nCone Potentials: \n\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = (i + 1) % 2; j < cols; j += 2) {
			std::cout << "[" << x[i][j]->getPotential() << "] ";
		}
		std::cout << '\n';
	}

	std::cout << "\nBipolar Potentials: \n\n";
	for (int i = 0; i < rows / bipolarRange; i++) {
		for (int j = 0; j < cols / bipolarRange; j++) {
			y[i][j]->update(0);
			std::cout << "[" << y[i][j]->getPotential() << "] ";
		}
		std::cout << '\n';
	}

	int xy;
	std::cin >> xy;

	return 0;
}
