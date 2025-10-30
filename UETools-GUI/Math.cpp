#include "Math.h"
#include "Unreal.h"






SDK::FVector Math::Vector_Normalize(const SDK::FVector& vector)
{
    float vectorLengthSquared = (vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z);
    if (vectorLengthSquared < 0.01f)
        return SDK::FVector();

    float vectorLengthInverted = 1.0f / sqrt(vectorLengthSquared);
    return vector * vectorLengthInverted;
}


float Math::Vector_Distance(const SDK::FVector& A, const SDK::FVector& B)
{
    const float X_Distance = A.X - B.X;
    const float Y_Distance = A.Y - B.Y;
    const float Z_Distance = A.Z - B.Z;

    return std::sqrtf(X_Distance * X_Distance + Y_Distance * Y_Distance + Z_Distance * Z_Distance);
}




SDK::FRotator Math::Quat_ToRotator(const SDK::FQuat& quat)
{
    /* Ensure quaternion is normalized before conversion. */
    SDK::FQuat q = quat;
    const float normSq = q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W;
    if (normSq > TINY)
    {
        const float invLen = 1.0f / std::sqrt(normSq);
        q.X *= invLen;
        q.Y *= invLen;
        q.Z *= invLen;
        q.W *= invLen;
    }
    else
    {
        /* Fall back to identity quaternion. */
        q = SDK::FQuat{ 0.0f, 0.0f, 0.0f, 1.0f };
    }

    /* Convert quaternion to Euler angles (in Z(Yaw)->Y(Pitch)->X(Roll) order). */
    SDK::FRotator rotator;

    /* Compute roll (X) using standard quaternion-to-Euler formulas. */
    const float sinr_cosp = 2.0f * (q.W * q.X + q.Y * q.Z);
    const float cosr_cosp = 1.0f - 2.0f * (q.X * q.X + q.Y * q.Y);
    rotator.Roll = std::atan2(sinr_cosp, cosr_cosp);

    /* Compute sin(pitch) value; clamp to [-1,1] to avoid invalid asin() results due to precision errors. */
    const float sinp = 2.0f * (q.W * q.Y - q.Z * q.X);
    if (std::fabs(sinp) >= 1.0f)
    {
        /* Use 90 degrees if out of range (gimbal lock). */
        rotator.Pitch = std::copysign(PI / 2.0f, sinp);
    }
    else
    {
        rotator.Pitch = std::asin(sinp);
    }

    /* Compute yaw (Z) using standard quaternion-to-Euler formulas. */
    const float siny_cosp = 2.0f * (q.W * q.Z + q.X * q.Y);
    const float cosy_cosp = 1.0f - 2.0f * (q.Y * q.Y + q.Z * q.Z);
    rotator.Yaw = std::atan2(siny_cosp, cosy_cosp);

    /* Convert radians back to degrees. */
    rotator.Roll  *= RTD; // X
    rotator.Pitch *= RTD; // Y
    rotator.Yaw   *= RTD; // Z

    return rotator;
}

SDK::FQuat Math::Rotator_ToQuat(const SDK::FRotator& rotator)
{
    /* Convert degrees to radians and take half - angles, as quaternion uses half - angle trig. */
    const float halfRoll  = 0.5f * rotator.Roll * DTR;  // X
    const float halfPitch = 0.5f * rotator.Pitch * DTR; // Y
    const float halfYaw   = 0.5f * rotator.Yaw * DTR;   // Z

    /* Precompute sines / cosines of the half-angles. */
    const float sr = std::sin(halfRoll);
    const float cr = std::cos(halfRoll);

    const float sp = std::sin(halfPitch);
    const float cp = std::cos(halfPitch);

    const float sy = std::sin(halfYaw);
    const float cy = std::cos(halfYaw);

    /* Compose in Z(Yaw)->Y(Pitch)->X(Roll) order, matching Unreal's FRotator::Quaternion(). */
    SDK::FQuat quat;
    quat.W = cr * cp * cy + sr * sp * sy;
    quat.X = sr * cp * cy - cr * sp * sy; // X corresponds to Roll contribution
    quat.Y = cr * sp * cy + sr * cp * sy; // Y corresponds to Pitch contribution
    quat.Z = cr * cp * sy - sr * sp * cy; // Z corresponds to Yaw contribution

    /* Normalize to ensure a unit quaternion (important for downstream use like rotation / matrix). */
    const float normSq = quat.X * quat.X + quat.Y * quat.Y + quat.Z * quat.Z + quat.W * quat.W;
    if (normSq > TINY) // Check for nonsense input.
    {
        const float invLen = 1.0f / std::sqrt(normSq);
        quat.X *= invLen;
        quat.Y *= invLen;
        quat.Z *= invLen;
        quat.W *= invLen;
    }
    else
    {
        /* Fall back to identity quaternion. */
        quat = SDK::FQuat{ 0.0f, 0.0f, 0.0f, 1.0f };
    }

    return quat;
}




Unreal::Transform Math::F_ToUnrealTransform(const SDK::FTransform& fTransform)
{
    Unreal::Transform unrealTransform;
    unrealTransform.location = fTransform.Translation;
    unrealTransform.rotation = Math::Quat_ToRotator(fTransform.Rotation);
    unrealTransform.scale = fTransform.Scale3D;

    return unrealTransform;
}

SDK::FTransform Math::Unreal_ToFTransform(const Unreal::Transform& unrealTransform)
{
    SDK::FTransform fTransform;
    fTransform.Translation = unrealTransform.location;
    fTransform.Rotation = Math::Rotator_ToQuat(unrealTransform.rotation);
    fTransform.Scale3D = unrealTransform.scale;

    return fTransform;
}




uint32_t Math::ColorFloat4_ToU32(const float color[4])
{
    uint8_t r = (uint8_t)(std::clamp(color[0], 0.0f, 1.0f) * 255.0f + 0.5f);
    uint8_t g = (uint8_t)(std::clamp(color[1], 0.0f, 1.0f) * 255.0f + 0.5f);
    uint8_t b = (uint8_t)(std::clamp(color[2], 0.0f, 1.0f) * 255.0f + 0.5f);
    uint8_t a = (uint8_t)(std::clamp(color[3], 0.0f, 1.0f) * 255.0f + 0.5f);
    return (uint32_t)((a << 24) | (b << 16) | (g << 8) | (r));
}




uint32_t Math::Seconds_ToMilliseconds(const double& seconds)
{
    return static_cast<uint32_t>(std::lround(seconds * 1000.0));
}
