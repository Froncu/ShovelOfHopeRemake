#pragma once
#include <string>

struct Window
{
	explicit Window( const std::string& title = "Title", float width = 320.0f, 
		float height = 180.0f, bool isVSyncOn = false );

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Point2i
{
	Point2i();
	explicit Point2i(int x, int y);

	int x;
	int y;
};

struct Point2f
{
	Point2f( );
	explicit Point2f( float x, float y );

	bool operator==(const Point2f& right) const;
	bool operator!=(const Point2f& right) const;

	float x;
	float y;
};

struct Point2d
{
	Point2d( );
	explicit Point2d( double x, double y );

	double x;
	double y;
};

struct Vector3f
{
	Vector3f();
	explicit Vector3f(float x, float y, float z);

	float x;
	float y;
	float z;
};

struct Body
{
	Body();
	explicit Body(const Point2f& bottomLeft, float width, float height);
	explicit Body(float left, float bottom, float width, float height);

	Point2f bottomLeft;
	float width;
	float height;
};

struct Rectf
{
	Rectf( );
	explicit Rectf( float left, float bottom, float width, float height );
	explicit Rectf( const Body& body );

	bool operator==(const Rectf& right) const;
	
	float left;
	float bottom;
	float width;
	float height;

};

struct Color4f
{
	Color4f( );
	explicit Color4f( float r, float g, float b, float a );
	
	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Circlef( );
	explicit Circlef( const Point2f& center, float radius );
	explicit Circlef( float centerX, float centerY, float radius );

	Point2f center;
	float radius;
};

struct Ellipsef
{
	Ellipsef( );
	explicit Ellipsef( const Point2f& center, float radiusX, float radiusY );
	explicit Ellipsef( float centerX, float centerY, float radiusX, float radiusY );

	Point2f center;
	float radiusX;
	float radiusY;
};