#include "Transform.h"
#include "MathUtils.h"

using MathUtils::DEG2RAD;

Transform::Transform() :
	mPosition(Vector3::zero), mRotation(Quaternion(Vector3::unitZ, 0)), mScale(Vector3::unit)
{
}

Transform::Transform(Vector3 position, Quaternion rotation, Vector3 scale) :
	mPosition(position), mRotation(rotation), mScale(scale)
{
}

Vector3 Transform::GetForwardVector() const
{
	return Vector3::unitX;
}

Vector3 Transform::GetUpVector() const
{
	return Vector3::unitY;
}

Vector3 Transform::GetRightVector() const
{
	return Vector3::unitZ;
}

WorldTransform::WorldTransform() :
	Transform(), mNeedUpdate(true)
{
}

WorldTransform::WorldTransform(Transform transform):
	Transform(transform), mNeedUpdate(true)
{
}

WorldTransform::WorldTransform(Vector3 position, Quaternion rotation, Vector3 scale) :
	Transform(position, rotation, scale), mNeedUpdate(true)
{
}

void WorldTransform::RecomputeWorldTransformMatrix()
{
	if (!mNeedUpdate) return;
	mNeedUpdate = false;
	mWorldTransformMatrix = Matrix4Row::CreateScale(mScale);
	mWorldTransformMatrix *= Matrix4Row::CreateFromQuaternion(mRotation);
	mWorldTransformMatrix *= Matrix4Row::CreateTranslation(mPosition);
}

Matrix4Row WorldTransform::GetWorldTransformMatrix()
{
	RecomputeWorldTransformMatrix();
	return mWorldTransformMatrix;
}
