#pragma once

#include "Point.h"


class NumberedPoint : public Point
{
public:
	NumberedPoint();
	NumberedPoint(int x, int y, size_t index);
	NumberedPoint(Point const& point, size_t index);
	~NumberedPoint();

	size_t GetIndex() const;

private:
	size_t m_index;

};
