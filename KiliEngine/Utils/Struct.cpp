#include "Struct.h"

#include "CollisionUtils.h"
#include "MathUtils.h"

using namespace MathUtils;
using namespace Struct;

#include "Transform.h"

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


