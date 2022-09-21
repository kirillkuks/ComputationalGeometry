#include "Point.h"

#include <cmath>


int Point::AngleBetweenVecAndOxCompare(Point const& point1, Point const& point2)
{
	if (point1.m_y >= 0 && point2.m_y < 0)
	{
		return -1;
	}
	else if (point1.m_y < 0 && point2.m_y >= 0)
	{
		return 1;
	}

	if ((point1.m_y >= 0 && point2.m_y >= 0)
		|| (point1.m_y <= 0 && point2.m_y <= 0))
	{
		if (point1.m_y + point2.m_y == 0)
		{
			if ((point1.m_x > 0 && point2.m_x > 0)
				|| (point1.m_x < 0 && point2.m_x < 0))
			{
				return 0;
			}
			else
			{
				return point1.m_x < 0 ? 1 : -1;
			}
		}

		int64 first = (int64)point2.m_x * point1.m_y;
		int64 second = (int64)point1.m_x * point2.m_y;
		int64 det = first - second;

		if (det > 0)
		{
			return 1;
		}
		else if (det < 0)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return point1.m_y < 0 ? 1 : -1;
	}
}

int Point::PointLocationToLine(Point const& p1, Point const& p2, Point const& q)
{
	int64 pos = (int64)q.X() * ((int64)p1.Y() - p2.Y()) 
		- (int64)q.Y() * ((int64)p1.X() - p2.X()) 
		+ ((int64)p1.X() * p2.Y() - (int64)p2.X() * p1.Y());

	return (int)(pos == 0 ? 0 : pos / abs(pos));
}



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
