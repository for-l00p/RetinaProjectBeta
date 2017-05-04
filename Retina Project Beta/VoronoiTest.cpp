#pragma once
// Boost.Polygon library voronoi_basic_tutorial.cpp file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.
#include "stdafx.h"
#include <cstdio>
#include <vector>
#include "VoronoiTest.h"
#include <boost/polygon/voronoi.hpp>
using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;
using boost::polygon::x;
using boost::polygon::y;
using boost::polygon::low;
using boost::polygon::high;

//#include "voronoi_visual_utils.hpp"

namespace boost {
	namespace polygon {

		template <>
		struct geometry_concept<Point> {
			typedef point_concept type;
		};

		template <>
		struct point_traits<Point> {
			typedef int coordinate_type;

			static inline coordinate_type get(
				const Point& point, orientation_2d orient) {
				return (orient == HORIZONTAL) ? point.x: point.y;
			}
		};

		template <>
		struct geometry_concept<Segment> {
			typedef segment_concept type;
		};

		template <>
		struct segment_traits<Segment> {
			typedef int coordinate_type;
			typedef Point point_type;

			static inline point_type get(const Segment& segment, direction_1d dir) {
				return dir.to_int() ? segment.p1 : segment.p0;
			}
		};
	}  // polygon
}  // boost

// Traversing Voronoi edges using cell iterator.
int iterate_primary_edges2(const voronoi_diagram<double> &vd) {
	int result = 0;
	for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
		it != vd.cells().end(); ++it) {
		const voronoi_diagram<double>::cell_type& cell = *it;
		const voronoi_diagram<double>::edge_type* edge = cell.incident_edge();
		// This is convenient way to iterate edges around Voronoi cell.
		do {
			if (edge->is_primary())
				++result;
			edge = edge->next();
		} while (edge != cell.incident_edge());
	}
	return result;
}

int testingVoronoi() {
	// Preparing Input Geometries.
	std::vector<Point> points;
	points.push_back(Point(0.0, 0.0));
	points.push_back(Point(1.2, 6.3));
	std::vector<Segment> segments;
//	segments.push_back(Segment(-4, 5, 5, -1));
//	segments.push_back(Segment(3, -11, 13, -1));

	// Construction of the Voronoi Diagram.
	voronoi_diagram<double> vd;
	construct_voronoi(points.begin(), points.end(),
		segments.begin(), segments.end(),
		&vd);

	// Traversing Voronoi Graph.

	printf("Traversing Voronoi graph.\n");
	printf("Number of visited primary edges using cell iterator: %d\n",
		iterate_primary_edges2(vd));
	printf("\n");


	// Using color member of the Voronoi primitives to store the average number
	// of edges around each cell (including secondary edges).

	printf("Number of edges (including secondary) around the Voronoi cells:\n");
	for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin();
		it != vd.edges().end(); ++it) {
		std::size_t cnt = it->cell()->color();
		it->cell()->color(cnt + 1);
	}
	for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
		it != vd.cells().end(); ++it) {
		printf("%lu ", it->color());
	}
	printf("\n");
	printf("\n");

	unsigned int cell_index = 0;
	for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
		it != vd.cells().end(); ++it) {
		if (it->contains_point()) {
			std::size_t index = (it->source_index());
			Point p = points[index];
			printf("Cell #%ud contains a point: (%d, %d).\n",
				cell_index, x(p), y(p));
		}
		++cell_index;
	}

	return 0;
}