#include "stdafx.h"
#include "Smooth.h"


int dim = 2;
int k = 100; //# of clusters to have
int maxPts = 100;
int stages = 1;
static ifstream dataStream;


KMterm	term(100, 0, 0, 0,		// run for 100 stages
	0.10,			// min consec RDL
	0.10,			// min accum RDL
	3,			// max run stages
	0.50,			// init. prob. of acceptance
	10,			// temp. run length
	0.95);

void smooth()
{
	istream* dataIn = NULL;
	file.open("inputCells.txt");
	dataStream.open("outputCells.txt", ios::in);
	if (!dataStream) {
		cerr << "Cannot open data file\n";
	//	kmExit(1);
	}

	dataIn = &dataStream;

	term.setAbsMaxTotStage(stages);		// set number of stages

	KMdata dataPts(dim, maxPts);		// allocate data storage
	int nPts = 0;				// actual number of points
								// generate points
	if (dataIn != NULL) {			// read points from file
		while (nPts < maxPts && readPt(*dataIn, dataPts[nPts])) nPts++;
	}

	cout << "Data Points:\n";			// echo data points
	for (int i = 0; i < nPts; i++)
		printPt(cout, dataPts[i]);

	dataPts.setNPts(nPts);			// set actual number of pts
	dataPts.buildKcTree();			// build filtering structure

	KMfilterCenters ctrs(k, dataPts);		// allocate centers

											// run each of the algorithms
	cout << "\nExecuting Clustering Algorithm: Lloyd's\n";
	KMlocalLloyds kmLloyds(ctrs, term);		// repeated Lloyd's
	ctrs = kmLloyds.execute();			// execute
	printSummary(kmLloyds, dataPts, ctrs);	// print summary

	file.close();

	//kmExit(0);
}


//----------------------------------------------------------------------
//  Reading/Printing utilities
//	readPt - read a point from input stream into data storage
//		at position i.  Returns false on error or EOF.
//	printPt - prints a points to output file
//----------------------------------------------------------------------
bool readPt(istream& in, KMpoint& p)
{
	for (int d = 0; d < dim; d++) {
		if (!(in >> p[d])) return false;
	}
	return true;
}

void printPt(ostream& out, const KMpoint& p)
{
	out << "(" << p[0];
	for (int i = 1; i < dim; i++) {
		out << ", " << p[i];
		file << p[0] << "," << p[i] << "\n";
	}
	out << ")\n";
}

//------------------------------------------------------------------------
//  Print summary of execution
//------------------------------------------------------------------------
void printSummary(
	const KMlocal&		theAlg,		// the algorithm
	const KMdata&		dataPts,	// the points
	KMfilterCenters&		ctrs)		// the centers
{
	cout << "Number of stages: " << theAlg.getTotalStages() << "\n";
	cout << "Average distortion: " <<
		ctrs.getDist(false) / double(ctrs.getNPts()) << "\n";
	// print final center points
	cout << "(Final Center Points:\n";
	ctrs.print();
	cout << ")\n";
	// get/print final cluster assignments
	KMctrIdxArray closeCtr = new KMctrIdx[dataPts.getNPts()];
	double* sqDist = new double[dataPts.getNPts()];
	ctrs.getAssignments(closeCtr, sqDist);

	*kmOut << "(Cluster assignments:\n"
		<< "    Point  Center  Squared Dist\n"
		<< "    -----  ------  ------------\n";
	for (int i = 0; i < dataPts.getNPts(); i++) {
		*kmOut << "   " << setw(5) << i
			<< "   " << setw(5) << closeCtr[i]
			<< "   " << setw(10) << sqDist[i]
			<< "   " << setw(5) << dataPts.getPts()[i][0] << "," << dataPts.getPts()[i][1] << "\n";
	}
	*kmOut << ")\n";
	delete[] closeCtr;
	delete[] sqDist;
}
