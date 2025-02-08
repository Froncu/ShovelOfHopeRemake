#pragma once

#include <vector>

class GameObject;
class Camera final
{
public:
	//	Rule of 5
	~Camera() = delete;

	Camera(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera& operator=(Camera&& other) = delete;

	//	Other special methods
	Camera() = delete;

	//	Methods
	static void Update(float elapsedSeconds);

	static void Reset();

	//	Setters
	static void SetShaking(bool isShaking);
	static void SetShakingFrameSeconds(float frameSeconds);
	static void SetSVGPath(const std::string& SVGPath);
	static void SetViewPort(const Rectf& viewPort);
	static void SetGameObjectToFollow(GameObject* const pGameObject);

	//	Getters
	static Rectf GetTransformedViewPort();
	static Point2f GetShakeOffsets();
	static float GetZoom();
	static bool IsShifting();

	static const std::vector<Rectf>& GetCameraZones();
	static int GetCurrentCameraZoneIndex();
	static int GetLastCameraZoneIndex();

private:
	static bool IsPointInRectangle(const Point2f& point, const Rectf& rectangle);

	static void DetermineCurrentZone();
	static void Follow();
	static void ClipToZone();
	static void ShiftToNextZone(float elapsedSeconds);
	static void Shake(float elapsedSeconds);

	static Rectf m_TRANSFORMED_VIEWPORT;
	static float m_ZOOM;

	static GameObject* m_pGAME_OBJECT_TO_FOLLOW;
	static bool m_STOP_FOLLOWING;

	static std::vector<Rectf> m_vCAMERA_ZONES;

	static bool m_IS_SHIFTING;
	static Vector2f m_SHIFT_VECTOR, m_SHIFTED_VECTOR;

	static int m_LAST_CAMERA_ZONE_INDEX, m_CURRENT_CAMERA_ZONE_INDEX;

	static bool m_IS_SHAKING;

	static float m_SHAKE_FRAME_SECONDS, m_SHAKE_ACCUMULATED_SECONDS;
	static float m_HORIZONTAL_SHAKE_OFFSET, m_VERTICAL_SHAKE_OFFSET;
};