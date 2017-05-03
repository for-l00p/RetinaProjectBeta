#pragma once
#ifndef _POINT_
#define _POINT_


struct Point {
	int x;
	int y;
	Point() :x(0), y(0) {}
	Point(int xc, int yc) : x(xc), y(yc) {}
};

#endif