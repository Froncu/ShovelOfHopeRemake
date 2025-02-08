#pragma once

#include "GameObject.h"
#include "KinematicCollider.h"
#include "SimpleSprite.h"

class SVGMap final : public GameObject, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	virtual ~SVGMap() = default;

	SVGMap(const SVGMap& other) = delete;
	SVGMap(SVGMap&& other) = delete;
	SVGMap& operator=(const SVGMap& other) = delete;
	SVGMap& operator=(SVGMap&& other) = delete;

	//	Other special methods
	SVGMap(const std::string& SVGPath);

	//	Methods


	//	Setters


	//	Getters


protected:


private:

};