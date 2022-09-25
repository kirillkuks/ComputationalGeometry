#include "Tester.h"

#include "Set.h"

#include <cassert>


Tester::Tester()
{}

Tester::~Tester()
{}


void Tester::TestSetRead() const
{
	Set set1;
	Set set2;

	assert(set1.ReadFromFile("sets/triangle.txt"));
	assert(set2.ReadFromFile("sets/triangleFull.txt"));

	assert(set1.Size() == 3);
	assert(set2.Size() == 8);
}

void Tester::TestGrahamScan() const
{
	{
		Set set;

		assert(set.ReadFromFile("sets/triangle.txt"));

		ConvexPolygon convexHull = set.ConvexHull();

		assert(convexHull.IsConvex());
		assert(convexHull.IsEqual(ConvexPolygon({ {-1, -1}, {0, 1}, {1, -1} })));
	}
	{
		Set set;

		assert(set.ReadFromFile("sets/triangleFull.txt"));

		ConvexPolygon convexHull = set.ConvexHull();

		assert(convexHull.IsConvex());
		assert(convexHull.IsEqual(ConvexPolygon({ {-2, -2}, {2, -2}, {0, 2} })));
	}
	{
		Set set;

		assert(set.ReadFromFile("sets/vertexBig.txt"));

		ConvexPolygon convexHull = set.ConvexHull();

		assert(convexHull.IsConvex());
		assert(convexHull.IsEqual(ConvexPolygon({ {-4, -6}, {2, -5}, {8, 1}, {4, 5}, {-999999999, 1} })));
	}
	{
		Set set;

		assert(set.ReadFromFile("sets/circuit.txt"));

		ConvexPolygon convexHull = set.ConvexHull();

		assert(convexHull.IsConvex());
		assert(convexHull.IsEqual(ConvexPolygon({ {-100, -100}, {100, -100}, {100, 100}, {-100, 100} })));
	}
	{
		Set set;

		assert(set.ReadFromFile("sets/set1.txt"));

		ConvexPolygon convexHull = set.ConvexHull();

		assert(convexHull.IsConvex());
		assert(convexHull.IsEqual(ConvexPolygon({ {-1, -6}, {2, -5}, {7, 4}, {-2, 4}, {-8, 2} })));
	}
	{
		Set set;

		assert(set.ReadFromFile("sets/set2.txt"));

		ConvexPolygon convexHull = set.ConvexHull();

		assert(convexHull.IsConvex());
		assert(convexHull.IsEqual(ConvexPolygon({ {-1, -6}, {2, -5}, {7, 4}, {-1, 8}, {-8, 2} })));
	}
}
