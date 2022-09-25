#include "Set.h"

#include "Stack.h"
#include "NumberedPoint.h"

#include <fstream>
#include <iostream>


Set::Set()
{}

Set::~Set()
{}


ConvexPolygon Set::ConvexHull()
{
	if (Size() < 3)
	{
		return TrivialConvexHull();
	}

	SortPointsByX();
	return GrahamScan();
}

size_t Set::Size() const
{
	return m_points.size();
}

bool Set::ReadFromFile(char const* sFileName)
{
	std::ifstream iStream;
	iStream.open(sFileName);

	if (!iStream.is_open())
	{
		return false;
	}

	size_t pointsNum;
	iStream >> pointsNum;

	m_points.resize(pointsNum);

	for (size_t i = 0; i < pointsNum; ++i)
	{
		int x_i;
		int y_i;

		iStream >> x_i >> y_i;

		m_points[i] = NumberedPoint(x_i, y_i, i);
	}

	return true;
}


void Set::SortPointsByX()
{
	auto compare = [](void const* pPoint1, void const* pPoint2) -> int
	{
		Point* p1 = (Point*)pPoint1;
		Point* p2 = (Point*)pPoint2;

		if (p1->X() == p2->X())
		{
			if (p1->Y() == p2->Y())
			{
				return 0;
			}

			return p1->Y() > p2->Y() ? 1 : -1;
		}

		return p1->X() > p2->X() ? 1 : -1;
	};

	std::qsort(m_points.data(), m_points.size(), sizeof(NumberedPoint), compare);
}

ConvexPolygon Set::GrahamScan() const
{
	ConvexPolygon convexHull;

	Stack<NumberedPoint> stack;
	size_t pointsNum = m_points.size();

	auto verticesProcess = [&stack](NumberedPoint const& q)
	{
		int angleCompare = 0;

		do
		{
			Point const& p1 = stack.TopSecond();
			Point const& p2 = stack.Top();

			angleCompare = Point::PointLocationToLine(p1, p2, q);

			if (angleCompare <= 0)
			{
				stack.Pop();
			}

		} while (angleCompare <= 0 && stack.Size() > 1);

		stack.Push(q);
	};

	auto fillConvexHull = [&stack, &convexHull]()
	{
		stack.Pop();

		while (!stack.IsEmpty())
		{
			convexHull.AddVertexToEnd(stack.Pop());
		}
	};

	{
		stack.Push(m_points[0]);
		stack.Push(m_points[1]);

		for (int i = 2; i < pointsNum; ++i)
		{
			verticesProcess(m_points[i]);
		}

		fillConvexHull();
	}

	{
		stack.Push(m_points[pointsNum - 1]);
		stack.Push(m_points[pointsNum - 2]);

		for (int i = (int)pointsNum - 3; i >= 0; --i)
		{
			verticesProcess(m_points[i]);
		}

		fillConvexHull();
	}

	return convexHull;
}

ConvexPolygon Set::TrivialConvexHull() const
{
	ConvexPolygon convexHull;

	for (size_t i = 0; i < m_points.size(); ++i)
	{
		convexHull.AddVertexToEnd({ m_points[i], i});
	}

	return convexHull;
}
