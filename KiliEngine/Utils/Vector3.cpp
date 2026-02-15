#include "Vector3.h"
#include "Matrix4.h"
#include "Quaternion.h"

const Vector3 Vector3::zero(0.0f, 0.0f, 0.f);
const Vector3 Vector3::unitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::unitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::unitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::negUnitX(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::negUnitY(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::negUnitZ(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::infinity(Maths::INFINITY_POS, Maths::INFINITY_POS, Maths::INFINITY_POS);
const Vector3 Vector3::negInfinity(Maths::INFINITY_NEG, Maths::INFINITY_NEG, Maths::INFINITY_NEG);

void Vector3::Set(float xP, float yP, float zP)
{
	x = xP;
	y = yP;
	z = zP;
}

float Vector3::LengthSq() const
{
	return (x * x + y * y + z * z);
}

float Vector3::Length() const
{
	return (Maths::Sqrt(LengthSq()));
}

void Vector3::Normalize()
{
	float len = Length();
	x /= len;
	y /= len;
	z /= len;
}



Vector3 Vector3::Transform(Vector3& vec, Matrix4& mat, float w)
{
	Vector3 retVal;
	retVal.x = vec.x * mat(0,0) + vec.y * mat(1,0) +
		vec.z * mat(2,0) + w * mat(3,0);
	retVal.y = vec.x * mat(0,1) + vec.y * mat(1,1) +
		vec.z * mat(2,1) + w * mat(3,1);
	retVal.z = vec.x * mat(0,2) + vec.y * mat(1,2) +
		vec.z * mat(2,2) + w * mat(3,2);
	//ignore w since we aren't returning a new value for it...
	return retVal;
}

Vector3 Vector3::TransformWithPerspDiv(Vector3& vec, Matrix4& mat, float w)
{
	Vector3 retVal;
	retVal.x = vec.x * mat(0,0) + vec.y * mat(1,0) +
		vec.z * mat(2,0) + w * mat(3,0);
	retVal.y = vec.x * mat(0,1) + vec.y * mat(1,1) +
		vec.z * mat(2,1) + w * mat(3,1);
	retVal.z = vec.x * mat(0,2) + vec.y * mat(1,2) +
		vec.z * mat(2,2) + w * mat(3,2);
	float transformedW = vec.x * mat(0,3) + vec.y * mat(1,3) +
		vec.z * mat(2,3) + w * mat(3,3);
	if (!Maths::NearZero(Maths::Abs(transformedW)))
	{
		transformedW = 1.0f / transformedW;
		retVal *= transformedW;
	}
	return retVal;
}


Vector3 Vector3::Transform(const Vector3& v, const Quaternion& q)
{
	// v + 2.0*cross(q.xyz, cross(q.xyz,v) + q.w*v);
	Vector3 qv(q.x, q.y, q.z);
	Vector3 retVal = v;
	retVal += 2.0f * Vector3::Cross(qv, Vector3::Cross(qv, v) + q.w * v);
	return retVal;
}
