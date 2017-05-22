#pragma once
#ifndef _POINT_
#define _POINT_
#include <string>

struct Point {
	double x;
	double y;
	Point() :x(0.0), y(0.0) {}
	Point(double xc, double yc) : x(xc), y(yc) {}

	std::string toString() {
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}
};

#endif
