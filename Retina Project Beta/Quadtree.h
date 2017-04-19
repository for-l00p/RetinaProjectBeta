#pragma once
#include "stdafx.h"
#ifndef QUADTREE
#define QUADTREE

struct Point
{
};

struct AABB
{
	bool contains(Point a) const{}

	bool intersects(const AABB& other) const {}
};

template <typename T>
struct Data {};


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

#endif