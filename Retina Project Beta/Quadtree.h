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
	QuadRegion(double topLeftX, double topLeftY, double width, double height) {};

	bool contains(Point a) const
	{
		if (a.x < centre.x + halfSize.x && a.x >= centre.x - halfSize.x)
		{
			if (a.y < centre.y + halfSize.y && a.y >= centre.y - halfSize.y)
			{
				return true;
			}
		}
		return false;
	}

	bool contains(QuadRegion r) const
	{
		if ((centre.x - halfSize.x < r.centre.x - r.halfSize.x) &&
			(centre.x + halfSize.x >= r.centre.x - r.halfSize.x) && 
			(centre.y - halfSize.y < r.centre.y - r.halfSize.y) &&
			(centre.y + halfSize.y >= r.centre.y - r.halfSize.y))
		{
			return true;
		}
		return false;
	}

	bool intersects(const QuadRegion& other) const
	{
		//this right > that left                                          this left <s that right
		if (centre.x + halfSize.x > other.centre.x - other.halfSize.x || centre.x - halfSize.x < other.centre.x + other.halfSize.x)
		{
			// This bottom > that top
			if (centre.y + halfSize.y > other.centre.y - other.halfSize.y || centre.y - halfSize.y < other.centre.y + other.halfSize.y)
			{
				return true;
			}
		}
		return false;
	}
};

struct QuadDifference
{
	QuadRegion quad1;
	QuadRegion quad2;

	QuadDifference(QuadRegion region1, QuadRegion region2) : quad1(region1), quad2(region2) {};

	bool contains(Point a) const
	{
		if ((quad1.contains(a) && !quad1.contains(a)) || (!quad1.contains(a) && quad2.contains(a)))
		{
			return true;
		}
		return false;
	}

	bool intersects(const QuadRegion& other) const
	{
		//this right > that left                                          this left <s that right
		if ((other.intersects(quad1) && !quad2.contains(other)) || (other.intersects(quad2) && !quad1.contains(other)))
		{
			return true;
		}
		return false;
	}
};

template <typename T>
struct Data
{
	Point pos;
	T* load;

	Data<T>(Point pos = Point(), T* data = NULL) : pos(pos), load(data) {};
};

template<class T>
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
	std::vector<Data<T>> objects;

	static constexpr int CAPACITY = 4;
public:
	Quadtree<T>();
	Quadtree<T>(QuadRegion boundary);

	~Quadtree<T>();

	bool insert(Data<T> d);
	void subdivide();
	QuadRegion getBoundary();
	std::vector<Data<T>> queryRange(QuadRegion range);
	std::vector<Data<T>> queryRange(QuadDifference range);
	std::vector<T*> queryRangeObjects(QuadRegion range);
	std::vector<T*> queryRangeObjects(QuadDifference range);
	void getTree(std::string prechain, int level = 1);
	void printTreeBoundaries(int level = 1);
};

#endif