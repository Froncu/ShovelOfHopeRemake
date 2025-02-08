#pragma once

#include "GameObject.h"
#include "HitBox.h"

class SVGDeathZone final : public GameObject, public HitBox
{
public:
	//	Other


	//	Rule of 5
	~SVGDeathZone() = default;

	SVGDeathZone(const SVGDeathZone& other) = delete;
	SVGDeathZone(SVGDeathZone&& other) = delete;
	SVGDeathZone& operator=(const SVGDeathZone& other) = delete;
	SVGDeathZone& operator=(SVGDeathZone&& other) = delete;

	//	Other special methods
	SVGDeathZone(const std::string& SVGPath);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:

};