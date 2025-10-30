#pragma once
#include "SDK/Engine_classes.hpp"

#include <algorithm>






/* Forward declaration of Unreal.h struct. */
namespace Unreal { struct Transform; }






class Math
{
public:
	static SDK::FVector Vector_Normalize(const SDK::FVector& vector);
	static float Vector_Distance(const SDK::FVector& A, const SDK::FVector& B);


	static SDK::FRotator Quat_ToRotator(const SDK::FQuat& quat);
	static SDK::FQuat Rotator_ToQuat(const SDK::FRotator& rotator);


	static Unreal::Transform F_ToUnrealTransform(const SDK::FTransform& fTransform);
	static SDK::FTransform Unreal_ToFTransform(const Unreal::Transform& unrealTransform);


	static uint32_t ColorFloat4_ToU32(const float color[4]);


	static uint32_t Seconds_ToMilliseconds(const double& seconds);


	static inline const float PI   = 3.14f;
	static inline const float DTR  = PI / 180.0f; // Degrees-to-radians factor.
	static inline const float RTD  = 180.0f / PI; // Radians-to-degrees factor.
	static inline const float TINY = 1e-8f;		  // Small epsilon to avoid divide-by-zero in normalization.
};

