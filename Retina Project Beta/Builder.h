#include "Quadtree.h"

#pragma once
#ifndef _BUILDERFILE_
#define _BUILDERFILE_

const double RETINA_RADIUS = 12;
Quadtree<Photoreceptor> photoreceptorBuilder(int numRods, int numCones);
Quadtree<Bipolar> bipolarBuilder(Quadtree<Photoreceptor> q, int numBipolars);
Quadtree<Ganglion> ganglionBuilder(Quadtree<Bipolar> q, int numGanglia);

#endif