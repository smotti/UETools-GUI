#pragma once
#include "SDK/Engine_classes.hpp"






class Math
{
public:
	static SDK::FVector NormalizeVector(const SDK::FVector& vector);


	static SDK::FQuat Rotator_ToQuat(const SDK::FRotator& rotator);


	static uint32_t Seconds_ToMilliseconds(const double& seconds);
};

