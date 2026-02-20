#include "Struct.h"
#include "MathUtils.h"

using namespace MathUtils;
using namespace Struct;

#include "Transform.h"

float Struct::OverlapOnAxis(const std::vector<Vector2>& a, const std::vector<Vector2>& b, Vector2 axis)
{
	float aMin = FLT_MAX, aMax = -FLT_MAX;
	float bMin = FLT_MAX, bMax = -FLT_MAX;

	for (const auto& point : a)
	{
		float projection = point.dot(axis);
		aMin = Min(projection, aMin);
		aMax = Max(projection, aMax);
	}

	for (const auto& point : b)
	{
		float projection = point.dot(axis);
		bMin = Min(projection, bMin);
		bMax = Max(projection, bMax);
	}

	return Min(aMax, bMax) - Max(aMin, bMin);
}

Vector2 Struct::Vector2FromRot(float rot)
{
	Vector2 vector = { sinf(rot * DEG2RAD), -cosf(rot * DEG2RAD) };
	return vector.normalized();
}

Vector2 Struct::Vect2FLerp(Vector2 a, Vector2 b, float t)
{
	return { Lerp(a.x, b.x, t), Lerp(a.y, b.y, t) };
}

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
	return (NearlyEqual(x, rm.x) && NearlyEqual(y, rm.y));
}

bool Vector2::operator<(const Vector2& rm) const
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

float Vector2::length() const
{
	return Sqrt(sqrLength());
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

void Struct::Vector2::normalize()
{
	if (*this == Vector2::zero)
	{
		x = 0.0f;
		y = 0.0f;
	}

	float l = length();
	x = x / l;
	y = y / l;
}

void Vector2::clamp(float min, float max)
{
	float sqrL = sqrLength();

	if (sqrL < min * min)
	{
		normalize();
		*this *= min;
	}
	else
	{
		if (sqrL > max * max)
		{
			normalize();
			*this *= max;
		}
	}
}

Vector2 Struct::Vector2::rotated(float angle)
{
	float c = cos(angle);
	float s = sin(angle);

	return {
		x * c - y * s,
		x * s + y * c
	};
}

#pragma endregion

#pragma region Rectangle

const Rectangle Rectangle::Null = Rectangle{ Vector2(0, 0), Vector2(0, 0), 0.0f };

std::vector<Vector2> Rectangle::getCorners() const
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

float Struct::Rectangle::GetRadius() const
{
	return halfSize.length();
}

Vector2 Rectangle::CheckAABB(const Rectangle& other) const
{
	Vector2 aMin = { center.x - halfSize.x, center.y - halfSize.y };
	Vector2 aMax = { center.x + halfSize.x, center.y + halfSize.y };
	Vector2 bMin = { other.center.x - other.halfSize.x, other.center.y - other.halfSize.y };
	Vector2 bMax = { other.center.x + other.halfSize.x, other.center.y + other.halfSize.y };

	Vector2 overlap = Vector2::zero;

	if (aMin.x <= bMax.x && aMax.x >= bMin.x && aMin.y <= bMax.y && aMax.y >= bMin.y)
	{
		overlap.x = Min(aMax.x, bMax.x) - Max(aMin.x, bMin.x);
		overlap.y = Min(aMax.y, bMax.y) - Max(aMin.y, bMin.y);

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

bool Rectangle::ContainPoint(const Vector2& point) const
{
	Vector2 aMin = { center.x - halfSize.x, center.y - halfSize.y };
	Vector2 aMax = { center.x + halfSize.x, center.y + halfSize.y };

	//Same as AABB but there is just onepoint so the max and the min are the same
	return point.x >= aMin.x && point.x <= aMax.x && point.y >= aMin.y && point.y <= aMax.y;
}

Rectangle Rectangle::toObjectSpace(const Transform& pTransform) const
{
	Rectangle result = *this;
	result.center.x += pTransform.GetPosition().x;
	result.center.y += pTransform.GetPosition().y;
	result.halfSize.x *= pTransform.GetScale().x;
	result.halfSize.y *= pTransform.GetScale().y;
	result.rotation += pTransform.GetRotation().z;
	return result;
}

Vector2 Rectangle::CheckOBB(const Rectangle& other) const
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

		float biggerAxisOverlap = FLT_MIN;

		for (const auto& axis : axes)									// Testing overlap on all axes. If there is overlap on all of them then there is collision
		{
			float axisOverlap = OverlapOnAxis(aCorners, bCorners, axis);

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

#pragma region Transform

Vector2 Struct::Transform2D::Up() const
{
	return Vector2FromRot(rotation);
}

Vector2 Struct::Transform2D::Right() const
{
	return Up().PerpendicularCCW();
}

const Transform2D Transform2D::one = { Vector2::zero, Vector2::one, 0 };

#pragma endregion

#pragma endregion


