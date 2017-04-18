#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>

//NOTE: This quadtree is based largely from implementation at https://codereview.stackexchange.com/questions/84374/quadtree-implementation with several modifications.

struct Point
{
	float x = 0.0f;
	float y = 0.0f;
};

struct AABB
{
	Point centre;
	Point halfSize;

	AABB(Point centre = Point(), Point halfSize = Point()) : centre(centre), halfSize(halfSize) {};

	bool contains(Point a) const
	{
		if (a.x < centre.x + halfSize.x && a.x > centre.x - halfSize.x)
		{
			if (a.y < centre.y + halfSize.y && a.y > centre.y - halfSize.y)
			{
				return true;
			}
		}
		return false;
	}

	bool intersects(const AABB& other) const
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

template <typename T>
struct Data
{
	Point pos;
	T* load;

	Data(Point pos = {}, T* data = nullptrptr) : pos(pos), load(data) {};
};


template <class T>
class Quadtree
{
private:
	//4 children
	Quadtree* nw;
	Quadtree* ne;
	Quadtree* sw;
	Quadtree* se;

	AABB boundary;

	std::vector< Data<T> > objects;

	static constexpr int CAPACITY = 4;
public:
	Quadtree<T>();
	Quadtree<T>(AABB boundary);

	~Quadtree();

	bool insert(Data<T> d);
	void subdivide();
	std::vector< Data<T> > queryRange(AABB range);
};

template <class T>
Quadtree<T>::Quadtree()
{
	nw = nullptr;
	ne = nullptr;
	sw = nullptr;
	se = nullptr;
	boundary = AABB();
	objects = std::vector< Data<T> >();
}

template <class T>
Quadtree<T>::Quadtree(AABB boundary)
{
	objects = std::vector< Data<T> >();
	nw = nullptr;
	ne = nullptr;
	sw = nullptr;
	se = nullptr;
	this->boundary = boundary;
}

template <class T>
Quadtree<T>::~Quadtree()
{
	delete nw;
	delete sw;
	delete ne;
	delete se;
}

template <class T>
void Quadtree<T>::subdivide()
{
	Point qSize = boundary.halfSize;
	Point qCentre = Point(boundary.centre.x - qSize.x, boundary.centre.y - qSize.y);
	nw = new Quadtree(AABB(qCentre, qSize));

	qCentre = Point(boundary.centre.x + qSize.x, boundary.centre.y - qSize.y);
	ne = new Quadtree(AABB(qCentre, qSize));

	qCentre = Point(boundary.centre.x - qSize.x, boundary.centre.y + qSize.y);
	sw = new Quadtree(AABB(qCentre, qSize));

	qCentre = Point(boundary.centre.x + qSize.x, boundary.centre.y + qSize.y);
	se = new Quadtree(AABB(qCentre, qSize));
}

template <class T>
bool Quadtree<T>::insert(Data<T> d)
{
	if (!boundary.contains(d.pos))
	{
		return false;
	}

	if (objects.size() < CAPACITY)
	{
		objects.push_back(d);
		return true;
	}

	if (nw == nullptr)
	{
		subdivide();
	}

	if (nw->insert(d))
	{
		return true;
	}
	if (ne->insert(d))
	{
		return true;
	}
	if (sw->insert(d))
	{
		return true;
	}
	if (se->insert(d))
	{
		return true;
	}

	return false;
}

template <class T>
std::vector< Data<T> > Quadtree<T>::queryRange(AABB range)
{
	std::vector< Data<T> > pInRange = std::vector< Data<T> >();

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

	std::vector< Data<T> > temp = nw->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = ne->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = sw->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = se->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	return pInRange;
}
