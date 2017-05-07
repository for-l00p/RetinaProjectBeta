// Demo.cpp : Defines the entry point for the console application.
//
#pragma once
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
#include "Cone.h"
#include "Rod.h"
#include "Bipolar.h"
#include "Ganglion.h"
#include "Quadtree.h"
#include <fstream>
#include <sstream>

const double PI = 3.1415926535;
const double probabilityRED = 0.64;
const double probabilityGREEN = 0.32;
//probabilityBlue= 0.02;

Quadtree<Photoreceptor> retina = Quadtree<Photoreceptor>();

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

std::default_random_engine generator;

std::vector<double> readInFromFile(std::string fileName) {
	std::vector<double> data;
	std::ifstream file(fileName);
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		double a;
		if ((!(iss >> a))) {
			break;
		}
		data.push_back(a);
	}
	for (auto i = data.begin(); i != data.end(); ++i)
		std::cout << *i << ' ';
	return data;
}

double getDistance(bool isCone) {
	if (isCone)
		return coneDistribution(generator);
	else
		return rodDistribution(generator);
}

Cone* buildCone() {
	// Method creates rods and cones based on polar coordinates 

	double r = getDistance(true);
	double theta = ((double)rand() / (RAND_MAX)) * 2.0 * PI;

	double x = r*cos(theta);
	double y = r*sin(theta);

	Cone* c;
	double coneType = ((double)rand() / (RAND_MAX));
	Point loc = Point(x, y);
	if (coneType < probabilityRED)
		c = new Cone(Cone::RED, loc);
	else if (coneType < probabilityRED + probabilityGREEN)
		c = new Cone(Cone::GREEN, loc);
	else
		c = new Cone(Cone::BLUE, loc);
	return c;
}


Rod* buildRod() {
	// Method creates rods and cones based on polar coordinates 

	double r = getDistance(false);
	double theta = ((double)rand() / (RAND_MAX)) * 2.0 * PI;

	double x = r*cos(theta);
	double y = r*sin(theta);


	Rod* c = new Rod(Point(x, y));
	return c;
}

int main()
{
	//just call this multiple times and replacing "rod.txt" with the string of the text file name
	const std::vector<double> data = readInFromFile("rod.txt");
	//data.data();
	double arr[30];
	std::copy(data.begin(), data.end(), arr);
	// NOTE THAT array size must be pre-defined


	srand((unsigned int)time(NULL));

	std::vector<Photoreceptor*> map;
	for (int i = 0; i < 100; i++) {
		Rod* temp = buildRod();
		map.push_back(temp);
		Data<Photoreceptor> cur((Photoreceptor)*temp);
		retina.insert(cur);
	}

	std::vector<std::vector<Photoreceptor*>> x = {};

	for (int i = 0; i < 10000; i++) {
		buildCone();
		Cone* tempC = buildCone();
		map.push_back(tempC);
		Data<Photoreceptor> curC((Photoreceptor)*tempC);
		retina.insert(curC);
	}

	//retina.getTree();

	int j;
	std::cin >> j;
	return 0;
}