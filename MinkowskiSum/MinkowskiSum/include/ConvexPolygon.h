#pragma once
#include <vector>

#include "Point.h"


class ConvexPolygon
{
public:
	class Iterator
	{
	public:
		enum class BypassOrder : int
		{
			Clockwise = -1,
			CounterClockwise = 1
		};

	public:
		Iterator(ConvexPolygon const* pPolygon);
		Iterator(Iterator const& other);
		~Iterator();

		Iterator& Next();
		Iterator GetNext() const;

		bool IsEnd() const;
		Point const& Value() const;

		BypassOrder Bypass() const;

	private:
		void DefineBypassOrder();

	private:
		ConvexPolygon const* m_pPolygon;
		size_t m_startIndex;
		size_t m_curIndex;

		BypassOrder m_bypassOrder;
		bool m_isBypassOver;
	};

public:
	static ConvexPolygon MinkowskiSum(ConvexPolygon const& polygon1, ConvexPolygon const& polygon2);

public:
	ConvexPolygon();
	ConvexPolygon(std::vector<Point> const& vertices);
	~ConvexPolygon();

	Iterator IteratorBegin() const;

	bool ReadFromFile(char const* sFileName);
	bool WriteToFile(char const* sFileName) const;

	size_t VertexNum() const;

	bool IsEqual(ConvexPolygon const& polygon) const;
	bool IsConvex() const;

private:
	void AddVertexToEnd(Point const& newVertex);

private:
	std::vector<Point> m_vertices;

	size_t m_bottomLeftVertexIndex;
	Point m_bottomLeftVertex;
};
