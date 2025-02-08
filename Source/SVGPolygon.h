#pragma once

#include "GameObject.h"
#include "KinematicCollider.h"

class SVGPolygon final : public GameObject, public KinematicCollider
{
public:
	//	Other
	friend class SVGMap;

	//	Rule of 5
	virtual ~SVGPolygon() = default;

	SVGPolygon(const SVGPolygon& other) = default;
	SVGPolygon(SVGPolygon&& other) = default;
	SVGPolygon& operator=(const SVGPolygon& other) = default;
	SVGPolygon& operator=(SVGPolygon&& other) = default;

	//	Other special methods
	

	//	Methods
	

	//	Setters
	

	//	Getters


protected:
	SVGPolygon(const std::vector<Point2f>& vVertices);

private:
	const std::vector<Point2f> m_vVertices;
};