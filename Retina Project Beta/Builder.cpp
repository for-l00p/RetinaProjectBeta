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
//#include "VoronoiTest.h"
#include "Voronoi.h"
#include "fstream"
//#include "Voronoi.h"

const double PI = 3.1415926535;
const double probabilityRED=0.64;
const double probabilityGREEN=0.32;
//probabilityBlue= 0.02;

Quadtree<Photoreceptor> retina = Quadtree<Photoreceptor>();

const int numCone = 10000;//number of cones to be generated
const int numRds = 10000;//number of rods to be generated


//eccentricities for data points for photoreceptors
std::array<double, 31> coneIntervals{ 0, 0.0494955, 0.0976036, 0.149798, 0.197754, 0.297772, 0.39771, 0.494803, 0.594697, 0.694594, 0.793082, 0.892953, 0.994235, 1, 1.9887, 2.95198, 3.94633, 4.9096, 5.93503, 6.96045, 7.98588, 8.94915, 9.9435, 10.9379, 11.9944, 12.9266, 13.952, 14.9153, 15.9407, 16.904, 17.8983 };
std::array<double, 29> rodIntervals{ 0, 0.0536332, 0.0986159, 0.147059, 0.198962, 0.301038, 0.396194, 0.49827, 0.595156, 0.695502, 0.797578, 0.896194, 0.99654, 1.0166, 1.99218, 2.99914, 4.07128, 5.00363, 5.97013, 6.97032, 7.97061, 8.93607, 9.93635, 10.9365, 11.9365, 12.9713, 13.9023, 14.8679, 15.868 };
std::array<double, 31> ganglionIntervals{ 0, 0.0632689, 0.105448, 0.147627, 0.203866, 0.302285, 0.400703, 0.499121, 0.604569, 0.695958, 0.808436, 0.906854, 0.998243, 1.51142, 2.00351, 2.52373, 3.02285, 3.99297, 4.01773, 5.07092, 6.0461, 7.02128, 8.11348, 9.12766, 10.1418, 11.156, 12.1312, 13.1064, 14.1596, 15.1348, 16.1099 };

//densities in 1000s of photoreceptors/mm^2 for each interval
std::array<double, 31> coneDensity{ 197.297, 162.184, 121.215, 99.1666, 79.8188, 57.3413, 46.1251, 39.4121, 34.5021, 29.1417, 24.2311, 22.4743, 20.2677, 19.5799, 11.6766, 9.07821, 6.98762, 5.74361, 5.06378, 4.72255, 4.43775, 4.20955, 3.8684, 3.80941, 3.52454, 3.40928, 3.35022, 3.34774, 3.17581, 3.11691, 3.34009 };
std::array<double, 29> rodDensity{ 0, 0.0148568, 0.0273174, 1.42578, 3.37921, 13.3798, 26.4255, 36.1491, 45.0402, 52.8242, 59.7777, 64.7912, 69.2511, 68.9053, 107.757, 132.022, 138.163, 136.795, 133.659, 126.543, 119.869, 111.87, 105.196, 98.0802, 90.0802, 82.9626, 75.4076, 68.2931, 60.7351 };
std::array<double, 31> ganglionDensity{ 0, 0.110385, 0.783357, 1.56869, 4.03902, 10.8902, 16.6178, 21.1094, 22.4547, 23.9128, 25.5951, 26.7159, 26.7133, 22.7663, 16.2357, 11.2772, 7.89242, 3.93258, 3.90423, 2.3493, 1.67324, 1.13239, 0.828169, 0.659155, 0.490141, 0.422535, 0.371831, 0.304225, 0.253521, 0.202817, 0.202817 };

std::piecewise_linear_distribution<double>
coneDistribution(coneIntervals.begin(), coneIntervals.end(), coneDensity.begin());

std::piecewise_linear_distribution<double>
rodDistribution(rodIntervals.begin(), rodIntervals.end(), rodDensity.begin());

std::piecewise_linear_distribution<double>
ganglionDistribution(ganglionIntervals.begin(), ganglionIntervals.end(), ganglionDensity.begin());

std::default_random_engine generator;

double getDistance(int type) {//0 is cone, 1 is rod, 2 is ganglion
	if (type == 0)
		return coneDistribution(generator);
	else if (type == 1)
		return rodDistribution(generator);
	else 
		return ganglionDistribution(generator);
}

Neuron* build(int type) {// 0 is cone, 1 is rod, 2 is ganglion
	// Method creates rods and cones based on polar coordinates 

	double r = getDistance(type);
	double theta = ((double)rand() / (RAND_MAX)) * 2.0 * PI;

	double x = r*cos(theta);
	double y = r*sin(theta);

	std::cout << "" + x + ", " + y + "\n";

	Neuron* n;
	//std::cout << x << ", " << y << "\n";
	double coneType = ((double)rand() / (RAND_MAX));
	Point loc = Point(x, y);
	if (type == 0) {
		n = new Rod(loc);
	}
	else if (type == 1) {
		n = new Cone(loc);
	}
	else {
		n = new Ganglion(loc);
	}
	return n;
}

int main()
{
	srand((unsigned int)time(NULL));

	std::vector<Photoreceptor*> map;
	for (int i = 0; i < 100; i++) {
		Rod* temp = (Rod) build(0);
		map.push_back(temp);
		Data<Photoreceptor> cur((Photoreceptor)*temp);
		retina.insert(cur);
	}
//	retina.getTree(); 

	std::vector<std::vector<Photoreceptor*>> x = {};

	for (int i = 0; i < 10000; i++) {
		build();
		Cone* tempC = buildCone();
		map.push_back(tempC);
		Data<Photoreceptor> curC((Photoreceptor)*tempC);
		retina.insert(curC);
	}

	retina.getTree();
	/*for (int i = 0; i < 10; i++) {
		std::vector<Photoreceptor*> currentRow;
		for (int j = 0; j < 10; j++) {
			auto* cell = build(i, j);
			//std::cout << cell->xc << " ";
		//	Photoreceptor* current = build(i, j);
			currentRow.push_back(cell);
			Data<Photoreceptor> cur((Photoreceptor)*cell);
			//cur.cell = *current;
			//cur.setPoint();
			retina.insert(cur);
		}
		x.push_back(currentRow);
	} */
	
	/*testingVoronoi();
	using namespace vor;
	vor::Voronoi * v;
	vor::Vertices * ver; 
	vor::Vertices * dir; 
	vor::Edges * edg;	 

	double w = 10000;
	v = new Voronoi();
	ver = new Vertices();
	dir = new Vertices();

	srand(time(NULL));

/*	for (int i = 0; i<50; i++)
	{

		ver->push_back(new Point(w * (double)rand() / (double)RAND_MAX, w * (double)rand() / (double)RAND_MAX));
		dir->push_back(new Point((double)rand() / (double)RAND_MAX - 0.5, (double)rand() / (double)RAND_MAX - 0.5));
	} 

	//edg = v->GetEdges(ver, w, w);
	std::cout << "voronois done!\n"; */

	int j;
	std::cin >> j;
	return 0;
}
