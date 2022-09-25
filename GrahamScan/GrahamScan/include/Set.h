#pragma once

#include "ConvexPolygon.h"
#include "NumberedPoint.h"

#include <vector>


class Set
{
public:
	struct PointInfo
	{
		Point m_point;
		size_t m_index;
	};

public:
	Set();
	~Set();

	ConvexPolygon ConvexHull();

	size_t Size() const;

	bool ReadFromFile(char const* sFileName);

private:
	void SortPointsByX();
	ConvexPolygon GrahamScan() const;

	ConvexPolygon TrivialConvexHull() const;

private:
	std::vector<NumberedPoint> m_points;
};
