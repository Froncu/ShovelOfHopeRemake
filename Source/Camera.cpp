#include "pch.h"
#include "Camera.h"

#include "GameObject.h"

#include "SVGParser.h"

#include "InputManager.h"

#include "GameObject.h"

#include "myutils.h"

#pragma region StaticDataMembers
Rectf Camera::m_TRANSFORMED_VIEWPORT{ 0.0f, 0.0f, 400.0f, 208.0f };
float Camera::m_ZOOM{};

GameObject* Camera::m_pGAME_OBJECT_TO_FOLLOW{};
bool Camera::m_STOP_FOLLOWING{};

std::vector<Rectf> Camera::m_vCAMERA_ZONES{};

bool Camera::m_IS_SHIFTING{};
Vector2f Camera::m_SHIFT_VECTOR{}, Camera::m_SHIFTED_VECTOR{};

int Camera::m_LAST_CAMERA_ZONE_INDEX{}, Camera::m_CURRENT_CAMERA_ZONE_INDEX{};

bool Camera::m_IS_SHAKING{};

float Camera::m_SHAKE_FRAME_SECONDS{ 0.02f }, Camera::m_SHAKE_ACCUMULATED_SECONDS{};
float Camera::m_HORIZONTAL_SHAKE_OFFSET{}, Camera::m_VERTICAL_SHAKE_OFFSET{};
#pragma endregion StaticDataMembers



#pragma region PublicMethods
void Camera::Update(float elapsedSeconds)
{
	if (m_pGAME_OBJECT_TO_FOLLOW->m_ShouldBeDeleted) 
		m_STOP_FOLLOWING = true;

	if (!m_STOP_FOLLOWING)
	{
		if (!m_IS_SHIFTING)
		{
			DetermineCurrentZone();
		}

		if (m_LAST_CAMERA_ZONE_INDEX == m_CURRENT_CAMERA_ZONE_INDEX)
		{
			Follow();
			ClipToZone();
			Shake(elapsedSeconds);
		}
		else
		{
			ShiftToNextZone(elapsedSeconds);
		}
	}
}

void Camera::Reset()
{
	m_pGAME_OBJECT_TO_FOLLOW = nullptr;
	m_STOP_FOLLOWING = false;

	m_vCAMERA_ZONES = std::vector<Rectf>();

	m_IS_SHIFTING = false;
	m_SHIFT_VECTOR = Vector2f();
	m_SHIFTED_VECTOR = Vector2f();

	m_LAST_CAMERA_ZONE_INDEX = 0;
	m_CURRENT_CAMERA_ZONE_INDEX = 0;

	m_IS_SHAKING = false;

	m_SHAKE_FRAME_SECONDS = 0.02f;
	m_SHAKE_ACCUMULATED_SECONDS = 0.0f;

	m_HORIZONTAL_SHAKE_OFFSET = 0.0f;
	m_VERTICAL_SHAKE_OFFSET = 0.0f;
}

void Camera::SetShaking(bool isShaking)
{
	m_IS_SHAKING = isShaking;
}

void Camera::SetShakingFrameSeconds(float frameSeconds)
{
	m_SHAKE_FRAME_SECONDS = frameSeconds;
}

void Camera::SetSVGPath(const std::string& SVGPath)
{
	m_vCAMERA_ZONES.clear();

	std::vector< std::vector<Point2f>> vvVertices{};
	SVGParser::GetVerticesFromSvgFile(SVGPath, vvVertices);

	for (const std::vector<Point2f>& vVertices : vvVertices)
	{
		Rectf cameraZone{ INFINITY, INFINITY, 0, 0 };

		for (const Point2f& vertex : vVertices)
		{
			if (vertex.x < cameraZone.left)
			{
				cameraZone.left = vertex.x;
			}

			if (vertex.y < cameraZone.bottom)
			{
				cameraZone.bottom = vertex.y;
			}
		}

		for (const Point2f& vertex : vVertices)
		{
			if (vertex.x > cameraZone.left)
			{
				cameraZone.width = vertex.x - cameraZone.left;
			}
			if (vertex.y > cameraZone.bottom)
			{
				cameraZone.height = vertex.y - cameraZone.bottom;
			}
		}

		m_vCAMERA_ZONES.push_back(cameraZone);
	}

	DetermineCurrentZone();
	Follow();
	ClipToZone();

	m_LAST_CAMERA_ZONE_INDEX = m_CURRENT_CAMERA_ZONE_INDEX;
}

void Camera::SetViewPort(const Rectf& viewPort)
{
	m_ZOOM = viewPort.width / m_TRANSFORMED_VIEWPORT.width;
}

void Camera::SetGameObjectToFollow(GameObject* const pGameObject)
{
	if (pGameObject) m_pGAME_OBJECT_TO_FOLLOW = pGameObject;

	DetermineCurrentZone();
	Follow();
	ClipToZone();

	m_LAST_CAMERA_ZONE_INDEX = m_CURRENT_CAMERA_ZONE_INDEX;
}

Rectf Camera::GetTransformedViewPort()
{
	return Rectf(m_TRANSFORMED_VIEWPORT.left + m_HORIZONTAL_SHAKE_OFFSET, m_TRANSFORMED_VIEWPORT.bottom + m_VERTICAL_SHAKE_OFFSET, m_TRANSFORMED_VIEWPORT.width, m_TRANSFORMED_VIEWPORT.height);
}

Point2f Camera::GetShakeOffsets()
{
	return Point2f(m_HORIZONTAL_SHAKE_OFFSET, m_VERTICAL_SHAKE_OFFSET);
}

float Camera::GetZoom()
{
	return m_ZOOM;
}

bool Camera::IsShifting()
{
	return m_IS_SHIFTING;
}

const std::vector<Rectf>& Camera::GetCameraZones()
{
	return m_vCAMERA_ZONES;
}

int Camera::GetCurrentCameraZoneIndex()
{
	return m_CURRENT_CAMERA_ZONE_INDEX;
}
int Camera::GetLastCameraZoneIndex()
{
	return m_LAST_CAMERA_ZONE_INDEX;
}
#pragma endregion PublicMethods



#pragma region PrivateMethods
bool Camera::IsPointInRectangle(const Point2f &point, const Rectf &rectangle)
{
	return 
	(
		point.x >= rectangle.left
		&&
		point.x <= rectangle.left + rectangle.width
		&&
		point.y >= rectangle.bottom
		&&
		point.y <= rectangle.bottom + rectangle.height
	);
}

void Camera::DetermineCurrentZone()
{
	if (m_pGAME_OBJECT_TO_FOLLOW)
	{
		for (int index{}; index < m_vCAMERA_ZONES.size(); ++index)
		{
			if (IsPointInRectangle(m_pGAME_OBJECT_TO_FOLLOW->m_RootCenter, m_vCAMERA_ZONES[index]))
			{
				m_CURRENT_CAMERA_ZONE_INDEX = index;
				break;
			}
		}
	}
}

void Camera::Follow()
{
	if (m_pGAME_OBJECT_TO_FOLLOW)
	{
		m_TRANSFORMED_VIEWPORT.left = m_pGAME_OBJECT_TO_FOLLOW->m_RootCenter.x - m_TRANSFORMED_VIEWPORT.width / 2;
		m_TRANSFORMED_VIEWPORT.bottom = m_pGAME_OBJECT_TO_FOLLOW->m_RootCenter.y - m_TRANSFORMED_VIEWPORT.height / 2;
	}
}

void Camera::ClipToZone()
{
	if (m_pGAME_OBJECT_TO_FOLLOW)
	{
		const Rectf& currentCameraZone{ m_vCAMERA_ZONES[m_CURRENT_CAMERA_ZONE_INDEX] };

		if (currentCameraZone.width <= m_TRANSFORMED_VIEWPORT.width)
		{
			m_TRANSFORMED_VIEWPORT.left = currentCameraZone.left;
		}
		else if (m_TRANSFORMED_VIEWPORT.left < currentCameraZone.left)
		{
			m_TRANSFORMED_VIEWPORT.left = currentCameraZone.left;
		}
		else if (m_TRANSFORMED_VIEWPORT.left + m_TRANSFORMED_VIEWPORT.width > currentCameraZone.left + currentCameraZone.width)
		{
			m_TRANSFORMED_VIEWPORT.left = currentCameraZone.left + currentCameraZone.width - m_TRANSFORMED_VIEWPORT.width;
		}

		if (currentCameraZone.height <= m_TRANSFORMED_VIEWPORT.height)
		{
			m_TRANSFORMED_VIEWPORT.bottom = currentCameraZone.bottom;
		}
		else if (m_TRANSFORMED_VIEWPORT.bottom < currentCameraZone.bottom)
		{
			m_TRANSFORMED_VIEWPORT.bottom = currentCameraZone.bottom;
		}
		else if (m_TRANSFORMED_VIEWPORT.bottom + m_TRANSFORMED_VIEWPORT.height > currentCameraZone.bottom + currentCameraZone.height)
		{
			m_TRANSFORMED_VIEWPORT.bottom = currentCameraZone.bottom + currentCameraZone.height - m_TRANSFORMED_VIEWPORT.height;
		}
	}
}

void Camera::ShiftToNextZone(float elapsedSeconds)
{
	if (m_pGAME_OBJECT_TO_FOLLOW)
	{
		const float shiftSeconds{ 1.0f };
		const Rectf& currentCameraZone{ m_vCAMERA_ZONES[m_CURRENT_CAMERA_ZONE_INDEX] };
		const Rectf& lastCameraZone{ m_vCAMERA_ZONES[m_LAST_CAMERA_ZONE_INDEX] };

		if (!m_IS_SHIFTING)
		{
			Point2f startingPoint{ m_TRANSFORMED_VIEWPORT.left, m_TRANSFORMED_VIEWPORT.bottom }, destinationPoint{ m_TRANSFORMED_VIEWPORT.left, m_TRANSFORMED_VIEWPORT.bottom };

			if (currentCameraZone.left > lastCameraZone.left)
			{
				destinationPoint.x = currentCameraZone.left;
			}
			else if (currentCameraZone.left < lastCameraZone.left)
			{
				destinationPoint.x = currentCameraZone.left + currentCameraZone.width - m_TRANSFORMED_VIEWPORT.width;
			}

			if (currentCameraZone.bottom > lastCameraZone.bottom)
			{
				destinationPoint.y = currentCameraZone.bottom;
			}
			else if (currentCameraZone.bottom < lastCameraZone.bottom)
			{
				destinationPoint.y = currentCameraZone.bottom + currentCameraZone.height - m_TRANSFORMED_VIEWPORT.height;
			}

			m_SHIFT_VECTOR = destinationPoint - startingPoint;
			m_IS_SHIFTING = true;
		}

		const Vector2f shiftFragment{ m_SHIFT_VECTOR.x * elapsedSeconds / shiftSeconds, m_SHIFT_VECTOR.y * elapsedSeconds / shiftSeconds };

		m_TRANSFORMED_VIEWPORT.left += shiftFragment.x;
		m_pGAME_OBJECT_TO_FOLLOW->m_RootCenter.x += m_SHIFT_VECTOR.Normalized().x * 15.0f * elapsedSeconds / shiftSeconds;

		m_TRANSFORMED_VIEWPORT.bottom += shiftFragment.y;
		m_pGAME_OBJECT_TO_FOLLOW->m_RootCenter.y += m_SHIFT_VECTOR.Normalized().y * 15.0f * elapsedSeconds / shiftSeconds;

		m_SHIFTED_VECTOR += shiftFragment;

		if (abs(m_SHIFTED_VECTOR.x) >= abs(m_SHIFT_VECTOR.x) && abs(m_SHIFTED_VECTOR.y) >= abs(m_SHIFT_VECTOR.y))
		{
			const Vector2f overshoot{ m_SHIFTED_VECTOR - m_SHIFT_VECTOR };
			m_TRANSFORMED_VIEWPORT.left -= overshoot.x;
			m_TRANSFORMED_VIEWPORT.bottom -= overshoot.y;

			m_SHIFTED_VECTOR = Vector2f(0, 0);

			m_LAST_CAMERA_ZONE_INDEX = m_CURRENT_CAMERA_ZONE_INDEX;
			m_IS_SHIFTING = false;
		}
	}
}

void Camera::Shake(float elapsedSeconds)
{
	if (m_IS_SHAKING)
	{
		m_SHAKE_ACCUMULATED_SECONDS += elapsedSeconds;

		if (m_SHAKE_ACCUMULATED_SECONDS >= m_SHAKE_FRAME_SECONDS)
		{
			m_SHAKE_ACCUMULATED_SECONDS -= m_SHAKE_FRAME_SECONDS;

			m_HORIZONTAL_SHAKE_OFFSET = myutils::GetRandom(1, -1) / m_ZOOM;
			m_VERTICAL_SHAKE_OFFSET = myutils::GetRandom(1, -1) / m_ZOOM;
		}
	}
	else
	{
		m_HORIZONTAL_SHAKE_OFFSET = 0;
		m_VERTICAL_SHAKE_OFFSET = 0;
	}
}
#pragma endregion PrivateMethods