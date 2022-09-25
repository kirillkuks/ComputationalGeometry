#include "ConvexPolygon.h"

#include <fstream>


ConvexPolygon::ConvexPolygon()
	: m_bottomLeftVertexIndex(0)
	, m_bottomLeftVertex(0, 0, 0)
{}

ConvexPolygon::ConvexPolygon(std::vector<Point> const& points)
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		AddVertexToEnd({ points[i], i });
	}
}

ConvexPolygon::~ConvexPolygon()
{}


ConvexPolygon::Iterator::Iterator(ConvexPolygon const* pPolygon)
	: m_pPolygon(pPolygon)
	, m_startIndex(pPolygon->m_bottomLeftVertexIndex)
	, m_curIndex(pPolygon->m_bottomLeftVertexIndex)
	, m_bypassOrder(BypassOrder::CounterClockwise)
	, m_isBypassOver(false)
{
	DefineBypassOrder();
}

ConvexPolygon::Iterator::~Iterator()
{}

ConvexPolygon::Iterator& ConvexPolygon::Iterator::Next()
{
	if (m_bypassOrder == BypassOrder::CounterClockwise)
	{
		m_curIndex = (m_curIndex + 1) % m_pPolygon->VertexNum();
	}
	else
	{
		m_curIndex = m_curIndex == 0 ? m_pPolygon->VertexNum() - 1 : m_curIndex - 1;
	}

	if (m_curIndex == m_startIndex)
	{
		m_isBypassOver = true;
	}

	return *this;
}

bool ConvexPolygon::Iterator::IsEnd() const
{
	return m_isBypassOver;
}

Point const& ConvexPolygon::Iterator::Value() const
{
	return m_pPolygon->m_vertices[m_curIndex];
}

size_t ConvexPolygon::Iterator::Index()const
{
	return m_pPolygon->m_vertices[m_curIndex].GetIndex();
}

void ConvexPolygon::Iterator::DefineBypassOrder()
{
	int i = 0;
	int pointLocation = 0;

	if (m_pPolygon->VertexNum() < 3)
	{
		m_bypassOrder = BypassOrder::CounterClockwise;
		return;
	}

	do
	{
		int p1 = i < 1 ? (int)m_pPolygon->VertexNum() - 1 : i - 1;
		int p2 = i;
		int q = (i + 1) % (int)m_pPolygon->VertexNum();

		pointLocation = Point::PointLocationToLine
		(
			m_pPolygon->m_vertices[p1],
			m_pPolygon->m_vertices[p2],
			m_pPolygon->m_vertices[q]
		);

		i = q;
	} while (pointLocation == 0);

	m_bypassOrder = pointLocation == 1 ? BypassOrder::CounterClockwise : BypassOrder::Clockwise;
}

ConvexPolygon::Iterator::BypassOrder ConvexPolygon::Iterator::Bypass() const
{
	return m_bypassOrder;
}


ConvexPolygon::Iterator ConvexPolygon::IteratorBegin() const
{
	return Iterator(this);
}


bool ConvexPolygon::WriteToFile(char const* sFileName) const
{
	std::ofstream oStream;
	oStream.open(sFileName);

	if (!oStream.is_open())
	{
		return false;
	}

	oStream << VertexNum() << std::endl;

	for (Iterator iter = IteratorBegin(); !iter.IsEnd(); iter.Next())
	{
		oStream << iter.Index() << std::endl;
	}

	return true;
}


size_t ConvexPolygon::VertexNum() const
{
	return m_vertices.size();
}


void ConvexPolygon::AddVertexToEnd(NumberedPoint const& vertex)
{
	if (VertexNum() == 0)
	{
		m_bottomLeftVertex = vertex;
		m_bottomLeftVertexIndex = 0;
	}
	else
	{
		if (vertex.Y() < m_bottomLeftVertex.Y())
		{
			m_bottomLeftVertexIndex = VertexNum();
			m_bottomLeftVertex = vertex;
		}
		else if (vertex.Y() == m_bottomLeftVertex.Y())
		{
			if (vertex.X() < m_bottomLeftVertex.X())
			{
				m_bottomLeftVertexIndex = VertexNum();
				m_bottomLeftVertex = vertex;
			}
		}
	}

	m_vertices.push_back(vertex);
}


bool ConvexPolygon::IsEqual(ConvexPolygon const& polygon) const
{
	ConvexPolygon::Iterator iter1 = IteratorBegin();
	ConvexPolygon::Iterator iter2 = polygon.IteratorBegin();

	for (; !iter1.IsEnd() && !iter2.IsEnd(); iter1.Next(), iter2.Next())
	{
		if (iter1.Value() != iter2.Value())
		{
			return false;
		}
	}

	return iter1.IsEnd() && iter2.IsEnd();
}

bool ConvexPolygon::IsConvex() const
{
	if (VertexNum() < 3)
	{
		return true;
	}

	Iterator iterator = IteratorBegin();

	for (size_t i = 0; i < VertexNum(); ++i)
	{
		int loc = Point::PointLocationToLine
		(
			m_vertices[i == 0 ? VertexNum() - 1 : i - 1],
			m_vertices[i],
			m_vertices[(i + 1) % VertexNum()]
		);

		if (iterator.Bypass() == Iterator::BypassOrder::CounterClockwise)
		{
			if (loc < 0)
			{
				return false;
			}
		}
		else
		{
			if (loc > 0)
			{
				return false;
			}
		}

	}

	return true;
}
