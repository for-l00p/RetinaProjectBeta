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
#include "Quadtree.cpp"
#include "Quadtree.h"

const double PI = 3.1415926535;
const double probabilityRED=0.64;
const double probabilityGREEN=0.32;
//probabilityBlue= 0.02;

Quadtree<Photoreceptor> retina;

Cone* buildCone() {
	// Method creates rods and cones based on polar coordinates 
	//TO DO: Implement density based on data in cone & rod topography (.txt) files
	
	srand((unsigned int)time(NULL));

	double r = ((double)rand() / (RAND_MAX)) * 180;
	double theta = ((double)rand() / (RAND_MAX)) * 2 * PI;

	double x = r*cos(theta);
	double y = r*sin(theta);

	Cone* c;
	
	double coneType = ((double)rand() / (RAND_MAX));
	if (coneType < probabilityRED)
		c = new Cone(Cone::RED, x, y);
	else if (coneType < probabilityRED + probabilityGREEN)
		c = new Cone(Cone::GREEN,x,y);
	else 
		c = new Cone(Cone::BLUE,x,y);
	return c;
}

Rod* buildRod() {
	// Method creates rods and cones based on polar coordinates 
	//TO DO: Implement density based on data in cone & rod topography (.txt) files
	
	srand((unsigned int)time(NULL));

	double r = ((double)rand() / (RAND_MAX)) * 180;
	double theta = ((double)rand() / (RAND_MAX)) * 2 * PI;

	double x = r*cos(theta);
	double y = r*sin(theta);

	Rod* c = new Rod(x,y);
	return c;
}

int main()
{
	
}
/*
int previousImplementation() {
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
	return 0;
} */
