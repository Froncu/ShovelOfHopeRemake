#include "base.h"
#include "structs.h"

//-----------------------------------------------------------------
// Window Constructors
//-----------------------------------------------------------------
Window::Window( const std::string& title , float width , float height , bool isVSyncOn )
	:title{ title }
	,width{ width }
	,height{ height }
	,isVSyncOn{ isVSyncOn }
{
}

//-----------------------------------------------------------------
// Point2i Constructors
//-----------------------------------------------------------------
Point2i::Point2i()
	:Point2i{ 0, 0 }
{
}
Point2i::Point2i(int x, int y)
	:x{ x }, y{ y }
{
}

//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
Point2f::Point2f( )
	:Point2f{ 0.0f, 0.0f }
{
}
Point2f::Point2f( float x, float y )
	:x{ x }, y{ y }
{
}

bool Point2f::operator==(const Point2f& right) const
{
	if (this->x == right.x
		&&
		this->y == right.y)
		return true;

	return false;
}

bool Point2f::operator!=(const Point2f& right) const
{
	if (*this == right) return false;

	return true;
}

//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
Point2d::Point2d( )
	:Point2d{ 0, 0 }
{
}
Point2d::Point2d( double x, double y)
	:x{ x }, y{ y }
{
}

//-----------------------------------------------------------------
// Vector3f Constructors
//-----------------------------------------------------------------
Vector3f::Vector3f()
	:Vector3f{ 0.0f, 0.0f, 0.0f }
{
}
Vector3f::Vector3f(float x, float y, float z)
	:x{ x }, y{ y }, z{ z }
{
}

//-----------------------------------------------------------------
// Body Constructors
//-----------------------------------------------------------------
Body::Body()
	:Body{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Body::Body(float left, float bottom, float width, float height)
	:bottomLeft{Point2f(left, bottom) }
	,width{ width }
	,height{ height }
{
}

Body::Body(const Point2f& bottomLeft, float width, float height)
	:Body(bottomLeft.x, bottomLeft.y, width, height)
{
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf( )
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Rectf::Rectf( float left, float bottom, float width, float height )
	:left{ left }
	,bottom{ bottom }
	,width{ width }
	,height{ height }
{
}

Rectf::Rectf( const Body& body )
	:left{ body.bottomLeft.x }
	,bottom{ body.bottomLeft.y }
	,width{ body.width }
	,height{ body.height }
{
}

bool Rectf::operator==(const Rectf& right) const
{
	if (this->left == right.left
		&&
		this->bottom == right.bottom
		&&
		this->width == right.width
		&&
		this->height == right.height)
		return true;

	return false;
}

//-----------------------------------------------------------------
// Color4f Constructors
//-----------------------------------------------------------------
Color4f::Color4f( )
	:Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }
{
}

Color4f::Color4f( float r, float g, float b, float a )
	:r{ r }
	,g{ g }
	,b{ b }
	,a{ a }
{
}

//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
Circlef::Circlef( )
	:Circlef{ 0.0f, 0.0f, 0.0f }
{
}

Circlef::Circlef( float centerX, float centerY, float radius )
	:Circlef{ Point2f{ centerX, centerY }, radius }
{
}

Circlef::Circlef( const Point2f& center, float radius )
	:center{ center }
	,radius{ radius }
{
}

//-----------------------------------------------------------------
// Ellipsef Constructors
//-----------------------------------------------------------------
Ellipsef::Ellipsef( )
	:Ellipsef{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Ellipsef::Ellipsef( const Point2f& center, float radiusX, float radiusY )
	: center{ center }
	, radiusX{ radiusX }
	, radiusY{ radiusY }
{
}

Ellipsef::Ellipsef( float centerX, float centerY, float radiusX, float radiusY )
	: Ellipsef{ Point2f{ centerX, centerY }, radiusX, radiusY }
{
}