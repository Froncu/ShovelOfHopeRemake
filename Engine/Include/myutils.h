#pragma once

#include "utils.h"
#include <string>
#include <vector>
#include "Vector2f.h"

namespace myutils
{
	#pragma region DrawFunctions
	// Draws squares within squares based on the bottom left corner (position), (size) and the (amount) of squares.
	void DrawSquares(const Point2f& position, float size, int amount, float thickness);
	// Draws squares within squares based on the bottom left corner (position), (size) and the (amount) of squares.
	void DrawSquares(float positionX, float positionY, float size, int amount, float thickness);

	// Draws an equilateral triangle based on the bottom left corner (position), (size) of the sides amd the (color).
	void DrawEquilateralTriangle(const Point2f& position, float size);
	// Draws an equilateral triangle based on the bottom left corner (position), (size) of the sides amd the (color).
	void DrawEquilateralTriangle(float positionX, float positionY, float size);

	// Draws an equilateral triangle based on the bottom left corner (position), (size) of the sides amd the (color).
	void FillEquilateralTriangle(const Point2f& position, float size);
	// Draws an equilateral triangle based on the bottom left corner (position), (size) of the sides amd the (color).
	void FillEquilateralTriangle(float positionX, float positionY, float size);

	// Draws a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void DrawSierpinskiTriangle(const Point2f& left, const Point2f& top, const Point2f& right, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f), float thickness = 1.0f);
	// Draws a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void DrawSierpinskiTriangle(float leftX, float leftY, const Point2f& top, const Point2f& right, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f), float thickness = 1.0f);
	// Draws a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void DrawSierpinskiTriangle(const Point2f& left, float topX, float topY, const Point2f& right, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f), float thickness = 1.0f);
	// Draws a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void DrawSierpinskiTriangle(const Point2f& left, const Point2f& top, float rightX, float rightY, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f), float thickness = 1.0f);
	// Draws a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void DrawSierpinskiTriangle(float leftX, float leftY, float topX, float topY, const Point2f& right, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f), float thickness = 1.0f);
	// Draws a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void DrawSierpinskiTriangle(const Point2f& left, float topX, float topY, float rightX, float rightY, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f), float thickness = 1.0f);
	// Draws a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void DrawSierpinskiTriangle(float leftX, float leftY, float topX, float topY, float rightX, float rightY, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f), float thickness = 1.0f);
	
	// Fills a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void FillSierpinskiTriangle(const Point2f& left, const Point2f& top, const Point2f& right, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	// Fills a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void FillSierpinskiTriangle(float leftX, float leftY, const Point2f& top, const Point2f& right, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	// Fills a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void FillSierpinskiTriangle(const Point2f& left, float topX, float topY, const Point2f& right, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	// Fills a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void FillSierpinskiTriangle(const Point2f& left, const Point2f& top, float rightX, float rightY, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	// Fills a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void FillSierpinskiTriangle(float leftX, float leftY, float topX, float topY, const Point2f& right, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	// Fills a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void FillSierpinskiTriangle(const Point2f& left, float topX, float topY, float rightX, float rightY, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	// Fills a Sierpinski triangle based on three points (left, top, right) and the colors of the triangles (colorLeft, colorTop, colorRight).
	void FillSierpinskiTriangle(float leftX, float leftY, float topX, float topY, float rightX, float rightY, const Color4f& colorLeft = Color4f(1.0f, 0.0f, 0.0f, 1.0f), const Color4f& colorTop = Color4f(0.0f, 1.0f, 0.0f, 1.0f), const Color4f& colorRight = Color4f(0.0f, 0.0f, 1.0f, 1.0f));

	// Draws a xgram based on the amount of (points), the (position) of the center, the (radius), the (color) and the (startAngle) in radians.
	void DrawXgram(const Point2f& position, int points, float radius, float startAngle = 0.0f, float thickness = 1.0f);
	// Draws a xgram based on the amount of (points), the (position) of the center, the (radius), the (color) and the (startAngle) in radians.
	void DrawXgram(float positionX, float positionY, int points, float radius, float startAngle = 0.0f, float thickness = 1.0f);

	// Draws a (rectangle) filled with a linear gradient from the (leftColor) to the (rightColor).
	void DrawLinearGradient(const Rectf& rectangle, const Color4f& leftColor = Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }, const Color4f& rightColor = Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	// Draws a (rectangle) filled with a linear gradient from the (leftColor) to the (rightColor).
	void DrawLinearGradient(const Point2f& rectanglePosition, float rectangleWidth, float rectangleHeight, const Color4f& leftColor = Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }, const Color4f& rightColor = Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	// Draws a (rectangle) filled with a linear gradient from the (leftColor) to the (rightColor).
	void DrawLinearGradient(float rectanglePositionX, float rectanglePositionY, float rectangleWidth, float rectangleHeight, const Color4f& leftColor = Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }, const Color4f& rightColor = Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });

	// Draws a dot grid based on the bottom left corner (position), the amount of columns and rows (resolution), the radius of the dots (radius), the (color) and the (offset) between the dots.
	void DrawDotGrid(const Point2f& position, const Point2f& resolution, float radius, float offset = 0.0f);
	// Draws a dot grid based on the bottom left corner (position), the amount of columns and rows (resolution), the radius of the dots (radius), the (color) and the (offset) between the dots.
	void DrawDotGrid(float positionX, float positionY, const Point2f& resolution, float radius, float offset = 0.0f);
	// Draws a dot grid based on the bottom left corner (position), the amount of columns and rows (resolution), the radius of the dots (radius), the (color) and the (offset) between the dots.
	void DrawDotGrid(const Point2f& position, float resolutionX, float resolutionY, float radius, float offset = 0.0f);
	// Draws a dot grid based on the bottom left corner (position), the amount of columns and rows (resolution), the radius of the dots (radius), the (color) and the (offset) between the dots.
	void DrawDotGrid(float positionX, float positionY, float resolutionX, float resolutionY, float radius, float offset = 0.0f);
	#pragma endregion DrawFunctions



	#pragma region Calculators
	// Generates a random integer value in interval [min, max].
	int GetRandom(int maximalValue, int minimalValue = 0);
	// Generates a random single precision floating value in interval [min, max].
	float GetRandom(float maximalValue, float minimalValue = 0.0f);
	// Generates a random single precision floating value in interval [min, max].
	Vector2f GetRandom(const Vector2f& maximalValue, const Vector2f& minimalValue = Vector2f(0, 0));

	// Calculates and returns a distance between (p1) and (p2).
	float GetDistance(const Point2f& p1, const Point2f& p2);
	// Calculates and returns a distance between (p1) and (p2).
	float GetDistance(const Point2f& p1, float p2x, float p2y);
	// Calculates and returns a distance between (p1) and (p2).
	float GetDistance(float p1x, float p1y, const Point2f& p2);
	// Calculates and returns a distance between (p1) and (p2).
	float GetDistance(float p1x, float p1y, float p2x, float p2y);

	// Converts the angle from (degrees) to radians and returns it.
	float ToRadians(float degrees);
	// Converts the angle from (radians) to degrees and returns it.
	float ToDegrees(float radians);
	#pragma endregion Calculators
		


	#pragma region Arrays
	// Converts an array specified by it's address (pNumbers) and amount of elements (size) to a string of it's elements and returns it.
	std::string ToString(int* pNumbers, int size);

	// Randomizes all of the elements of an array specified by it's address (pNumbers) and amount of elements (size) in the interval [minimalValue, maximalValue].
	void Randomize(int* pNumbers, int size, int minimalValue, int maximalValue);
	// Randomizes the elements in interval [startingIndex, endingIndex] of an array specified by it's address (pNumbers) and amount of elements (size) in the interval [minimalValue, maximalValue].
	void Randomize(int* pNumbers, int startingIndex, int endingIndex, int minimalValue, int maximalValue);

	// Uses the (rowIndex), (columnIndex) and the (columnAmount) to calculate the index of an element in a 2D array and return it.
	int GetIndex(int rowIndex, int columnIndex, int columnAmount);

	// Counts and returns the amount of times a certain (value) occurs in an array specified by it's address (pNumbers) and amount of elements (size).
	int Count(int* pNumbers, int size, int value);

	// Finds and retunrs the minimal element in an array specified by it's address (pNumbers) and amount of elements (size).
	int MinElement(int* pNumbers, int size);

	// Finds and retunrs the maximal element in an array specified by it's address (pNumbers) and amount of elements (size).
	int MaxElement(int* pNumbers, int size);

	// Swaps the elements on (index1) and (index2) in an array specified by it's address (pNumbers).
	void Swap(int* pNumbers, int index1, int index2);

	// Swaps two random elements of an array specified by it's address (pNumbers) and amount of elements (size) a specified (amount) of times.
	void Shuffle(int* pNumbers, int size, int amount);

	// Sorts an array specified by it's address (pNumbers) and amount of elements (size) in order specified by the boolean (increasing).
	void BubbleSort(int* pNumbers, int size, bool increasing = true);
	#pragma endregion Arrays



	#pragma region CollisionFunctionality
	// Checks whether (circle1) and (circle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Circlef& circle1, const Circlef& circle2);
	// Checks whether (circle1) and (circle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& circle1Position, float circle1Radius, const Circlef& circle2);
	// Checks whether (circle1) and (circle2) are overlapping and returns a boolean.
	bool IsOverlapping(float circle1PositionX, float circle1PositionY, float circle1Radius, const Circlef& circle2);
	// Checks whether (circle1) and (circle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Circlef& circle1, const Point2f& circle2Position, float circle2Radius = 0.0f);
	// Checks whether (circle1) and (circle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Circlef& circle1, float circle2PositionX, float circle2PositionY, float circle2Radius = 0.0f);
	// Checks whether (circle1) and (circle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& circle1Position, float circle1Radius, const Point2f& circle2Position, float circle2Radius = 0.0f);
	// Checks whether (circle1) and (circle2) are overlapping and returns a boolean.
	bool IsOverlapping(float circle1PositionX, float circle1PositionY, float circle1Radius, const Point2f& circle2Position, float circle2Radius = 0.0f);
	// Checks whether (circle1) and (circle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& circle1Position, float circle1Radius, float circle2PositionX, float circle2PositionY, float circle2Radius = 0.0f);
	// Checks whether (circle1) and (circle2) are overlapping and returns a boolean.
	bool IsOverlapping(float circle1PositionX, float circle1PositionY, float circle1Radius, float circle2PositionX, float circle2PositionY, float circle2Radius = 0.0f);

	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Rectf& rectangle1, const Rectf& rectangle2);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Rectf& rectangle1, const Point2f& rectangle2Position, const Point2f& size);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Rectf& rectangle1, const Point2f& rectangle2Position, float width, float height);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Rectf& rectangle1, float rectangle2PositionX, float rectangle2PositionY, const Point2f& size);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Rectf& rectangle1, float rectangle2PositionX, float rectangle2PositionY, float rectangle2Width, float rectangle2Height);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, const Rectf& rectangle2);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& rectangle1Position, float rectangle1SizeX, float rectangle1SizeY, const Rectf& rectangle2);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, const Point2f& rectangle1Size, const Rectf& rectangle2);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, float rectangle1SizeX, float rectangle1SizeY, const Rectf& rectangle2);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, const Point2f& rectangle2Position, const Point2f& rectangle2Size);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, const Point2f& rectangle1Size, const Point2f& rectangle2Position, const Point2f& rectangle2Size);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& rectangle1Position, float rectangle1SizeX, float rectangle1SizeY, const Point2f& rectangle2Position, const Point2f& rectangle2Size);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, float rectangle2PositionX, float rectangle2PositionY, const Point2f& rectangle2Size);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, const Point2f& rectangle2Position, float rectangle2SizeX, float rectangle2SizeY);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, float rectangle1SizeX, float rectangle1SizeY, const Point2f& rectangle2Position, const Point2f& rectangle2Size);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& rectangle1Position, float rectangle1SizeX, float rectangle1SizeY, float rectangle2PositionX, float rectangle2PositionY, const Point2f& rectangle2Size);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, float rectangle2PositionX, float rectangle2PositionY, float rectangle2SizeX, float rectangle2SizeY);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, float rectangle1SizeX, float rectangle1SizeY, float rectangle2PositionX, float rectangle2PositionY, const Point2f& rectangle2Size);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(const Point2f& rectangle1Position, float rectangle1SizeX, float rectangle1SizeY, float rectangle2PositionX, float rectangle2PositionY, float rectangle2SizeX, float rectangle2SizeY);
	// Checks whether (rectangle1) and (rectangle2) are overlapping and returns a boolean.
	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, float rectangle1SizeX, float rectangle1SizeY, float rectangle2PositionX, float rectangle2PositionY, float rectangle2SizeX, float rectangle2SizeY);

	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(const Rectf& rectangle, const Circlef& circle);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(const Rectf& rectangle, const Point2f& circlePosition, float circleRadius = 0.0f);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(const Rectf& rectangle, float circlePositionX, float circlePositionY, float circleRadius = 0.0f);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(const Point2f& rectanglePosition, const Point2f& rectangleSize, const Circlef& circle);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(const Point2f& rectanglePosition, float rectangleSizeX, float rectangleSizeY, const Circlef& circle);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, const Point2f& rectangleSize, const Circlef& circle);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, float rectangleSizeX, float rectangleSizeY, const Circlef& circle);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(const Point2f& rectanglePosition, const Point2f& rectangleSize, const Point2f& circlePosition, float circleRadius = 0.0f);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(const Point2f& rectanglePosition, const Point2f& rectangleSize, float circlePositionX, float circlePositionY, float circleRadius = 0.0f);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(const Point2f& rectanglePosition, float rectangleSizeX, float rectangleSizeY, const Point2f& circlePosition, float circleRadius = 0.0f);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, const Point2f& rectangleSize, const Point2f& circlePosition, float circleRadius = 0.0f);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, float rectangleSizeX, float rectangleSizeY, const Point2f& circlePosition, float circleRadius = 0.0f);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(const Point2f& rectanglePosition, float rectangleSizeX, float rectangleSizeY, float circlePositionX, float circlePositionY, float circleRadius = 0.0f);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, const Point2f& rectangleSize, float circlePositionX, float circlePositionY, float circleRadius = 0.0f);
	// Checks whether (rectangle) and (circle) overlap and returns a boolean.
	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, float rectangleSizeX, float rectangleSizeY, float circlePositionX, float circlePositionY, float circleRadius = 0.0f);

	bool Raycast(const std::vector<std::vector<Point2f>>& vVertices, const Point2f& rayP1, const Point2f& rayP2, utils::HitInfo& hitInfo);
	#pragma endregion CollisionFunctionality



	#pragma region Vectors
	// Converts a (vector) to a string of it's x and y component and returns it.
	std::string ToString(const Vector2f& vector);
	// Converts a (vector) to a string of it's x and y component and returns it.
	std::string ToString(float vectorX, float vectorY);

	// Calculates and returns the dot product of (vector1) and (vector2).
	float DotProduct(const Vector2f& vector1, const Vector2f& vector2);
	// Calculates and returns the dot product of (vector1) and (vector2).
	float DotProduct(const Vector2f& vector1, float vector2X, float vector2Y);
	// Calculates and returns the dot product of (vector1) and (vector2).
	float DotProduct(float vector1X, float vector1Y, const Vector2f& vector2);
	// Calculates and returns the dot product of (vector1) and (vector2).
	float DotProduct(float vector1X, float vector1Y, float vector2X, float vector2Y);

	// Calculates and returns the cross product of (vector1) over (vector2).
	float CrossProduct(const Vector2f& vector1, const Vector2f& vector2);
	// Calculates and returns the cross product of (vector1) over (vector2).
	float CrossProduct(const Vector2f& vector1, float vector2X, float vector2Y);
	// Calculates and returns the cross product of (vector1) over (vector2).
	float CrossProduct(float vector1X, float vector1Y, const Vector2f& vector2);
	// Calculates and returns the cross product of (vector1) over (vector2).
	float CrossProduct(float vector1X, float vector1Y, float vector2X, float vector2Y);

	// Calculates and returns the length between (vector1) and (vector2).
	float Length(const Vector2f& vector1);
	// Calculates and returns the length between (vector1) and (vector2).
	float Length(float vector1X, float vector1Y);

	// Calculates and returns the angle between (vector1) and (vector2) in radians.
	float AngleBetween(const Vector2f& vector1, const Vector2f& vector2);
	// Calculates and returns the angle between (vector1) and (vector2) in radians.
	float AngleBetween(const Vector2f& vector1, float vector2X, float vector2Y);
	// Calculates and returns the angle between (vector1) and (vector2) in radians.
	float AngleBetween(float vector1X, float vector1Y, const Vector2f& vector2);
	// Calculates and returns the angle between (vector1) and (vector2) in radians.
	float AngleBetween(float vector1X, float vector1Y, float vector2X, float vector2Y);

	// Checks whether (vector1) and (vector2) are equal and returns a boolean.
	bool AreEqual(const Vector2f& vector1, const Vector2f& vector2);
	// Checks whether (vector1) and (vector2) are equal and returns a boolean.
	bool AreEqual(const Vector2f& vector1, float vector2X, float vector2Y);
	// Checks whether (vector1) and (vector2) are equal and returns a boolean.
	bool AreEqual(float vector1X, float vector1Y, const Vector2f& vector2);
	// Checks whether (vector1) and (vector2) are equal and returns a boolean.
	bool AreEqual(float vector1X, float vector1Y, float vector2X, float vector2Y);

	// Draws a (vector) from a specified (startingPosition).
	void DrawVector(const Vector2f& vector, const Point2f& startingPoint = Point2f(0.0f, 0.0f));
	// Draws a (vector) from a specified (startingPosition).
	void DrawVector(const Vector2f& vector, float startingPointX, float startingPointY);
	// Draws a (vector) from a specified (startingPosition).
	void DrawVector(float vectorX, float vectorY, const Point2f& startingPoint);
	// Draws a (vector) from a specified (startingPosition).
	void DrawVector(float vectorX, float vectorY, float startingPointX, float startingPointY);

	// Adds two vectors together and returns the resulting vector.
	Vector2f AddVectors(const Vector2f& vector1, const Vector2f& vector2);
	// Adds two vectors together and returns the resulting vector.
	Vector2f AddVectors(const Vector2f& vector1, float vector2X, float vector2Y);
	// Adds two vectors together and returns the resulting vector.
	Vector2f AddVectors(float vector1X, float vector1Y, const Vector2f& vector2);
	// Adds two vectors together and returns the resulting vector.
	Vector2f AddVectors(float vector1X, float vector1Y, float vector2X, float vector2Y);

	// Substracts (vector2) from (vector1) and returns the resulting vector.
	Vector2f SubstractVectors(const Vector2f& vector1, const Vector2f& vector2);
	// Substracts (vector2) from (vector1) and returns the resulting vector.
	Vector2f SubstractVectors(const Vector2f& vector1, const Vector2f& vector2);
	// Substracts (vector2) from (vector1) and returns the resulting vector.
	Vector2f SubstractVectors(float vector1X, float vector1Y, const Vector2f& vector2);
	// Substracts (vector2) from (vector1) and returns the resulting vector.
	Vector2f SubstractVectors(float vector1X, float vector1Y, float vector2X, float vector2Y);

	// Scales and returns the scaled (vector) based on the (scalar).
	Vector2f Scale(const Vector2f& vector, float scalar);
	// Scales and returns the scaled (vector) based on the (scalar).
	Vector2f Scale(float vectorX, float vectorY, float scalar);

	// Normalizes and returns a (vector).
	Vector2f Normalize(Vector2f vector);
	// Normalizes and returns a (vector).
	Vector2f Normalize(float vectorX, float vectorY);
	#pragma endregion Vectors
}