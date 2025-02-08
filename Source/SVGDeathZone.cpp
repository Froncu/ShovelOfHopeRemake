#include "pch.h"
#include "SVGDeathZone.h"

#include "SVGParser.h"

#pragma region Constructors/Desstructor
SVGDeathZone::SVGDeathZone(const std::string& SVGPath)	:
	GameObject(),
	HitBox(m_RootCenter)
{
	std::vector<std::vector<Point2f>> vvVertices{};
	SVGParser::GetVerticesFromSvgFile(SVGPath, vvVertices);

	Point2f bottomLeft{ INFINITY, INFINITY }, topRight{ -INFINITY, -INFINITY };
	for (const std::vector<Point2f> vVertices : vvVertices)
	{
		for (const Point2f vertex : vVertices)
		{
			if (vertex.x < bottomLeft.x) bottomLeft.x = vertex.x;
			if (vertex.y < bottomLeft.y) bottomLeft.y = vertex.y;

			if (vertex.x > topRight.x) topRight.x = vertex.x;
			if (vertex.y > topRight.y) topRight.y = vertex.y;
		}
	}

	m_RootCenter.x = bottomLeft.x + (topRight.x - bottomLeft.x) / 2;
	m_RootCenter.y = bottomLeft.y + (topRight.y - bottomLeft.y) / 2;

	for (const std::vector<Point2f> vVertices : vvVertices)
	{
		Point2f localBottomLeft{ INFINITY, INFINITY }, localTopRight{ -INFINITY, -INFINITY };
		for (const Point2f& vertex : vVertices)
		{
			if (vertex.x < localBottomLeft.x) localBottomLeft.x = vertex.x;
			if (vertex.y < localBottomLeft.y) localBottomLeft.y = vertex.y;

			if (vertex.x > localTopRight.x) localTopRight.x = vertex.x;
			if (vertex.y > localTopRight.y) localTopRight.y = vertex.y;
		}

		HitBox::AddLocalHitBox((localBottomLeft.x + (localTopRight.x - localBottomLeft.x) / 2) - m_RootCenter.x, (localBottomLeft.y + (localTopRight.y - localBottomLeft.y) / 2) - m_RootCenter.y, localTopRight.x - localBottomLeft.x, localTopRight.y - localBottomLeft.y);
	}

	HitBox::AddGroupNumber(5);
	HitBox::SetDamage(999);
}
#pragma endregion Constructors/Desstructor