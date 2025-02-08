// Fratczak, Jakub - 1DAE11

#include "base.h"
#include "myutils.h"

namespace myutils
{
	#pragma region DrawFunctions
	void DrawSquares(const Point2f& position, float size, int amount, float thickness)
	{
		const float deltaSize = size / amount, halfDeltaSize = deltaSize / 2;

		for (int i{}; i < amount; ++i)
		{
			utils::DrawRect(position.x + i * halfDeltaSize, position.y + i * halfDeltaSize, size - deltaSize * i, size - deltaSize * i, thickness);
		}
	}

	void DrawSquares(float positionX, float positionY, float size, int amount, float thickness)
	{
		DrawSquares(Point2f{ positionX, positionY }, size, amount, thickness);
	}

	void DrawEquilateralTriangle(const Point2f& position, float size)
	{
		const Point2f bottomRight{ position.x + size, position.y };
		const Point2f apex{ position.x + size / 2, position.y + sqrtf(powf(size, 2) - powf(size / 2, 2)) };

		utils::DrawTriangle(position, bottomRight, apex);
	}

	void DrawEquilateralTriangle(float positionX, float positionY, float size)
	{
		DrawEquilateralTriangle(Point2f{ positionX, positionY }, size);
	}

	void FillEquilateralTriangle(const Point2f& position, float size)
	{
		const Point2f bottomRight{ position.x + size, position.y };
		const Point2f apex{ position.x + size / 2, position.y + sqrtf(powf(size, 2) - powf(size / 2, 2)) };

		utils::FillTriangle(position, bottomRight, apex);
	}

	void FillEquilateralTriangle(float positionX, float positionY, float size)
	{
		FillEquilateralTriangle(Point2f{ positionX, positionY }, size);
	}

	void DrawSierpinskiTriangle(const Point2f& left, const Point2f& top, const Point2f& right, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight, float thickness)
	{
		const Point2f 
			leftMiddle{ left.x + (top.x - left.x) / 2 , left.y + (top.y - left.y) / 2 },
			middleBottom{ left.x + (right.x - left.x) / 2 , left.y + (right.y - left.y) / 2 },
			rightMiddle{ right.x - (right.x - top.x) / 2 , right.y + (top.y - right.y) / 2 };

		utils::SetColor(colorLeft);
		utils::DrawTriangle(left, leftMiddle, middleBottom, thickness);

		utils::SetColor(colorTop);
		utils::DrawTriangle(leftMiddle, top, rightMiddle, thickness);

		utils::SetColor(colorRight);
		utils::DrawTriangle(middleBottom, rightMiddle, right, thickness);

		if (GetDistance(middleBottom, top) * GetDistance(right, left) / 2 < 1000.0f)
			return;

		DrawSierpinskiTriangle(left, leftMiddle, middleBottom, colorLeft, colorTop, colorRight, thickness);
		DrawSierpinskiTriangle(leftMiddle, top, rightMiddle, colorLeft, colorTop, colorRight, thickness);
		DrawSierpinskiTriangle(middleBottom, rightMiddle, right, colorLeft, colorTop, colorRight, thickness);
	}

	void DrawSierpinskiTriangle(float leftX, float leftY, const Point2f& top, const Point2f& right, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight, float thickness)
	{
		DrawSierpinskiTriangle(Point2f(leftX, leftY), top, right, colorLeft, colorTop, colorRight, thickness);
	}

	void DrawSierpinskiTriangle(const Point2f& left, float topX, float topY, const Point2f& right, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight, float thickness)
	{
		DrawSierpinskiTriangle(left, Point2f(topX, topY), right, colorLeft, colorTop, colorRight, thickness);
	}

	void DrawSierpinskiTriangle(const Point2f& left, const Point2f& top, float rightX, float rightY, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight, float thickness)
	{
		DrawSierpinskiTriangle(left, top, Point2f(rightX, rightY), colorLeft, colorTop, colorRight, thickness);
	}

	void DrawSierpinskiTriangle(float leftX, float leftY, float topX, float topY, const Point2f& right, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight, float thickness)
	{
		DrawSierpinskiTriangle(Point2f(leftX, leftY), Point2f(topX, topY), right, colorLeft, colorTop, colorRight, thickness);
	}

	void DrawSierpinskiTriangle(const Point2f& left, float topX, float topY, float rightX, float rightY, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight, float thickness)
	{
		DrawSierpinskiTriangle(left, Point2f(topX, topY), Point2f(rightX, rightY), colorLeft, colorTop, colorRight, thickness);
	}

	void DrawSierpinskiTriangle(float leftX, float leftY, float topX, float topY, float rightX, float rightY, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight, float thickness)
	{
		DrawSierpinskiTriangle(Point2f(leftX, leftY), Point2f(topX, topY), Point2f(rightX, rightY), colorLeft, colorTop, colorRight, thickness);
	}

	void FillSierpinskiTriangle(const Point2f& left, const Point2f& top, const Point2f& right, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight)
	{
		const Point2f
			leftMiddle{ left.x + (top.x - left.x) / 2 , left.y + (top.y - left.y) / 2 },
			middleBottom{ left.x + (right.x - left.x) / 2 , left.y + (right.y - left.y) / 2 },
			rightMiddle{ right.x - (right.x - top.x) / 2 , right.y + (top.y - right.y) / 2 };

		utils::SetColor(colorLeft);
		utils::FillTriangle(left, leftMiddle, middleBottom);

		utils::SetColor(colorTop);
		utils::FillTriangle(leftMiddle, top, rightMiddle);

		utils::SetColor(colorRight);
		utils::FillTriangle(middleBottom, rightMiddle, right);

		if (GetDistance(middleBottom, top) * GetDistance(right, left) / 2 < 1000.0f)
			return;

		FillSierpinskiTriangle(left, leftMiddle, middleBottom, colorLeft, colorTop, colorRight);
		FillSierpinskiTriangle(leftMiddle, top, rightMiddle, colorLeft, colorTop, colorRight);
		FillSierpinskiTriangle(middleBottom, rightMiddle, right, colorLeft, colorTop, colorRight);
	}

	void FillSierpinskiTriangle(float leftX, float leftY, const Point2f& top, const Point2f& right, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight)
	{
		FillSierpinskiTriangle(Point2f(leftX, leftY), top, right, colorLeft, colorTop, colorRight);
	}

	void FillSierpinskiTriangle(const Point2f& left, float topX, float topY, const Point2f& right, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight)
	{
		FillSierpinskiTriangle(left, Point2f(topX, topY), right, colorLeft, colorTop, colorRight);
	}

	void FillSierpinskiTriangle(const Point2f& left, const Point2f& top, float rightX, float rightY, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight)
	{
		FillSierpinskiTriangle(left, top, Point2f(rightX, rightY), colorLeft, colorTop, colorRight);
	}

	void FillSierpinskiTriangle(float leftX, float leftY, float topX, float topY, const Point2f& right, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight)
	{
		FillSierpinskiTriangle(Point2f(leftX, leftY), Point2f(topX, topY), right, colorLeft, colorTop, colorRight);
	}

	void FillSierpinskiTriangle(const Point2f& left, float topX, float topY, float rightX, float rightY, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight)
	{
		FillSierpinskiTriangle(left, Point2f(topX, topY), Point2f(rightX, rightY), colorLeft, colorTop, colorRight);
	}

	void FillSierpinskiTriangle(float leftX, float leftY, float topX, float topY, float rightX, float rightY, const Color4f& colorLeft, const Color4f& colorTop, const Color4f& colorRight)
	{
		FillSierpinskiTriangle(Point2f(leftX, leftY), Point2f(topX, topY), Point2f(rightX, rightY), colorLeft, colorTop, colorRight);
	}

	void DrawXgram(const Point2f& position, int points, float radius, float startAngle, float thickness)
	{
		for (float angle{}; angle < 2 * utils::g_Pi; angle += 2 * utils::g_Pi / points)
		{
			utils::DrawLine(position.x + radius * cosf(startAngle + angle), position.y + radius * sinf(startAngle + angle), position.x + radius * cosf(startAngle + angle + 4 * utils::g_Pi / points), position.y + radius * sinf(startAngle + angle + 4 * utils::g_Pi / points), thickness);
		}
	}

	void DrawXgram(float positionX, float positionY, int points, float radius, float startAngle, float thickness)
	{
		DrawXgram(Point2f{ positionX, positionY }, points, radius, startAngle, thickness);
	}

	void DrawLinearGradient(const Rectf& rectangle, const Color4f& leftColor, const Color4f& rightColor)
	{
		float colorStepR{ (rightColor.r - leftColor.r) / rectangle.width }, colorStepG{ (rightColor.g - leftColor.g) / rectangle.width }, colorStepB{ (rightColor.b - leftColor.b) / rectangle.width };

		for (int i{}; i < rectangle.width; ++i)
		{
			utils::SetColor(Color4f(leftColor.r + i * colorStepR, leftColor.g + i * colorStepG, leftColor.b + i * colorStepB, leftColor.a));
			utils::FillRect(i + rectangle.left, rectangle.bottom, rectangle.width - i, rectangle.height);
		}
	}

	void DrawLinearGradient(const Point2f& rectanglePosition, float rectangleWidth, float rectangleHeight, const Color4f& leftColor, const Color4f& rightColor)
	{
		DrawLinearGradient(Rectf{ rectanglePosition.x, rectanglePosition.y, rectangleWidth, rectangleHeight }, leftColor, rightColor);
	}

	void DrawLinearGradient(float rectanglePositionX, float rectanglePositionY, float rectangleWidth, float rectangleHeight, const Color4f& leftColor, const Color4f& rightColor)
	{
		DrawLinearGradient(Rectf{ rectanglePositionX, rectanglePositionY, rectangleWidth, rectangleHeight }, leftColor, rightColor);
	}

	void DrawDotGrid(const Point2f& position, const Point2f& resolution, float radius, float offset)
	{
		for (float j{}; j < resolution.x; ++j)
		{
			for (float i{}; i < resolution.y; ++i)
			{
				utils::FillEllipse(position.x + radius + j * 2 * (radius + offset), position.y + radius + i * 2 * (radius + offset), radius, radius);
			}
		}
	}

	void DrawDotGrid(float positionX, float positionY, const Point2f& resolution, float radius, float offset)
	{
		DrawDotGrid(Point2f{ positionX, positionY }, resolution, radius, offset);
	}

	void DrawDotGrid(const Point2f& position, float resolutionX, float resolutionY, float radius, float offset)
	{
		DrawDotGrid(position, Point2f{ resolutionX, resolutionY }, radius, offset);
	}

	void DrawDotGrid(float positionX, float positionY, float resolutionX, float resolutionY, float radius, float offset)
	{
		DrawDotGrid(Point2f{ positionX, positionY }, Point2f{ resolutionX, resolutionY }, radius, offset);
	}
	#pragma endregion DrawFunctions



	#pragma region Calculators
	int GetRandom(int maximalValue, int minimalValue)
	{
		return rand() % (maximalValue - minimalValue + 1) + minimalValue;
	}

	float GetRandom(float maximalValue, float minimalValue)
	{
		return rand() / float(RAND_MAX) * (maximalValue - minimalValue) + minimalValue;
	}

	Vector2f GetRandom(const Vector2f& maximalValue, const Vector2f& minimalValue)
	{
		Vector2f randomVector{};
		randomVector.x = GetRandom(maximalValue.x, minimalValue.x);
		randomVector.y = GetRandom(maximalValue.y, minimalValue.y);

		return randomVector;
	}

	float GetDistance(const Point2f& p1, const Point2f& p2)
	{
		return GetDistance(p1.x, p1.y, p2.x, p2.y);
	}

	float GetDistance(const Point2f& p1, float p2x, float p2y)
	{
		return GetDistance(p1.x, p1.y, p2x, p2y);
	}

	float GetDistance(float p1x, float p1y, const Point2f& p2)
	{
		return GetDistance(p1x, p1y, p2.x, p2.y);
	}

	float GetDistance(float p1x, float p1y, float p2x, float p2y)
	{
		return sqrtf(powf(p2x - p1x, 2) + powf(p2y - p1y, 2));
	}

	float ToRadians(float degrees)
	{
		return degrees / 180.0f * utils::g_Pi;
	}

	float ToDegrees(float radians)
	{
		return radians / utils::g_Pi * 180.0f;
	}
	#pragma endregion Calculators



	#pragma region Arrays
	std::string ToString(int* pNumbers, int size)
	{
		std::string elements{"| "};

		for (int idx{}; idx < size; ++idx) elements += std::to_string(pNumbers[idx]) + " | ";
		elements.pop_back();

		return elements;
	}

	void Randomize(int* pNumbers, int size, int minimalValue, int maximalValue)
	{
		for (int idx{}; idx < size; ++idx)
			pNumbers[idx] = GetRandom(minimalValue, maximalValue);
	}

	void Randomize(int* pNumbers, int startingIndex, int endingIndex, int minimalValue, int maximalValue)
	{
		for (int idx{ startingIndex }; idx <= endingIndex; ++idx)
			pNumbers[idx] = GetRandom(minimalValue, maximalValue);
	}

	int GetIndex(int rowIndex, int columnIndex, int columnAmount)
	{
		if (columnIndex >= columnAmount)
		{
			columnIndex = columnAmount - 1;
		}
		if (columnIndex < 0)
		{
			columnIndex = 0;
		}
		return rowIndex * columnAmount + columnIndex;
	}

	int Count(int* pNumbers, int size, int value)
	{
		int amount{};

		for (int idx{}; idx < size; ++idx)
			if (pNumbers[idx] == value)
				++amount;

		return amount;
	}

	int MinElement(int* pNumbers, int size)
	{
		int smallestElement{ *pNumbers };

		for (int idx{ 1 }; idx < size; ++idx)
			if (pNumbers[idx] < smallestElement)
				smallestElement = pNumbers[idx];

		return smallestElement;
	}

	int MaxElement(int* pNumbers, int size)
	{
		int biggestElement{ *pNumbers };

		for (int idx{ 1 }; idx < size; ++idx)
			if (pNumbers[idx] > biggestElement)
				biggestElement = pNumbers[idx];

		return biggestElement;
	}

	void Swap(int* pNumbers, int index1, int index2)
	{
		const int element1{ pNumbers[index1] };
		pNumbers[index1] = pNumbers[index2];
		pNumbers[index2] = element1;
	}

	void Shuffle(int* pNumbers, int size, int amount)
	{
		for (int i{}; i < amount; ++i)
		{
			int idx1{ rand() % size };
			int idx2{ rand() % size };
			while (idx2 == idx1)
				idx2 = rand() % size;

			Swap(pNumbers, idx1, idx2);
		}
	}

	void BubbleSort(int* pNumbers, int size, bool increasing)
	{
		if (increasing)
			for (int i{ size }; i > 1; --i)
				for (int idx{ 1 }; idx < i; ++idx)
				{
					if (pNumbers[idx] < pNumbers[idx - 1])
						Swap(pNumbers, idx, idx - 1);
				}
		else
			for (int i{ size }; i > 1; --i)
				for (int idx{ 1 }; idx < i; ++idx)
				{
					if (pNumbers[idx] > pNumbers[idx - 1])
						Swap(pNumbers, idx, idx - 1);
				}
	}
	#pragma endregion Arrays



	#pragma region CollisionFunctionality
	bool IsOverlapping(const Circlef& circle1, const Circlef& circle2)
	{
		if (GetDistance(circle1.center, circle2.center) < circle1.radius + circle2.radius) return true;
		return false;
	}

	bool IsOverlapping(const Point2f& circle1Position, float circle1Radius, const Circlef& circle2)
	{
		return IsOverlapping(Circlef(circle1Position, circle1Radius), circle2);
	}

	bool IsOverlapping(float circle1PositionX, float circle1PositionY, float circle1Radius, const Circlef& circle2)
	{
		return IsOverlapping(Circlef(Point2f(circle1PositionX, circle1PositionY), circle1Radius), circle2);
	}

	bool IsOverlapping(const Circlef& circle1, const Point2f& circle2Position, float circle2Radius)
	{
		return IsOverlapping(circle1, Circlef(circle2Position, circle2Radius));
	}

	bool IsOverlapping(const Circlef& circle1, float circle2PositionX, float circle2PositionY, float circle2Radius)
	{
		return IsOverlapping(circle1, Circlef(Point2f(circle2PositionX, circle2PositionY), circle2Radius));
	}

	bool IsOverlapping(const Point2f& circle1Position, float circle1Radius, const Point2f& circle2Position, float circle2Radius)
	{
		return IsOverlapping(Circlef(circle1Position, circle1Radius), Circlef(circle2Position, circle2Radius));
	}

	bool IsOverlapping(float circle1PositionX, float circle1PositionY, float circle1Radius, const Point2f& circle2Position, float circle2Radius)
	{
		return IsOverlapping(Circlef(Point2f(circle1PositionX, circle1PositionY), circle1Radius), Circlef(circle2Position, circle2Radius));
	}

	bool IsOverlapping(const Point2f& circle1Position, float circle1Radius, float circle2PositionX, float circle2PositionY, float circle2Radius)
	{
		return IsOverlapping(Circlef(circle1Position, circle1Radius), Circlef(Point2f(circle2PositionX, circle2PositionY), circle2Radius));
	}

	bool IsOverlapping(float circle1PositionX, float circle1PositionY, float circle1Radius, float circle2PositionX, float circle2PositionY, float circle2Radius)
	{
		return IsOverlapping(Circlef(Point2f(circle1PositionX, circle1PositionY), circle1Radius), Circlef(Point2f(circle2PositionX, circle2PositionY), circle2Radius));
	}

	bool IsOverlapping(const Rectf& rectangle1, const Rectf& rectangle2)
	{
		const Point2f topLeft1{ rectangle1.left,  rectangle1.bottom + rectangle1.height }, bottomRight1{ rectangle1.left + rectangle1.width,  rectangle1.bottom };
		const Point2f topLeft2{ rectangle2.left,  rectangle2.bottom + rectangle2.height }, bottomRight2{ rectangle2.left + rectangle2.width,  rectangle2.bottom };

		if (topLeft1.x > bottomRight2.x || topLeft2.x > bottomRight1.x)
			return false;

		if (bottomRight2.y > topLeft1.y || bottomRight1.y > topLeft2.y)
			return false;

		return true;
	}

	bool IsOverlapping(const Rectf& rectangle1, const Point2f& rectangle2Position, const Point2f& rectangle2Size)
	{
		return IsOverlapping(rectangle1, Rectf(rectangle2Position.x, rectangle2Position.y, rectangle2Size.x, rectangle2Size.y));
	}

	bool IsOverlapping(const Rectf& rectangle1, const Point2f& rectangle2Position, float rectangle2Width, float rectangle2Height)
	{
		return IsOverlapping(rectangle1, Rectf(rectangle2Position.x, rectangle2Position.y, rectangle2Width, rectangle2Height));
	}

	bool IsOverlapping(const Rectf& rectangle1, float rectangle2PositionX, float rectangle2PositionY, const Point2f& rectangle2Size)
	{
		return IsOverlapping(rectangle1, Rectf(rectangle2PositionX, rectangle2PositionY, rectangle2Size.x, rectangle2Size.y));
	}

	bool IsOverlapping(const Rectf& rectangle1, float rectangle2PositionX, float rectangle2PositionY, float rectangle2Width, float rectangle2Height)
	{
		return IsOverlapping(rectangle1, Rectf(rectangle2PositionX, rectangle2PositionY, rectangle2Width, rectangle2Height));
	}

	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, const Rectf& rectangle2)
	{
		return IsOverlapping(Rectf(rectangle1Position.x, rectangle1Position.y, rectangle1Size.x, rectangle1Size.y), rectangle2);
	}

	bool IsOverlapping(const Point2f& rectangle1Position, float rectangle1SizeX, float rectangle1SizeY, const Rectf& rectangle2)
	{
		return IsOverlapping(Rectf(rectangle1Position.x, rectangle1Position.y, rectangle1SizeX, rectangle1SizeY), rectangle2);
	}

	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, const Point2f& rectangle1Size, const Rectf& rectangle2)
	{
		return IsOverlapping(Rectf(rectangle1PositionX, rectangle1PositionY, rectangle1Size.x, rectangle1Size.y), rectangle2);
	}

	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, float rectangle1SizeX, float rectangle1SizeY, const Rectf& rectangle2)
	{
		return IsOverlapping(Rectf(rectangle1PositionX, rectangle1PositionY, rectangle1SizeX, rectangle1SizeY), rectangle2);
	}

	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, const Point2f& rectangle2Position, const Point2f& rectangle2Size)
	{
		return IsOverlapping(Rectf(rectangle1Position.x, rectangle1Position.y, rectangle1Size.x, rectangle1Size.y), Rectf(rectangle2Position.x, rectangle2Position.y, rectangle2Size.x, rectangle2Size.y));
	}

	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, const Point2f& rectangle1Size, const Point2f& rectangle2Position, const Point2f& rectangle2Size)
	{
		return IsOverlapping(Rectf(rectangle1PositionX, rectangle1PositionY, rectangle1Size.x, rectangle1Size.y), Rectf(rectangle2Position.x, rectangle2Position.y, rectangle2Size.x, rectangle2Size.y));
	}

	bool IsOverlapping(const Point2f& rectangle1Position, float rectangle1SizeX, float rectangle1SizeY, const Point2f& rectangle2Position, const Point2f& rectangle2Size)
	{
		return IsOverlapping(Rectf(rectangle1Position.x, rectangle1Position.y, rectangle1SizeX, rectangle1SizeY), Rectf(rectangle2Position.x, rectangle2Position.y, rectangle2Size.x, rectangle2Size.y));
	}

	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, float rectangle2PositionX, float rectangle2PositionY, const Point2f& rectangle2Size)
	{
		return IsOverlapping(Rectf(rectangle1Position.x, rectangle1Position.y, rectangle1Size.x, rectangle1Size.y), Rectf(rectangle2PositionX, rectangle2PositionY, rectangle2Size.x, rectangle2Size.y));
	}

	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, const Point2f& rectangle2Position, float rectangle2SizeX, float rectangle2SizeY)
	{
		return IsOverlapping(Rectf(rectangle1Position.x, rectangle1Position.y, rectangle1Size.x, rectangle1Size.y), Rectf(rectangle2Position.x, rectangle2Position.y, rectangle2SizeX, rectangle2SizeY));
	}

	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, float rectangle1SizeX, float rectangle1SizeY, const Point2f& rectangle2Position, const Point2f& rectangle2Size)
	{
		return IsOverlapping(Rectf(rectangle1PositionX, rectangle1PositionY, rectangle1SizeX, rectangle1SizeY), Rectf(rectangle2Position.x, rectangle2Position.y, rectangle2Size.x, rectangle2Size.y));
	}

	bool IsOverlapping(const Point2f& rectangle1Position, float rectangle1SizeX, float rectangle1SizeY, float rectangle2PositionX, float rectangle2PositionY, const Point2f& rectangle2Size)
	{
		return IsOverlapping(Rectf(rectangle1Position.x, rectangle1Position.y, rectangle1SizeX, rectangle1SizeY), Rectf(rectangle2PositionX, rectangle2PositionY, rectangle2Size.x, rectangle2Size.y));
	}

	bool IsOverlapping(const Point2f& rectangle1Position, const Point2f& rectangle1Size, float rectangle2PositionX, float rectangle2PositionY, float rectangle2SizeX, float rectangle2SizeY)
	{
		return IsOverlapping(Rectf(rectangle1Position.x, rectangle1Position.y, rectangle1Size.x, rectangle1Size.y), Rectf(rectangle2PositionX, rectangle2PositionY, rectangle2SizeX, rectangle2SizeY));
	}

	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, float rectangle1SizeX, float rectangle1SizeY, float rectangle2PositionX, float rectangle2PositionY, const Point2f& rectangle2Size)
	{
		return IsOverlapping(Rectf(rectangle1PositionX, rectangle1PositionY, rectangle1SizeX, rectangle1SizeY), Rectf(rectangle2PositionX, rectangle2PositionY, rectangle2Size.x, rectangle2Size.y));
	}

	bool IsOverlapping(const Point2f& rectangle1Position, float rectangle1SizeX, float rectangle1SizeY, float rectangle2PositionX, float rectangle2PositionY, float rectangle2SizeX, float rectangle2SizeY)
	{
		return IsOverlapping(Rectf(rectangle1Position.x, rectangle1Position.y, rectangle1SizeX, rectangle1SizeY), Rectf(rectangle2PositionX, rectangle2PositionY, rectangle2SizeX, rectangle2SizeY));
	}

	bool IsOverlapping(float rectangle1PositionX, float rectangle1PositionY, float rectangle1SizeX, float rectangle1SizeY, float rectangle2PositionX, float rectangle2PositionY, float rectangle2SizeX, float rectangle2SizeY)
	{
		return IsOverlapping(Rectf(rectangle1PositionX, rectangle1PositionY, rectangle1SizeX, rectangle1SizeY), Rectf(rectangle2PositionX, rectangle2PositionY, rectangle2SizeX, rectangle2SizeY));
	}

	bool IsOverlapping(const Rectf& rectangle, const Circlef& circle)
	{
		if (
			(circle.center.x + circle.radius > rectangle.left && circle.center.x - circle.radius < rectangle.left + rectangle.width && circle.center.y > rectangle.bottom && circle.center.y < rectangle.bottom + rectangle.height)
			||
			(circle.center.y + circle.radius > rectangle.bottom && circle.center.y - circle.radius < rectangle.bottom + rectangle.height && circle.center.x > rectangle.left && circle.center.x < rectangle.left + rectangle.width)
			||
			(IsOverlapping(circle, rectangle.left, rectangle.bottom)) || (IsOverlapping(circle, rectangle.left, rectangle.bottom + rectangle.height))
			||
			(IsOverlapping(circle, rectangle.left + rectangle.width, rectangle.bottom)) || (IsOverlapping(circle, rectangle.left + rectangle.width, rectangle.bottom + rectangle.height))
			)
			return true;

		return false;
	}

	bool IsOverlapping(const Rectf& rectangle, const Point2f& circlePosition, float circleRadius)
	{
		return IsOverlapping(rectangle, Circlef(circlePosition, circleRadius));
	}

	bool IsOverlapping(const Rectf& rectangle, float circlePositionX, float circlePositionY, float circleRadius)
	{
		return IsOverlapping(rectangle, Circlef(Point2f(circlePositionX, circlePositionY), circleRadius));
	}

	bool IsOverlapping(const Point2f& rectanglePosition, const Point2f& rectangleSize, const Circlef& circle)
	{
		return IsOverlapping(Rectf(rectanglePosition.x, rectanglePosition.y, rectangleSize.x, rectangleSize.y), circle);
	}

	bool IsOverlapping(const Point2f& rectanglePosition, float rectangleSizeX, float rectangleSizeY, const Circlef& circle)
	{
		return IsOverlapping(Rectf(rectanglePosition.x, rectanglePosition.y, rectangleSizeX, rectangleSizeY), circle);
	}

	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, const Point2f& rectangleSize, const Circlef& circle)
	{
		return IsOverlapping(Rectf(rectanglePositionX, rectanglePositionY, rectangleSize.x, rectangleSize.y), circle);
	}

	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, float rectangleSizeX, float rectangleSizeY, const Circlef& circle)
	{
		return IsOverlapping(Rectf(rectanglePositionX, rectanglePositionY, rectangleSizeX, rectangleSizeY), circle);
	}

	bool IsOverlapping(const Point2f& rectanglePosition, const Point2f& rectangleSize, const Point2f& circlePosition, float circleRadius)
	{
		return IsOverlapping(Rectf(rectanglePosition.x, rectanglePosition.y, rectangleSize.x, rectangleSize.y), Circlef(circlePosition, circleRadius));
	}

	bool IsOverlapping(const Point2f& rectanglePosition, const Point2f& rectangleSize, float circlePositionX, float circlePositionY, float circleRadius)
	{
		return IsOverlapping(Rectf(rectanglePosition.x, rectanglePosition.y, rectangleSize.x, rectangleSize.y), Circlef(Point2f(circlePositionX, circlePositionY), circleRadius));
	}

	bool IsOverlapping(const Point2f& rectanglePosition, float rectangleSizeX, float rectangleSizeY, const Point2f& circlePosition, float circleRadius)
	{
		return IsOverlapping(Rectf(rectanglePosition.x, rectanglePosition.y, rectangleSizeX, rectangleSizeY), Circlef(circlePosition, circleRadius));
	}

	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, const Point2f& rectangleSize, const Point2f& circlePosition, float circleRadius)
	{
		return IsOverlapping(Rectf(rectanglePositionX, rectanglePositionY, rectangleSize.x, rectangleSize.y), Circlef(circlePosition, circleRadius));
	}

	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, float rectangleSizeX, float rectangleSizeY, const Point2f& circlePosition, float circleRadius)
	{
		return IsOverlapping(Rectf(rectanglePositionX, rectanglePositionY, rectangleSizeX, rectangleSizeY), Circlef(circlePosition, circleRadius));
	}

	bool IsOverlapping(const Point2f& rectanglePosition, float rectangleSizeX, float rectangleSizeY, float circlePositionX, float circlePositionY, float circleRadius)
	{
		return IsOverlapping(Rectf(rectanglePosition.x, rectanglePosition.y, rectangleSizeX, rectangleSizeY), Circlef(Point2f(circlePositionX, circlePositionY), circleRadius));
	}

	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, const Point2f& rectangleSize, float circlePositionX, float circlePositionY, float circleRadius)
	{
		return IsOverlapping(Rectf(rectanglePositionX, rectanglePositionY, rectangleSize.x, rectangleSize.y), Circlef(Point2f(circlePositionX, circlePositionY), circleRadius));
	}

	bool IsOverlapping(float rectanglePositionX, float rectanglePositionY, float rectangleSizeX, float rectangleSizeY, float circlePositionX, float circlePositionY, float circleRadius)
	{
		return IsOverlapping(Rectf(rectanglePositionX, rectanglePositionY, rectangleSizeX, rectangleSizeY), Circlef(Point2f(circlePositionX, circlePositionY), circleRadius));
	}

	bool Raycast(const std::vector<std::vector<Point2f>>& vVertices, const Point2f& rayP1, const Point2f& rayP2, utils::HitInfo& hitInfo)
	{
		bool didSucces{};

		utils::HitInfo closestHitInfo{};
		float closestDistance{ INFINITY };

		for (const std::vector<Point2f>& vPoint2f : vVertices)
		{
			utils::HitInfo testHitInfo{};
			if (!didSucces)
			{
				didSucces = utils::Raycast(vPoint2f, rayP1, rayP2, testHitInfo);

				const float currentDistance{ utils::GetDistance(rayP1, testHitInfo.intersectPoint) };

				if (currentDistance < closestDistance)
				{
					closestHitInfo = testHitInfo;
					closestDistance = currentDistance;
				}
			}
		}

		hitInfo = closestHitInfo;
		return didSucces;
	}
	#pragma endregion CollisionFunctionality



	#pragma region Vectors
	std::string ToString(const Vector2f& vector)
	{
		return std::string{ "[" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + "]" };
	}

	std::string ToString(float vectorX, float vectorY)
	{
		return ToString(Vector2f(vectorX, vectorY));
	}

	float DotProduct(const Vector2f& vector1, const Vector2f& vector2)
	{
		return vector1.x * vector2.x + vector1.y * vector2.y;
	}

	float DotProduct(const Vector2f& vector1, float vector2X, float vector2Y)
	{
		return DotProduct(vector1, Vector2f(vector2X, vector2Y));
	}

	float DotProduct(float vector1X, float vector1Y, const Vector2f& vector2)
	{
		return DotProduct(Vector2f(vector1X, vector1Y), vector2);
	}

	float DotProduct(float vector1X, float vector1Y, float vector2X, float vector2Y)
	{
		return DotProduct(Vector2f(vector1X, vector1Y), Vector2f(vector2X, vector2Y));
	}

	float CrossProduct(const Vector2f& vector1, const Vector2f& vector2)
	{
		return vector1.x * vector2.y - vector1.y * vector2.x;
	}

	float CrossProduct(const Vector2f& vector1, float vector2X, float vector2Y)
	{
		return CrossProduct(vector1, Vector2f(vector2X, vector2Y));
	}

	float CrossProduct(float vector1X, float vector1Y, const Vector2f& vector2)
	{
		return CrossProduct(Vector2f(vector1X, vector1Y), vector2);
	}

	float CrossProduct(float vector1X, float vector1Y, float vector2X, float vector2Y)
	{
		return CrossProduct(Vector2f(vector1X, vector1Y), Vector2f(vector2X, vector2Y));
	}

	float Length(const Vector2f& vector)
	{
		return sqrtf(powf(vector.x, 2) + powf(vector.y, 2));
	}

	float Length(float vector1X, float vector1Y)
	{
		return Length(Vector2f(vector1X, vector1Y));
	}

	float AngleBetween(const Vector2f& vector1, const Vector2f& vector2)
	{
		return fabsf(atan2f(CrossProduct(vector1, vector2), DotProduct(vector1, vector2)));
	}

	float AngleBetween(const Vector2f& vector1, float vector2X, float vector2Y)
	{
		return AngleBetween(vector1, Vector2f(vector2X, vector2Y));
	}

	float AngleBetween(float vector1X, float vector1Y, const Vector2f& vector2)
	{
		return AngleBetween(Vector2f(vector1X, vector1Y), vector2);
	}

	float AngleBetween(float vector1X, float vector1Y, float vector2X, float vector2Y)
	{
		return AngleBetween(Vector2f(vector1X, vector1Y), Vector2f(vector2X, vector2Y));
	}

	bool AreEqual(const Vector2f& vector1, const Vector2f& vector2)
	{
		if (AngleBetween(vector1, vector2) < 0.0000001f) return true;
		return false;
	}

	bool AreEqual(const Vector2f& vector1, float vector2X, float vector2Y)
	{
		return AreEqual(vector1, Vector2f(vector2X, vector2Y));
	}

	bool AreEqual(float vector1X, float vector1Y, const Vector2f& vector2)
	{
		return AreEqual(Vector2f(vector1X, vector1Y), vector2);
	}

	bool AreEqual(float vector1X, float vector1Y, float vector2X, float vector2Y)
	{
		return AreEqual(Vector2f(vector1X, vector1Y), Vector2f(vector2X, vector2Y));
	}

	void DrawVector(const Vector2f& vector, const Point2f& startingPoint)
	{
		const float triangleSize{ 5.0f };
		const float theta(atan2f(vector.y, vector.x));
		const Point2f pivotPoint{ startingPoint.x + vector.x - triangleSize * cosf(theta), startingPoint.y + vector.y - triangleSize * sinf(theta) };
		const Point2f 
			p1{ pivotPoint.x + triangleSize * cosf(theta					    ), pivotPoint.y + triangleSize * sinf(theta                        ) },
			p2{ pivotPoint.x + triangleSize * cosf(theta + (2 * utils::g_Pi / 3)), pivotPoint.y + triangleSize * sinf(theta + (2 * utils::g_Pi / 3)) },
			p3{ pivotPoint.x + triangleSize * cosf(theta + (4 * utils::g_Pi / 3)), pivotPoint.y + triangleSize * sinf(theta + (4 * utils::g_Pi / 3)) };

		utils::DrawLine(startingPoint.x, startingPoint.y, startingPoint.x + vector.x, startingPoint.y + vector.y);
		utils::FillTriangle(p1, p2, p3);
	}

	void DrawVector(const Vector2f& vector, float startingPointX, float startingPointY)
	{
		DrawVector(vector, Point2f(startingPointX, startingPointY));
	}

	void DrawVector(float vectorX, float vectorY, const Point2f& startingPoint)
	{
		DrawVector(Vector2f(vectorX, vectorY), startingPoint);
	}

	void DrawVector(float vectorX, float vectorY, float startingPointX, float startingPointY)
	{
		DrawVector(Vector2f(vectorX, vectorY), Point2f(startingPointX, startingPointY));
	}

	Vector2f AddVectors(const Vector2f& vector1, const Vector2f& vector2)
	{
		return Vector2f(vector1.x + vector2.x, vector1.y + vector2.y);
	}

	Vector2f AddVectors(const Vector2f& vector1, float vector2X, float vector2Y)
	{
		return AddVectors(vector1, Vector2f(vector2X, vector2Y));
	}

	Vector2f AddVectors(float vector1X, float vector1Y, const Vector2f& vector2)
	{
		return AddVectors(Vector2f(vector1X, vector1Y), vector2);
	}

	Vector2f AddVectors(float vector1X, float vector1Y, float vector2X, float vector2Y)
	{
		return AddVectors(Vector2f(vector1X, vector1Y), Vector2f(vector2X, vector2Y));
	}

	Vector2f SubstractVectors(const Vector2f& vector1, const Vector2f& vector2)
	{
		return AddVectors(vector1, -vector2.x, -vector2.y);
	}

	Vector2f SubstractVectors(const Vector2f& vector1, float vector2X, float vector2Y)
	{
		return SubstractVectors(vector1, Vector2f(vector2X, vector2Y));
	}

	Vector2f SubstractVectors(float vector1X, float vector1Y, const Vector2f& vector2)
	{
		return SubstractVectors(Vector2f(vector1X, vector1Y), vector2);
	}

	Vector2f SubstractVectors(float vector1X, float vector1Y, float vector2X, float vector2Y)
	{
		return SubstractVectors(Vector2f(vector1X, vector1Y), Vector2f(vector2X, vector2Y));
	}

	Vector2f Scale(const Vector2f& vector, float scalar)
	{
		return Vector2f(vector.x * scalar, vector.y * scalar);
	}

	Vector2f Scale(float vectorX, float vectorY, float scalar)
	{
		return Scale(Vector2f(vectorX, vectorY), scalar);
	}

	Vector2f Normalize(Vector2f vector)
	{
		return Vector2f(vector.x / Length(vector), vector.y / Length(vector));
	}

	Vector2f Normalize(float vectorX, float vectorY)
	{
		return Normalize(Vector2f(vectorX, vectorY));
	}
	#pragma endregion Vectors
}