#include "Point.h"

#include <cmath>


int Point::PointLocationToLine(Point const& p1, Point const& p2, Point const& q)
{
	int64 pos = (int64)q.X() * ((int64)p1.Y() - p2.Y())
		- (int64)q.Y() * ((int64)p1.X() - p2.X())
		+ ((int64)p1.X() * p2.Y() - (int64)p2.X() * p1.Y());

	return (int)(pos == 0 ? 0 : pos / abs(pos));
}


Point::Point()
	: m_x(0)
	, m_y(0)
{}

Point::Point(int x, int y)
	: m_x(x)
	, m_y(y)
{}

Point::~Point()
{}


Point Point::operator+(Point const& other) const
{
	return Point(m_x + other.m_x, m_y + other.m_y);
}

Point Point::operator-(Point const& other) const
{
	return Point(m_x - other.m_x, m_y - other.m_y);
}

bool Point::operator==(Point const& other) const
{
	return m_x == other.m_x && m_y == other.m_y;
}

bool Point::operator!=(Point const& other) const
{
	return !(*this == other);
}
