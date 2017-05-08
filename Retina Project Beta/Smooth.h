#pragma once
#include "stdafx.h"
#include <cstdlib>			// C standard includes
#include <iostream>			// C++ I/O
#include <string>			// C++ strings
#include "KMlocal.h"			// k-means algorithms

using namespace std;

void printSummary(			// print final summary
	const KMlocal&	theAlg,		// the algorithm
	const KMdata&	dataPts,	// the points
	KMfilterCenters&	ctrs);		// the centers

bool readPt(				// read a point
	istream&		in,		// input stream
	KMpoint&		p);		// point (returned)

void printPt(				// print a point
	ostream&		out,		// output stream
	const KMpoint&	p);		// the point
	// temp. reduction factor

					//----------------------------------------------------------------------
					//  Main program
					//----------------------------------------------------------------------

static ofstream file;
void smooth();