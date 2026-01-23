#pragma once

#include <limits>
#include <cmath>

namespace MathUtils {

	constexpr float PI = 3.1415926536f;
	constexpr float PI2 = PI * 2.0f;
	constexpr float DEG2RAD = PI/180;
	constexpr float RAD2DEG = 180/PI;
	constexpr double EPSILON = 1e-8;

	const float INFINITY_POS = std::numeric_limits<float>::infinity();
	const float INFINITY_NEG = -INFINITY_POS;


	template <typename T> inline  T Min(const T& a, const T& b)							{ return (a <= b) ? a : b; }
	template <typename T> inline  T Max(const T& a, const T& b)							{ return (a >= b) ? a : b; }
	template <typename T> inline  T Clamp(const T& value, const T& min, const T& max)	{ return Min(max, Max(value, min)); }

	inline float Cos(float angle)														{ return cosf(angle); }
	inline float Sin(float angle)														{ return sinf(angle); }
	inline float Tan(float angle)														{ return tanf(angle); }
	inline float ACos(float angle)														{ return acosf(angle); }
	inline float ATan2(float opposite, float adjacent)									{ return atan2f(opposite, adjacent); }
	inline float Cot(float angle)														{ return 1.0f / Tan(angle); }
	inline float Abs(float value)														{ return std::fabs(value); }
	inline float Sign(float value)														{ return (value > 0) ? 1.0f : (value < 0 ? -1.0f : 0.0f); }
	inline float Lerp(float a, float b, float t)										{ return a + (b - a) * Clamp(t, 0.0f, 1.0f); }
	inline float Sqrt(float val)														{ return sqrtf(val); }
	inline float Fmod(float numer, float denom)											{ return std::fmod(numer, denom); }
	inline int Round(float val)															{ return static_cast<int>(val); }

	inline bool NearZero(float value, float epsilon = EPSILON)							{ return Abs(value) <= epsilon;}

	bool NearlyEqual(const float a, const float b);
};
