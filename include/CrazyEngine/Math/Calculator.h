#ifndef CRAZYENGINE_MATH_CALCULATOR_H_
#define CRAZYENGINE_MATH_CALCULATOR_H_

#include <cstdint>

namespace CrazyEngine
{
    class Calculator
    {
    public:
        static constexpr float Pi = 3.1415927f;
        static constexpr double PiDouble = 3.141592653589793;
        static constexpr float PiOver2 = 1.5707963f;
        static constexpr float PiOver3 = 1.0471976f;
        static constexpr float PiOver4 = 0.7853982f;
        static constexpr float Tau = 6.2831853f;
        static constexpr double TauDouble = 6.283185307179586;

        static constexpr float E = 2.7182818f;
        static constexpr double EDouble = 2.718281828459045;

        static constexpr float GoldenRatio = 1.6180339f;
        static constexpr double GoldenRatioDouble = 1.618033988749894;

        static constexpr float Root2 = 1.4142135f;
        static constexpr double Root2Double = 1.414213562373095;

        static float DegreesToRadians(float degrees);
        static float RadiansToDegrees(float radians);
        static float WrapAngle(float angle);
        static float WrapAngle180(float angle);
        static float Lerp(float a, float b, float t);
        static float Clamp(const float value, const float lower, const float upper);

        static std::uint32_t Max(const std::uint32_t a, const std::uint32_t b);
        static std::uint32_t Min(const std::uint32_t a, const std::uint32_t b);
        static float Maxf(const float a, const float b);
        static float Minf(const float a, const float b);

        static std::uint32_t Mod(std::int32_t a, std::int32_t m);
    };
}

#endif