#ifndef QUADTREE
#define QUADTREE
#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "Photoreceptor.h"
#include "Point.h"

struct QuadRegion
{
	Point centre;
	Point halfSize;

	QuadRegion(Point centre = Point(), Point halfSize = Point()) : centre(centre), halfSize(halfSize) {};

	bool contains(Point a) const{
		if (a.x < centre.x + halfSize.x && a.x >= centre.x - halfSize.x){
			if (a.y < centre.y + halfSize.y && a.y >= centre.y - halfSize.y){
				return true;
			}
		}
		return false;
	}

	bool intersects(const QuadRegion& other) const
	{
		//this right > that left                                          this left <s that right
		if (centre.x + halfSize.x > other.centre.x - other.halfSize.x || centre.x - halfSize.x < other.centre.x + other.halfSize.x){
			// This bottom > that top
			if (centre.y + halfSize.y > other.centre.y - other.halfSize.y || centre.y - halfSize.y < other.centre.y + other.halfSize.y){
				return true;
			}
		}
		return false;
	}
};


template <typename T>
struct Data
{
	Point pos;
	Photoreceptor neuron;
	T* load;


	Data(Photoreceptor cell) {
		neuron = cell;
		pos = Point(cell.getX(), cell.getY());
	}
	/*	T setPoint() {
	pos = Point(cell.xc, cell.yc);
	}*/
};


template <typename T>
class Quadtree
{
protected:
	//4 children
	Quadtree* nw;
	Quadtree* ne;
	Quadtree* sw;
	Quadtree* se;

	QuadRegion boundary;
	std::string position;
	std::vector< Data<T> > objects;

	static constexpr int CAPACITY = 4;
public:
	Quadtree<T>();
	Quadtree<T>(QuadRegion boundary);

	~Quadtree();

	bool insert(Data<T> d);
	void subdivide();
	std::vector< Data<T> > queryRange(QuadRegion range);
	void getTree();
};

#endif