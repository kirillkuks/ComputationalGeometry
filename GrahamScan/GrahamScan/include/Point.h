#pragma once


class Point
{
private:
	using int64 = long long;

public:
	static int PointLocationToLine(Point const& p1, Point const& p2, Point const& q);

public:
	Point();
	Point(int x, int y);
	~Point();

	inline int X() const { return m_x; }
	inline int Y() const { return m_y; }

	Point operator+(Point const& other) const;
	Point operator-(Point const& other) const;

	bool operator==(Point const& other) const;
	bool operator!=(Point const& other) const;

private:
	int m_x;
	int m_y;
};
