#include "ConvexPolygon.h"

#include <iostream>
#include <fstream>


ConvexPolygon ConvexPolygon::MinkowskiSum(ConvexPolygon const& polygon1, ConvexPolygon const& polygon2)
{
	ConvexPolygon sumResult;

	ConvexPolygon::Iterator iter1 = polygon1.IteratorBegin();
	ConvexPolygon::Iterator iter2 = polygon2.IteratorBegin();

	while (!(iter1.IsEnd() && iter2.IsEnd()))
	{
		Point v_i = iter1.Value();
		Point w_i = iter2.Value();

		sumResult.AddVertexToEnd(v_i + w_i);

		ConvexPolygon::Iterator iter1Next = iter1.GetNext();
		ConvexPolygon::Iterator iter2Next = iter2.GetNext();
		
		int angleCompare;

		if (iter1.IsEnd())
		{
			angleCompare = 1;
		}
		else if (iter2.IsEnd())
		{
			angleCompare = -1;
		}
		else
		{
			angleCompare = Point::AngleBetweenVecAndOxCompare
			(
				iter1Next.Value() - v_i,
				iter2Next.Value() - w_i
			);
		}

		if (angleCompare == -1)
		{
			iter1 = iter1Next;
		}
		else if (angleCompare == 1)
		{
			iter2 = iter2Next;
		}
		else
		{
			iter1 = iter1Next;
			iter2 = iter2Next;
		}
	}

	return sumResult;
}


ConvexPolygon::ConvexPolygon()
	: m_bottomLeftVertexIndex(0)
	, m_bottomLeftVertex(0, 0)
{}

ConvexPolygon::ConvexPolygon(std::vector<Point> const& vertices)
	: m_bottomLeftVertexIndex(0)
	, m_bottomLeftVertex(0, 0)
{
	for (Point const& vertex : vertices)
	{
		AddVertexToEnd(vertex);
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

ConvexPolygon::Iterator::Iterator(ConvexPolygon::Iterator const& other)
	: m_pPolygon(other.m_pPolygon)
	, m_startIndex(other.m_startIndex)
	, m_curIndex(other.m_curIndex)
	, m_bypassOrder(other.m_bypassOrder)
	, m_isBypassOver(other.m_isBypassOver)
{}

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

ConvexPolygon::Iterator ConvexPolygon::Iterator::GetNext() const
{
	Iterator iter(*this);
	return iter.Next();
}

bool ConvexPolygon::Iterator::IsEnd() const
{
	return m_isBypassOver;
}

Point const& ConvexPolygon::Iterator::Value() const
{
	return m_pPolygon->m_vertices[m_curIndex];
}

void ConvexPolygon::Iterator::DefineBypassOrder()
{
	int i = 0;
	int pointLocation = 0;

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

bool ConvexPolygon::ReadFromFile(char const* sFileName)
{
	std::ifstream iStream;
	iStream.open(sFileName);

	if (!iStream.is_open())
	{
		return false;
	}

	m_vertices.clear();

	size_t verticesNum;
	iStream >> verticesNum;

	if (verticesNum < 1)
	{
		return false;
	}

	for (size_t i = 0; i < verticesNum; ++i)
	{
		int x_i;
		int y_i;
		iStream >> x_i >> y_i;

		AddVertexToEnd(Point(x_i, y_i));
	}

	iStream.close();
	return true;
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

	for (ConvexPolygon::Iterator iter = IteratorBegin(); !iter.IsEnd(); iter.Next())
	{
		Point vertex = iter.Value();
		oStream << vertex.X() << " " << vertex.Y() << std::endl;
	}

	oStream.close();
	return true;
}

void ConvexPolygon::AddVertexToEnd(Point const& vertex)
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

size_t ConvexPolygon::VertexNum() const
{
	return m_vertices.size();
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
