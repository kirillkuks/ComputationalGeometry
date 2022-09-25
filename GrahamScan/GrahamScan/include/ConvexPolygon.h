#pragma once

#include "NumberedPoint.h"

#include <vector>


class ConvexPolygon
{
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
		~Iterator();

		Iterator& Next();

		bool IsEnd() const;

		Point const& Value() const;
		size_t Index() const;

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
	ConvexPolygon();
	ConvexPolygon(std::vector<Point> const& vertices);
	~ConvexPolygon();

	Iterator IteratorBegin() const;

	bool WriteToFile(char const* sFileName) const;

	size_t VertexNum() const;

	void AddVertexToEnd(NumberedPoint const& newVertex);

	bool IsEqual(ConvexPolygon const& polygon) const;
	bool IsConvex() const;

private:
	std::vector<NumberedPoint> m_vertices;

	size_t m_bottomLeftVertexIndex;
	NumberedPoint m_bottomLeftVertex;
};
