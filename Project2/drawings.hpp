#pragma once

class drawings
{
public:
	class Vector3;
	bool IsBehindCamera(const SDK::APlayerController* PlayerController, const SDK::FVector& Point);
	bool IsOnScreen(const ImVec2& Point);
	void Box3D(SDK::APlayerController* PlayerController, SDK::FVector Origin, SDK::FVector Extents);
};