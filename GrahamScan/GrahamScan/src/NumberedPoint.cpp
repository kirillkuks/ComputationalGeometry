#include "NumberedPoint.h"


NumberedPoint::NumberedPoint()
	: m_index(0)
{}

NumberedPoint::NumberedPoint(int x, int y, size_t index)
	: Point(x, y)
	, m_index(index)
{}

NumberedPoint::NumberedPoint(Point const& point, size_t index)
	: Point(point)
	, m_index(index)
{}

NumberedPoint::~NumberedPoint()
{}


size_t NumberedPoint::GetIndex() const
{
	return m_index;
}
