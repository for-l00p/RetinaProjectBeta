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
//#include <SFML/Graphics.hpp>

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