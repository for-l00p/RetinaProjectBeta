// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <array>
#include <random>
#include <vector>
#include <cmath>
#include <ctime>
#include <iterator>
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

const int numCone = 10000;//number of cones to be generated
const int numRds = 10000;//number of rods to be generated

//eccentricities for data points for photoreceptors
std::array<double, 12> coneIntervals{ 0.12219, 7.9600897, 17.49904, 26.76169, 35.5145, 54.50688, 72.42695, 90.7516, 108.60589, 126.01612, 144.24867, 162.93843 };
std::array<double, 16> rodIntervals{ 9.147886, 17.805035, 26.424519, 35.26334, 44.18192, 52.72386, 62.198536, 70.36384, 79.412025, 88.8867, 98.371346, 107.429504, 116.45775, 125.505936, 134.09773, 143.59235 };

//densities in 1000s of photoreceptors/mm^2 for each interval
std::array<double, 12> coneDensity{ 201.819, 150.17027, 111.00869, 88.49225, 69.91545, 50.293564, 41.721466, 35.550728, 30.941757, 26.3093, 25.686943, 24.295444 };
std::array<double, 16> rodDensity{ 64.36445, 109.88923, 129.6439, 135.57826, 136.48705, 132.98442, 126.99707, 119.08304, 111.82526, 105.837906, 99.22235, 91.33638, 85.335, 78.07722, 71.43361, 64.189865 };

std::piecewise_linear_distribution<double>
coneDistribution(coneIntervals.begin(), coneIntervals.end(), coneDensity.begin());

std::piecewise_linear_distribution<double>
rodDistribution(rodIntervals.begin(), rodIntervals.end(), rodDensity.begin());

Cone* buildCone() {
	// Method creates rods and cones based on polar coordinates 
	//TO DO: Implement density based on data in cone & rod topography (.txt) files
	
	srand((unsigned int)time(NULL));

	double r = getDistance(true);
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

double getDistance(bool isCone) {



	return ((double)rand() / (RAND_MAX)) * 180;
}

Rod* buildRod() {
	// Method creates rods and cones based on polar coordinates 
	//TO DO: Implement density based on data in cone & rod topography (.txt) files
	
	srand((unsigned int)time(NULL));

	double r = getDistance(false);
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
