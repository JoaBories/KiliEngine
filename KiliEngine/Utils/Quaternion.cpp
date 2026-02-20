#include "Quaternion.h"
#include "Matrix4Row.h"
#include <array>

using std::array;

const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion::Quaternion(float xP, float yP, float zP, float wP)
{
	Set(xP, yP, zP, wP);
}

Quaternion::Quaternion(const Vector3& axis, float angle)
{
	float scalar = MathUtils::Sin(angle / 2.0f);
	x = axis.x * scalar;
	y = axis.y * scalar;
	z = axis.z * scalar;
	w = MathUtils::Cos(angle / 2.0f);
}

void Quaternion::Set(float inX, float inY, float inZ, float inW)
{
	x = inX;
	y = inY;
	z = inZ;
	w = inW;
}

void Quaternion::Conjugate()
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}

void Quaternion::Normalize()
{
	float len = Length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}

Matrix4Row Quaternion::AsMatrixRow() const
{
	Matrix4Row m;

	const float xx = x * x;
	const float yy = y * y;
	const float zz = z * z;
	const float ww = w * w;
	const float xy = x * y;
	const float xz = x * z;
	const float xw = x * w;
	const float yz = y * z;
	const float yw = y * w;
	const float zw = z * w;

	m.mat[0][0] = 1.0f - 2.0f * (yy + zz);
	m.mat[0][1] =        2.0f * (xy - zw);
	m.mat[0][2] =        2.0f * (xz + yw);
	m.mat[0][3] =        0.0f;

	m.mat[1][0] =        2.0f * (xy + zw);
	m.mat[1][1] = 1.0f - 2.0f * (xx + zz);
	m.mat[1][2] =        2.0f * (yz - xw);
	m.mat[1][3] =        0.0f;

	m.mat[2][0] =        2.0f * (xz - yw);
	m.mat[2][1] =        2.0f * (yz + xw);
	m.mat[2][2] = 1.0f - 2.0f * (xx + yy);
	m.mat[2][3] =        0.0f;

	m.mat[3][0] =        0.0f;
	m.mat[3][1] =        0.0f;
	m.mat[3][2] =        0.0f;
	m.mat[3][3] =        1.0f;

	return m;
}
