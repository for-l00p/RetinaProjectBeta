#pragma once
#include "stdafx.h"
#include <vector>
#include "boost_1_63_0\boost\polygon\voronoi.hpp"
using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;
using boost::polygon::geometry_concept;
using boost::polygon::point_traits;
using boost::polygon::point_concept;
using boost::polygon::orientation_2d;
using boost::polygon::segment_concept;
using boost::polygon::direction_1d;




struct Point {
	int a;
	int b;

	Point(int x, int y) : a(x), b(y) {}
};

struct Segment {
	Point p0;
	Point p1;
	Segment(int x1, int y1, int x2, int y2) : p0(x1, y1), p1(x2, y2) {}
};


int testingVoronoi();

int iterate_primary_edges2(const voronoi_diagram<double> &vd);

