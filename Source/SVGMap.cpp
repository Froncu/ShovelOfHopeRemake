#include "pch.h"
#include "SVGMap.h"

#include "SVGParser.h"
#include "SVGPolygon.h"

#include "utils.h"

#pragma region Constructors/Destructor
SVGMap::SVGMap(const std::string& SVGPath) :
	GameObject(),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Resources/Level/Textures/Ground.png", 10)
{
	std::vector<std::vector<Point2f>> vvVertices;

	SVGParser::GetVerticesFromSvgFile(SVGPath, vvVertices);

	for (const std::vector<Point2f>&vVertices: vvVertices)
	{
		GameObject::AddGameObject(new SVGPolygon{ vVertices });
	}

	m_RootCenter.x = SimpleSprite::GetSourceRectangle().width / 2;
	m_RootCenter.y = SimpleSprite::GetSourceRectangle().height / 2;
}
#pragma endregion Constructors/Destructor