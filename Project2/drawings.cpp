#include "includes.hpp"

class drawings::Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	inline float Length()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}

};


SDK::FVector RotationToVector(const SDK::FRotator& Rotation)
{
	float M_PI = 3.14159265358979323846;

	float CP = cos(Rotation.Pitch * M_PI / 180.0f);
	float SP = sin(Rotation.Pitch * M_PI / 180.0f);
	float CY = cos(Rotation.Yaw * M_PI / 180.0f);
	float SY = sin(Rotation.Yaw * M_PI / 180.0f);

	return SDK::FVector(CP * CY, CP * SY, SP);
}

bool drawings::IsBehindCamera(const SDK::APlayerController* PlayerController, const SDK::FVector& Point)
{
	SDK::FVector CameraLocation;
	SDK::FRotator CameraRotation;
	PlayerController->GetActorEyesViewPoint(&CameraLocation, &CameraRotation);

	SDK::FVector ForwardVector = RotationToVector(CameraRotation);
	SDK::FVector PointDirection = Point - CameraLocation;

	return ForwardVector.Dot(PointDirection) < 0;
}

bool drawings::IsOnScreen(const ImVec2& Point)
{
	auto& io = ImGui::GetIO();

	return (Point.x >= -20 && Point.x <= io.DisplaySize.x+20 && Point.y >= -20 && Point.y <= io.DisplaySize.y+20);
}

void drawings::Box3D(SDK::APlayerController* PlayerController, SDK::FVector Origin, SDK::FVector Extents)
{
	std::pair<UC::int32, UC::int32> ViewPortSize;

	PlayerController->GetViewportSize(&ViewPortSize.first, &ViewPortSize.second);

	std::vector<SDK::FVector> Points(8);
	std::vector<ImVec2> ScreenPoints(8);

	Points[0] = Origin - Extents;
	Points[1] = Origin + SDK::FVector(Extents.X, -Extents.Y, -Extents.Z);
	Points[2] = Origin + SDK::FVector(Extents.X, Extents.Y, -Extents.Z);
	Points[3] = Origin + SDK::FVector(-Extents.X, Extents.Y, -Extents.Z);

	Points[4] = Points[0] + SDK::FVector(0, 0, 2 * Extents.Z);
	Points[5] = Points[1] + SDK::FVector(0, 0, 2 * Extents.Z);
	Points[6] = Points[2] + SDK::FVector(0, 0, 2 * Extents.Z);
	Points[7] = Points[3] + SDK::FVector(0, 0, 2 * Extents.Z);

	for (int i = 0; i < 8; ++i) {
		SDK::FVector2D ScreenPosition;
		if (PlayerController->ProjectWorldLocationToScreen(Points[i], &ScreenPosition, false)) {
			ScreenPoints[i] = ImVec2(ScreenPosition.X, ScreenPosition.Y);
		}
	}

	ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
	for (int i = 0; i < 4; ++i) {
		if ((IsOnScreen(ScreenPoints[i]) || IsOnScreen(ScreenPoints[(i + 1) % 4])) &&
			(!IsBehindCamera(PlayerController, Points[i]) && !IsBehindCamera(PlayerController, Points[(i + 1) % 4]))) {
			DrawList->AddLine(ScreenPoints[i], ScreenPoints[(i + 1) % 4], ImColor(255, 255, 255));
		}
		if ((IsOnScreen(ScreenPoints[i + 4]) || IsOnScreen(ScreenPoints[(i + 1) % 4 + 4])) &&
			(!IsBehindCamera(PlayerController, Points[i + 4]) && !IsBehindCamera(PlayerController, Points[(i + 1) % 4 + 4]))) {
			DrawList->AddLine(ScreenPoints[i + 4], ScreenPoints[(i + 1) % 4 + 4], ImColor(255, 0, 0));
		}
		if ((IsOnScreen(ScreenPoints[i]) || IsOnScreen(ScreenPoints[i + 4])) &&
			(!IsBehindCamera(PlayerController, Points[i]) && !IsBehindCamera(PlayerController, Points[i + 4]))) {
			DrawList->AddLine(ScreenPoints[i], ScreenPoints[i + 4], ImColor(255, 255, 0));
		}
	}
}