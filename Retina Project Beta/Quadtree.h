//#ifndef QUADTREE
//#define QUADTREE
#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
//#include "Photoreceptor.h"
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

	bool QuadRegion::intersects(const QuadDifference& other) const
	{
		other.intersects(*this);
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
	std::vector<Data<T>*> objects;

	static constexpr int CAPACITY = 4;
public:
	Quadtree<T>() {
		nw = nullptr;
		ne = nullptr;
		sw = nullptr;
		se = nullptr;

		boundary = QuadRegion(Point(5.0, 5.0), Point(5.0, 5.0));
		position = "hello";
		objects = std::vector<Data<T>*>();
	}
	Quadtree(QuadRegion boundary)
	{
		objects = std::vector<Data<T>*>();
		nw = nullptr;
		ne = nullptr;
		sw = nullptr;
		se = nullptr;
		position = "hi";
		this->boundary = boundary;
	}
	~Quadtree<T>() {
		if (nw != nullptr) {
			delete nw;
			delete sw;
			delete ne;
			delete se;
		}
	}

	void subdivide()
	{
		Point qSize = Point(boundary.halfSize.x / 2, boundary.halfSize.y / 2);
		Point qCentre = Point(boundary.centre.x - qSize.x, boundary.centre.y - qSize.y);

		nw = new Quadtree(QuadRegion(qCentre, qSize));

		qCentre = Point(boundary.centre.x + qSize.x, boundary.centre.y - qSize.y);
		ne = new Quadtree(QuadRegion(qCentre, qSize));

		qCentre = Point(boundary.centre.x - qSize.x, boundary.centre.y + qSize.y);
		sw = new Quadtree(QuadRegion(qCentre, qSize));

		qCentre = Point(boundary.centre.x + qSize.x, boundary.centre.y + qSize.y);
		se = new Quadtree(QuadRegion(qCentre, qSize));
	}

	bool insert(Data<T>* d)
	{
		//std::cout << "putting stuff inside" << std::endl;
		if (!boundary.contains(d->pos))
		{
			//std::cout << "outside boundary" << std::endl;
			return false;
		}
		//std::cout << "inside boundary" << std::endl;
		if (objects.size() < CAPACITY)
		{
			//counter++;
			objects.push_back(d);
			return true;
		}

		if (nw == nullptr)
		{
			subdivide();
		}

		if (nw->insert(d))
		{
			position = "nw";
			return true;
		}
		if (ne->insert(d))
		{
			position = "ne";
			return true;
		}
		if (sw->insert(d))
		{
			position = "sw";
			return true;
		}
		if (se->insert(d))
		{
			position = "se";
			return true;
		}

		return false;
	}
	
	template<class U>
	std::vector<Data<T>*> queryRange(U range)
	{
		std::vector<Data<T>*> pInRange = std::vector<Data<T>*>();

		if (!boundary.intersects(range))
		{
			return pInRange;
		}

		for (auto&& object : objects)
		{
			if (range.contains(object.pos))
			{
				pInRange.push_back(object);
			}
		}

		if (nw == nullptr)
		{
			return pInRange;
		}

		std::vector<Data<T>*> temp = nw->queryRange(range);
		pInRange.insert(pInRange.end(), temp.begin(), temp.end());

		temp = ne->queryRange(range);
		pInRange.insert(pInRange.end(), temp.begin(), temp.end());

		temp = sw->queryRange(range);
		pInRange.insert(pInRange.end(), temp.begin(), temp.end());

		temp = se->queryRange(range);
		pInRange.insert(pInRange.end(), temp.begin(), temp.end());

		return pInRange;
	}

	template<class U>
	std::vector<T*> queryRangeObjects(U range) {
		std::vector<T*> pInRange = std::vector<T*>();

		if (!boundary.intersects(range))
		{
			return pInRange;
		}

		for (auto&& object : objects)
		{
			if (range.contains(object->pos))
			{
				pInRange.push_back(object->load);
			}
		}

		if (nw == nullptr)
		{
			return pInRange;
		}

		std::vector<T*> temp = nw->queryRangeObjects(range);
		pInRange.insert(pInRange.end(), temp.begin(), temp.end());

		temp = ne->queryRangeObjects(range);
		pInRange.insert(pInRange.end(), temp.begin(), temp.end());

		temp = sw->queryRangeObjects(range);
		pInRange.insert(pInRange.end(), temp.begin(), temp.end());

		temp = se->queryRangeObjects(range);
		pInRange.insert(pInRange.end(), temp.begin(), temp.end());

		return pInRange;
	}

	void getTree(std::string prechain, int level = 1);
	void printTreeBoundaries(int level = 1);
	QuadRegion getBoundary();
};

template<typename T>
QuadRegion Quadtree<T>::getBoundary() {
	return boundary;
}

template<typename T>
void Quadtree<T>::getTree(std::string prechain, int level = 1) {
	//std::cout << "in getTree()" << std::endl;
	if (!this) {
		//std::cout << "root is null";
		return;
	}

	for (auto i : this->objects)
		std::cout << i->getPoint().x << ' ' << i->getPoint().y << std::endl;
	//std::cout << (this->position).c_str() << "  ";

	std::cout << prechain << "Sublevel " << ++level << " NW Tree:\n";
	nw->getTree(prechain + "Sublevel " + std::to_string(level) + " NW Tree", level);
	std::cout << prechain << "Sublevel " << level << " NE Tree:\n";
	ne->getTree(prechain + "Sublevel " + std::to_string(level) + " NE Tree", level);
	std::cout << prechain << "Sublevel " << level << " SW Tree:\n";
	sw->getTree(prechain + "Sublevel " + std::to_string(level) + " SW Tree", level);
	std::cout << prechain << "Sublevel " << level << " SE Tree:\n";
	se->getTree(prechain + "Sublevel " + std::to_string(level) + " SE Tree", level);
}

template<typename T>
void Quadtree<T>::printTreeBoundaries(int level = 1)
{
	//std::cout << "in getTree()" << std::endl;
	if (!this) {
		//std::cout << "root is null";
		return;
	}

	std::cout << "Tree Boundary: Center: " + boundary.centre.toString() + "Half-Size: " + boundary.halfSize.toString() + "\n";
	if (nw == nullptr) {
		return;
	}
	int l = 0;
	std::cin >> l;
	std::cout << ++level << " NW ";
	nw->printTreeBoundaries(level);
	std::cout << level << " NE ";
	ne->printTreeBoundaries(level);
	std::cout << level << " SW ";
	sw->printTreeBoundaries(level);
	std::cout << level << " SE ";
	se->printTreeBoundaries(level);
}

//#endif