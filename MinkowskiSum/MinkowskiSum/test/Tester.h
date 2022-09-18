#pragma once

#include "Point.h"
#include "ConvexPolygon.h"


class Tester
{
public:
	Tester();
	~Tester();

	void TestPointAngleCompare() const;
	void TestPolygonRead() const;
	void TestIterators() const;
	void TestMinkowskiSum() const;
};
