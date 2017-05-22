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
#include "Builder.h"

//#include "VoronoiTest.h"
//#include "Voronoi.h"

const double PI = 3.1415926535;
const double probabilityRED=0.64;
const double probabilityGREEN=0.32;
//probabilityBlue= 0.02;

Quadtree<Photoreceptor> photoreceptors = Quadtree<Photoreceptor>();
Quadtree<Bipolar> bipolars = Quadtree<Bipolar>();
Quadtree<Ganglion> ganglia = Quadtree<Ganglion>();

const int numCone = 10000;//number of cones to be generated
const int numRds = 10000;//number of rods to be generated

//eccentricities for data points for photoreceptors
std::array<double, 12> coneIntervals{ 0.12219, 7.9600897, 17.49904, 26.76169, 35.5145, 54.50688, 72.42695, 90.7516, 108.60589, 126.01612, 144.24867, 162.93843 };
std::array<double, 16> rodIntervals{ 9.147886, 17.805035, 26.424519, 35.26334, 44.18192, 52.72386, 62.198536, 70.36384, 79.412025, 88.8867, 98.371346, 107.429504, 116.45775, 125.505936, 134.09773, 143.59235 };
std::array<double, 31> ganglionIntervals{ 0, 0.0632689, 0.105448, 0.147627, 0.203866, 0.302285, 0.400703, 0.499121, 0.604569, 0.695958, 0.808436, 0.906854, 0.998243, 1.51142, 2.00351, 2.52373, 3.02285, 3.99297, 4.01773, 5.07092, 6.0461, 7.02128, 8.11348, 9.12766, 10.1418, 11.156, 12.1312, 13.1064, 14.1596, 15.1348, 16.1099 };

//densities in 1000s of photoreceptors/mm^2 for each interval
std::array<double, 12> coneDensity{ 201.819, 150.17027, 111.00869, 88.49225, 69.91545, 50.293564, 41.721466, 35.550728, 30.941757, 26.3093, 25.686943, 24.295444 };
std::array<double, 16> rodDensity{ 64.36445, 109.88923, 129.6439, 135.57826, 136.48705, 132.98442, 126.99707, 119.08304, 111.82526, 105.837906, 99.22235, 91.33638, 85.335, 78.07722, 71.43361, 64.189865 };
std::array<double, 31> ganglionDensity{ 0, 0.110385, 0.783357, 1.56869, 4.03902, 10.8902, 16.6178, 21.1094, 22.4547, 23.9128, 25.5951, 26.7159, 26.7133, 22.7663, 16.2357, 11.2772, 7.89242, 3.93258, 3.90423, 2.3493, 1.67324, 1.13239, 0.828169, 0.659155, 0.490141, 0.422535, 0.371831, 0.304225, 0.253521, 0.202817, 0.202817 };

std::piecewise_linear_distribution<double>
coneDistribution(coneIntervals.begin(), coneIntervals.end(), coneDensity.begin());

std::piecewise_linear_distribution<double>
rodDistribution(rodIntervals.begin(), rodIntervals.end(), rodDensity.begin());

std::piecewise_linear_distribution<double>
ganglionDistribution(ganglionIntervals.begin(), ganglionIntervals.end(), ganglionDensity.begin());

std::default_random_engine generator;

double getDistance(int type) {
	switch (type) {
	case 0:
		return rodDistribution(generator);
	case 1:
		return coneDistribution(generator);
	case 2:
		return ganglionDistribution(generator);
	}
}

Point halfSizeBipolarsCenter(Point p) {
	if (p.x*p.x + p.y*p.y < 5.0625)
		return Point(0.125, 0.125);
	return Point(0.5, 0.5);
}

Point halfSizeBipolarsSurround(Point p) {
	if (p.x*p.x + p.y*p.y < 5.0625)
		return Point(0.375, 0.375);
	return Point(1, 1);
}

Data<Photoreceptor> buildRod() {
	// Method creates rods and cones based on polar coordinates 

	double ecc = getDistance(0);
	double r = sin(ecc / 180 * PI)*RETINA_RADIUS;
	double theta = ((double)rand() / (RAND_MAX)) * 2.0 * PI;

	double x = r*cos(theta);
	double y = r*sin(theta);
	Data<Photoreceptor> d(Point(x, y), new Rod());
	return d;
}

Data<Photoreceptor> buildCone() {
	// Method creates rods and cones based on polar coordinates 

	double ecc = getDistance(1);
	double r = sin(ecc/180*PI)*RETINA_RADIUS;
	double theta = ((double)rand() / (RAND_MAX)) * 2.0 * PI;

	double x = r*cos(theta);
	double y = r*sin(theta);

	Cone* c;
	//std::cout << x << ", " << y << "\n";
	double coneType = ((double)rand() / (RAND_MAX));
	Point loc = Point(x, y);
	if (coneType < probabilityRED)
		c = new Cone(Cone::RED);
	else if (coneType < probabilityRED + probabilityGREEN)
		c = new Cone(Cone::GREEN);
	else 
		c = new Cone(Cone::BLUE);
	Data<Photoreceptor> d(loc,c);
	return d;
}

Data<Bipolar> buildBipolar(Quadtree<Photoreceptor> q) {
	// Method creates rods and cones based on polar coordinates 

	double ecc = getDistance(2);
	double r = sin(ecc / 180 * PI)*RETINA_RADIUS;
	double theta = ((double)rand() / (RAND_MAX)) * 2.0 * PI;

	double x = r*cos(theta);
	double y = r*sin(theta);
	Point p = Point(x, y);
	Data<Bipolar> d(p, new Bipolar());
	QuadDifference region(QuadRegion(p, halfSizeBipolarsCenter(p)),QuadRegion(p, halfSizeBipolarsSurround(p)));
	d.load->addInputCellCenter(*(std::vector<Neuron*> *)&q.queryRangeObjects(QuadRegion(p, halfSizeBipolarsCenter(p))));
	d.load->addInputCellSurround(*(std::vector<Neuron*> *)&q.queryRangeObjects(region));
	return d;
}

Data<Ganglion> buildGanglion(Quadtree<Bipolar> q) {
	// Method creates rods and cones based on polar coordinates 

	double ecc = getDistance(2);
	double r = sin(ecc / 180 * PI)*RETINA_RADIUS;
	double theta = ((double)rand() / (RAND_MAX)) * 2.0 * PI;

	double x = r*cos(theta);
	double y = r*sin(theta);
	Point p = Point(x, y);
	Data<Ganglion> d(p, new Ganglion());
	QuadDifference region(QuadRegion(p, halfSizeBipolarsCenter(p)), QuadRegion(p, halfSizeBipolarsSurround(p)));
	d.load->addInputCellCenter(*(std::vector<Neuron*> *)&q.queryRangeObjects(QuadRegion(p, halfSizeBipolarsCenter(p))));
	d.load->addInputCellSurround(*(std::vector<Neuron*> *)&q.queryRangeObjects(region));
	return d;
}
 
Photoreceptor* build(int x, int y) {
	float r = std::sqrtf((x - 5)*(x - 5) + (y - 5)*(y - 5));
	if (r <= 3) {
		if (rand() % 3 < 2) {
			//std::cout << "hi1";
			return new Cone(Cone::RED);
		}
		//std::cout << "hi2";
		return new Cone(Cone::GREEN);
	}
	if (r <= 3 * 2) {
		if (rand() % 2 < 1) {
			//std::cout << "hi3";
			return new Rod();
		}
		int i = rand() % 10;
		if (i < 1) {
			//std::cout << "hi4";
			return new Cone(Cone::BLUE);
		}
		if (i < 4) {
			return new Cone(Cone::GREEN);
		}
		//std::cout << "hi6";
		return new Cone(Cone::RED);
	}
	//std::cout << "hi";
	if (rand() % 4 < 3)
		return new Rod();
	int i = rand() % 10;
	if (i < 1)
		return new Cone(Cone::BLUE);
	if (i < 4)
		return new Cone(Cone::GREEN);
	return new Cone(Cone::RED);
}

Quadtree<Photoreceptor> photoreceptorBuilder(int numRods, int numCones)
{
	srand((unsigned int)time(NULL));
	photoreceptors = Quadtree<Photoreceptor>(QuadRegion(Point(0,0), Point(RETINA_RADIUS,RETINA_RADIUS)));

	for (int i = 0; i < numRods; i++) {
		photoreceptors.insert(buildRod());
		if (i % (numRods / 100) == 0)
			std::cout << "Rod Loading " << i * 100 / numRods << "% Complete\n";
	}

	for (int i = 0; i < numCones; i++) {
		photoreceptors.insert(buildCone());
		if (i % (numCones / 100) == 0)
			std::cout << "Cone Loading " << i * 100 / numCones << "% Complete\n";
	} 

	//retina.getTree();
	return photoreceptors;
}

Quadtree<Bipolar> bipolarBuilder(Quadtree<Photoreceptor> q, int numBipolars)
{
	srand((unsigned int)time(NULL));
	bipolars = Quadtree<Bipolar>(QuadRegion(Point(0, 0), Point(RETINA_RADIUS, RETINA_RADIUS)));
	for (int i = 0; i < numBipolars; i++) {
		bipolars.insert(buildBipolar(q));
		if (i % (numBipolars / 100) == 0)
			std::cout << "Bipolar Loading " << i * 100 / numBipolars << "% Complete\n";
	}

	//retina.getTree();
	return bipolars;
}

Quadtree<Ganglion> ganglionBuilder(Quadtree<Bipolar> q, int numGanglia) {
	ganglia = Quadtree<Ganglion>(QuadRegion(Point(0, 0), Point(RETINA_RADIUS, RETINA_RADIUS)));
	for (int i = 0; i < numGanglia; i++) {
		ganglia.insert(buildGanglion(q));
		if (i % (numGanglia / 100) == 0)
			std::cout << "Ganglion Loading " << i * 100 / numGanglia << "% Complete\n";
	}
}