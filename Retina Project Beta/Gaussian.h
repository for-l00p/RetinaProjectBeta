#pragma once
#include <iostream>
#include <math.h>
#include <cmath>
#include <iomanip>


using namespace std;
const double PI = 3.141592653589793238463;

//creating hte gaussian receptive field shape
//do this twice: once for inner? once for outer?
//and subtract/add them?

//output of ganglion cell should be the 
//sum(filter[x][y] * photoreceptor getting that pixel)

void gaussian(double *filter[]) {
	double sigma = 1.0;
	double r;
	double s = 2.0*sigma*sigma;

	double sum;

	for (int x = -2; x <= 2; x++) {

		for (int y = -2; y <= 2; y++) {
			r = sqrt(x*x + y*y);
			filter[x + 2][y+2] = (exp(-(r*r) / s)) / (PI * s);
			sum += filter[x + 2][y + 2];

		}
	}
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			filter[i][j] /= sum;

};
