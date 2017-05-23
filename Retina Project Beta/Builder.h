#include "Quadtree.h"

#pragma once
#ifndef _BUILDERFILE_
#define _BUILDERFILE_

const double RETINA_RADIUS = 12;
Quadtree<class Photoreceptor>* photoreceptorBuilder(int numRods, int numCones);
Quadtree<class Bipolar>* bipolarBuilder(Quadtree<class Photoreceptor>* q, int numBipolars);
Quadtree<class Ganglion>* ganglionBuilder(Quadtree<class Bipolar>* q, int numGanglia);

#endif