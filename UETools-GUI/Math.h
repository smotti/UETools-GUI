#pragma once
#include "SDK/Engine_classes.hpp"

#include <algorithm>






class Math
{
public:
	static SDK::FVector NormalizeVector(const SDK::FVector& vector);
	static float Vector_Distance(const SDK::FVector& A, const SDK::FVector& B);


	static SDK::FQuat Rotator_ToQuat(const SDK::FRotator& rotator);


	static uint32_t ColorFloat4_ToU32(const float color[4]);


	static uint32_t Seconds_ToMilliseconds(const double& seconds);
};

