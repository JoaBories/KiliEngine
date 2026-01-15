#include "Utils.h"

using Struct::Vector2;

#define PI 3.1415926536f
#define DEG2RAD PI/180
#define RAD2DEG 180/PI
#define EPSILON 1e-8

#pragma region MathUtils

Vector2 MathUtils::Vect2FromRot(float rot)
{
	Vector2 vector = { cosf(rot * DEG2RAD), sinf(rot * DEG2RAD) };
	return vector.normalized();
}

bool MathUtils::NearlyEqual(const float a, const float b)
{
	return Abs(a - b) < EPSILON;
}

#pragma endregion

#pragma region Structs

#pragma region Vectors

//Vect2F

const Vector2 Vector2::zero = { 0,0 };
const Vector2 Vector2::one = { 1,1 };
const Vector2 Vector2::up = { 0,1 };
const Vector2 Vector2::down = { 0,-1 };
const Vector2 Vector2::right = { 1,0 };
const Vector2 Vector2::left = { -1,0 };

bool Vector2::operator==(const Vector2& rm) const
{
	return (MathUtils::NearlyEqual(x, rm.x) && MathUtils::NearlyEqual(y, rm.y));
}

bool Struct::Vector2::operator<(const Vector2& rm) const
{
	return (sqrLength()) < rm.sqrLength();
}

float Vector2::getRot() const
{
	if (x == 0 && y == 0) return 0;

	float a = atan2f(y, x) * RAD2DEG;
	if (a < 0) a += 360.0f;

	return a;
}

Vector2 Vector2::normalized() const
{
	if (*this == Vector2::zero)
	{
		return Vector2::zero;
	}

	float l = length();
	return { x / l, y / l };
}

Vector2 Vector2::clamp(float min, float max) const
{
	float sqrL = sqrLength();

	if (sqrL < min * min)
	{
		return normalized() * min;
	}
	else
	{
		if (sqrL > max * max)
		{
			return normalized() * max;
		}
		else
		{
			return *this;
		}
	}
}

#pragma endregion

#pragma endregion