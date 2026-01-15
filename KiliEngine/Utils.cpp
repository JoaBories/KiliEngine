#include "Utils.h"

using Struct::Vector2;
using Struct::Rectangle2;

constexpr auto PI = 3.1415926536f;
constexpr auto EPSILON = 1e-8;
#define DEG2RAD PI/180
#define RAD2DEG 180/PI

#pragma region MathUtils

float MathUtils::OverlapOnAxis(const std::vector<Vector2>& a, const std::vector<Vector2>& b, Vector2 axis)
{
	return 0.0f;
}

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

#pragma region Rectangle

std::vector<Vector2> Rectangle2::getCorners() const
{
	std::vector<Vector2> corners(4);

	float cosA = cosf(rotation * DEG2RAD);
	float sinA = sinf(rotation * DEG2RAD);

	Vector2 right = { cosA, sinA };
	Vector2 up = { -sinA, cosA };

	corners[0] = center + right * halfSize.x + up * halfSize.y;
	corners[1] = center + right * -halfSize.x + up * halfSize.y;
	corners[3] = center + right * halfSize.x + up * -halfSize.y;
	corners[2] = center + right * -halfSize.x + up * -halfSize.y;

	return corners;
}

Vector2 Rectangle2::CheckAABB(const Rectangle2& other) const
{
	Vector2 aMin = { center.x - halfSize.x, center.y - halfSize.y };
	Vector2 aMax = { center.x + halfSize.x, center.y + halfSize.y };
	Vector2 bMin = { other.center.x - other.halfSize.x, other.center.y - other.halfSize.y };
	Vector2 bMax = { other.center.x + other.halfSize.x, other.center.y + other.halfSize.y };

	Vector2 overlap = Vector2::zero;

	if (aMin.x <= bMax.x && aMax.x >= bMin.x && aMin.y <= bMax.y && aMax.y >= bMin.y)
	{
		overlap.x = MathUtils::Min(aMax.x, bMax.x) - MathUtils::Max(aMin.x, bMin.x);
		overlap.y = MathUtils::Min(aMax.y, bMax.y) - MathUtils::Max(aMin.y, bMin.y);

		if (overlap.x < overlap.y) // Getting minimal overlap and his axis
		{
			overlap *= (center.x > other.center.x) ? Vector2::right : Vector2::left;
		}
		else
		{
			overlap *= (center.y > other.center.y) ? Vector2::up : Vector2::down;
		}
	}

	return overlap; // if overlap == Vector2::zero false else true
}

bool Rectangle2::ContainPoint(const Vector2& point) const
{
	Vector2 aMin = { center.x - halfSize.x, center.y - halfSize.y };
	Vector2 aMax = { center.x + halfSize.x, center.y + halfSize.y };

	//Same as AABB but there is just onepoint so the max and the min are the same
	return point.x >= aMin.x && point.x <= aMax.x && point.y >= aMin.y && point.y <= aMax.y;
}

Vector2 Rectangle2::CheckOBB(const Rectangle2& other) const
{
	Vector2 overlap = Vector2::zero;

	if (rotation == 0 && other.rotation == 0) // i can improve by using AABB for same rot rectangle or 90 rotated rectangles | i believe
	{
		overlap = CheckAABB(other); // more optimized
	}
	else
	{
		std::vector<Vector2> aCorners = getCorners();
		std::vector<Vector2> bCorners = other.getCorners();

		std::vector<Vector2> axes;

		axes.push_back((aCorners[0] - aCorners[1]).PerpendicularCW());	// 2 axes is enough for a rectangle
		axes.push_back((aCorners[1] - aCorners[2]).PerpendicularCW());

		axes.push_back((bCorners[0] - bCorners[1]).PerpendicularCW());
		axes.push_back((bCorners[1] - bCorners[2]).PerpendicularCW());

		float biggerAxisOverlap;

		for (const auto& axis : axes)									// Testing overlap on all axes. If there is overlap on all of them then there is collision
		{
			float axisOverlap = MathUtils::OverlapOnAxis(aCorners, bCorners, axis);

			if (axisOverlap < 0)
			{
				return overlap;
			}
			else if (axisOverlap < biggerAxisOverlap)							// Returning the minimal overlap and his axis 
			{
				biggerAxisOverlap = axisOverlap;
				overlap = axis * axisOverlap;
			}
		}
	}

	return overlap;
}

#pragma endregion

#pragma endregion

