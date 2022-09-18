#include "Tester.h"

#include "Point.h"
#include "ConvexPolygon.h"

#include <cassert>
#include <iostream>


Tester::Tester()
{}

Tester::~Tester()
{}

void Tester::TestPointAngleCompare() const
{
	Point a1(1, 1), b1(-1, 1); // -1
	Point a2(-2, -3), b2(-2, -4); // -1
	Point a3(4, 3), b3(2, 0); // 1
	Point a4(-5, -1), b4(-1, 0); // 1
	Point a5(1, 0), b5(2, 0); // 0
	Point a6(-4, 0), b6(-6, 0); // 0
	Point a7(1, 0), b7(-2, 0); // -1 
	Point a8(2, 2), b8(3, 3); // 0
	Point a9(4, 4), b9(4, -4); // -1

	assert(Point::AngleBetweenVecAndOxCompare(a1, b1) == -1);
	assert(Point::AngleBetweenVecAndOxCompare(a2, b2) == -1);
	assert(Point::AngleBetweenVecAndOxCompare(a3, b3) == 1);
	assert(Point::AngleBetweenVecAndOxCompare(a4, b4) == 1);
	assert(Point::AngleBetweenVecAndOxCompare(a5, b5) == 0);
	assert(Point::AngleBetweenVecAndOxCompare(a6, b6) == 0);
	assert(Point::AngleBetweenVecAndOxCompare(a7, b7) == -1);
	assert(Point::AngleBetweenVecAndOxCompare(a8, b8) == 0);
	assert(Point::AngleBetweenVecAndOxCompare(a9, b9) == -1);

	assert(Point::AngleBetweenVecAndOxCompare(b1, a1) == 1);
	assert(Point::AngleBetweenVecAndOxCompare(b2, a2) == 1);
	assert(Point::AngleBetweenVecAndOxCompare(b3, a3) == -1);
	assert(Point::AngleBetweenVecAndOxCompare(b4, a4) == -1);
	assert(Point::AngleBetweenVecAndOxCompare(b5, a5) == 0);
	assert(Point::AngleBetweenVecAndOxCompare(b6, a6) == 0);
	assert(Point::AngleBetweenVecAndOxCompare(b7, a7) == 1);
	assert(Point::AngleBetweenVecAndOxCompare(b8, a8) == 0);
	assert(Point::AngleBetweenVecAndOxCompare(b9, a9) == 1);
}

void Tester::TestPolygonRead() const
{
	ConvexPolygon polygonTriLeft;
	ConvexPolygon polygonTriRight;
	ConvexPolygon polygonSqLeft;
	ConvexPolygon polygonSqRight;

	assert(polygonTriLeft.ReadFromFile("polygons/polygonTriLeft.txt"));
	assert(polygonTriRight.ReadFromFile("polygons/polygonTriRight.txt"));
	assert(polygonSqLeft.ReadFromFile("polygons/polygonSqLeft.txt"));
	assert(polygonSqRight.ReadFromFile("polygons/polygonSqRight.txt"));

	assert(polygonTriLeft.IsConvex());
	assert(polygonTriRight.IsConvex());
	assert(polygonSqLeft.IsConvex());
	assert(polygonSqRight.IsConvex());

	ConvexPolygon::Iterator iter1 = polygonTriLeft.IteratorBegin();
	ConvexPolygon::Iterator iter2 = polygonTriRight.IteratorBegin();
	ConvexPolygon::Iterator iter3 = polygonSqLeft.IteratorBegin();
	ConvexPolygon::Iterator iter4 = polygonSqRight.IteratorBegin();

	assert(polygonTriLeft.IsEqual(polygonTriRight));
	assert(polygonSqRight.IsEqual(polygonSqLeft));
	assert(!polygonTriLeft.IsEqual(polygonSqRight));
}

void Tester::TestIterators() const
{
	ConvexPolygon polygonSqLeft;

	assert(polygonSqLeft.ReadFromFile("polygons/polygonSqLeft.txt"));

	for (ConvexPolygon::Iterator iter = polygonSqLeft.IteratorBegin(); !iter.IsEnd(); iter.Next())
	{
		Point const& p = iter.Value();
	}
}

void Tester::TestMinkowskiSum() const
{
	ConvexPolygon polygonTriRight;
	ConvexPolygon polygonSqRight;

	assert(polygonTriRight.ReadFromFile("polygons/polygonTriRight.txt"));
	assert(polygonSqRight.ReadFromFile("polygons/polygonSqRight.txt"));
	
	assert(polygonTriRight.IsConvex());
	assert(polygonSqRight.IsConvex());

	ConvexPolygon polygon1 = ConvexPolygon::MinkowskiSum(polygonSqRight, polygonTriRight);
	ConvexPolygon polygon2 = ConvexPolygon::MinkowskiSum(polygonTriRight, polygonSqRight);
	
	assert(polygon1.IsEqual(polygon2));
	assert(polygon1.IsConvex());
	assert(polygon2.IsConvex());

	ConvexPolygon polygonTriLeft;
	ConvexPolygon polygonSqLeft;

	assert(polygonTriLeft.ReadFromFile("polygons/polygonTriLeft.txt"));
	assert(polygonSqLeft.ReadFromFile("polygons/polygonSqLeft.txt"));
	assert(polygonTriLeft.IsConvex());
	assert(polygonSqLeft.IsConvex());

	ConvexPolygon polygon3 = ConvexPolygon::MinkowskiSum(polygonSqLeft, polygonTriLeft);
	ConvexPolygon polygon4 = ConvexPolygon::MinkowskiSum(polygonTriLeft, polygonSqLeft);

	assert(polygon3.IsEqual(polygon4));
	assert(polygon4.IsEqual(polygon1));
	assert(polygon3.IsConvex());
	assert(polygon4.IsConvex());

	ConvexPolygon polygon5 = ConvexPolygon::MinkowskiSum(polygonSqLeft, polygonTriRight);
	ConvexPolygon polygon6 = ConvexPolygon::MinkowskiSum(polygonTriLeft, polygonSqRight);

	assert(polygon5.IsEqual(polygon6));
	assert(polygon6.IsEqual(polygon1));
	assert(polygon5.IsConvex());
	assert(polygon6.IsConvex());


	ConvexPolygon square1;
	ConvexPolygon square2;

	assert(square1.ReadFromFile("polygons/polygonSq2Left.txt"));
	assert(square2.ReadFromFile("polygons/polygonSq2Right.txt"));
	assert(square1.IsConvex());
	assert(square2.IsConvex());

	ConvexPolygon polygonSq1 = ConvexPolygon::MinkowskiSum(square1, square1);
	ConvexPolygon polygonSq2 = ConvexPolygon::MinkowskiSum(square2, square2);
	ConvexPolygon polygonSq3 = ConvexPolygon::MinkowskiSum(square1, square2);

	assert(polygonSq1.IsEqual(polygonSq2));
	assert(polygonSq2.IsEqual(polygonSq3));
	assert(polygonSq1.IsConvex());
	assert(polygonSq2.IsConvex());
	assert(polygonSq3.IsConvex());


	{
		ConvexPolygon triangle;
		ConvexPolygon square;

		assert(triangle.ReadFromFile("polygons/polygonTri.txt"));
		assert(square.ReadFromFile("polygons/polygonSq.txt"));
		assert(triangle.IsConvex());
		assert(square.IsConvex());

		ConvexPolygon res1 = ConvexPolygon::MinkowskiSum(triangle, square);
		ConvexPolygon res2 = ConvexPolygon::MinkowskiSum(square, triangle);

		assert(res1.IsEqual(res2));
		assert(res1.IsConvex());
		assert(res2.IsConvex());

		ConvexPolygon polygonSq5;

		assert(polygonSq5.ReadFromFile("polygons/polygon5.txt"));
		assert(polygonSq5.IsConvex());

		ConvexPolygon res3 = ConvexPolygon::MinkowskiSum(triangle, polygonSq5);
		ConvexPolygon res4 = ConvexPolygon::MinkowskiSum(polygonSq5, triangle);

		assert(res3.IsEqual(res4));
		assert(res3.IsConvex());
		assert(res4.IsConvex());
	}
}
