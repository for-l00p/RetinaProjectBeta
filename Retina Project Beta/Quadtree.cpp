#pragma once
#include "stdafx.h"
#include <iostream>
//#include "VoronoiTest.h"
#include "Quadtree.h"

//NOTE: This quadtree is based on a quadtree implementation from https://codereview.stackexchange.com/questions/84374/quadtree-implementation with several modifications.


Quadtree<Photoreceptor>::Quadtree() {
	nw = nullptr;
	ne = nullptr;
	sw = nullptr;
	se = nullptr;
	boundary = AABB(Point(5.0,5.0), Point(5.0,5.0));
	position = "hello";
	objects = std::vector< Data<Photoreceptor> >();
}

//template <typename T>
Quadtree<Photoreceptor>::Quadtree(AABB boundary)
{
	objects = std::vector< Data<Photoreceptor> >();
	nw = nullptr;
	ne = nullptr;
	sw = nullptr;
	se = nullptr;
	position = "hi";
	this->boundary = boundary;
}

//template <typename T>
Quadtree<Photoreceptor>::~Quadtree()
{
	delete nw;
	delete sw;
	delete ne;
	delete se;
}

//template <typename T>
void Quadtree<Photoreceptor>::subdivide()
{
	Point qSize = Point(boundary.halfSize.x/2, boundary.halfSize.y/2);
	Point qCentre = Point(boundary.centre.x - qSize.x, boundary.centre.y - qSize.y);
	nw = new Quadtree(AABB(qCentre, qSize));

	qCentre = Point(boundary.centre.x + qSize.x, boundary.centre.y - qSize.y);
	ne = new Quadtree(AABB(qCentre, qSize));

	qCentre = Point(boundary.centre.x - qSize.x, boundary.centre.y + qSize.y);
	sw = new Quadtree(AABB(qCentre, qSize));

	qCentre = Point(boundary.centre.x + qSize.x, boundary.centre.y + qSize.y);
	se = new Quadtree(AABB(qCentre, qSize));
}
int counter = 0;
//template <typename T>
bool Quadtree<Photoreceptor>::insert(Data<Photoreceptor> d)
{
	//std::cout << "putting stuff inside" << std::endl;
	if (!boundary.contains(d.pos))
	{
		//std::cout << "outside boundary" << std::endl;
		return false;
	}
	//std::cout << "inside boundary" << std::endl;
	if (objects.size() < CAPACITY)
	{
		counter++;
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

//template <typename T>
std::vector< Data<Photoreceptor> > Quadtree<Photoreceptor>::queryRange(AABB range)
{
	std::vector< Data<Photoreceptor> > pInRange = std::vector< Data<Photoreceptor> >();

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

	std::vector< Data<Photoreceptor> > temp = nw->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = ne->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = sw->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = se->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	return pInRange;
}

void Quadtree<Photoreceptor>::getTree() {
	if (!this) {
		//std::cout << "root is null";
		return;
	}
	//std::cout << "hello";
	for (auto i : this->objects) {
		//std::cout << "hello" << std::endl;

		//std::cout << i.pos.x << ' ' << i.pos.y << std::endl;
	}
	//std::cout << (this->position).c_str() << "  ";
	
	nw->getTree();
	ne->getTree();
	sw->getTree();
	se->getTree();
}
