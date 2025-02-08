#include "pch.h"
#include "SVGPolygon.h"

#pragma region Constructors/Destructor
SVGPolygon::SVGPolygon(const std::vector<Point2f>& vVertices) :
	GameObject(),
	KinematicCollider(m_vVertices),

	m_vVertices{ vVertices }
{
}
#pragma endregion Constructors/Destructor