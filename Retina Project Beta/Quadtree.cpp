#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include "Quadtree.h"

//NOTE: This quadtree is based on a quadtree implementation from https://codereview.stackexchange.com/questions/84374/quadtree-implementation with several modifications.

template <typename T>
Quadtree<T>::Quadtree()
{
	nw = nullptr;
	ne = nullptr;
	sw = nullptr;
	se = nullptr;
	boundary = AABB();
	objects = std::vector< Data<T> >();
}

template <typename T>
Quadtree<T>::Quadtree(AABB boundary)
{
	objects = std::vector< Data<T> >();
	nw = nullptr;
	ne = nullptr;
	sw = nullptr;
	se = nullptr;
	this->boundary = boundary;
}

template <typename T>
Quadtree<T>::~Quadtree()
{
	delete nw;
	delete sw;
	delete ne;
	delete se;
}

template <typename T>
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

template <typename T>
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

template <typename T>
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