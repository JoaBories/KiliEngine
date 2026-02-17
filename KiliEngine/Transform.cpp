#include "Transform.h"

#include "GameActor.h"

Transform::Transform() :
	mPosition(Vector3::zero), mRotation(Vector3::zero), mScale(Vector3::unit)
{
}

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) :
	mPosition(position), mRotation(rotation), mScale(scale)
{
}

WorldTransform::WorldTransform() :
	Transform(), mNeedUpdate(true)
{
}

WorldTransform::WorldTransform(Transform transform):
	Transform(transform), mNeedUpdate(true)
{
}

WorldTransform::WorldTransform(Vector3 position, Vector3 rotation, Vector3 scale) :
	Transform(position, rotation, scale), mNeedUpdate(true)
{
}

void WorldTransform::RecomputeWorldTransformMatrix()
{
	if (!mNeedUpdate) return;
	mNeedUpdate = false;
	mWorldTransformMatrix = Matrix4Row::CreateScale(mScale);
	mWorldTransformMatrix *= Matrix4Row::CreateRotationX(mRotation.x);
	mWorldTransformMatrix *= Matrix4Row::CreateRotationY(mRotation.y);
	mWorldTransformMatrix *= Matrix4Row::CreateRotationZ(mRotation.z);
	mWorldTransformMatrix *= Matrix4Row::CreateTranslation(mPosition);
}

Matrix4Row WorldTransform::GetWorldTransformMatrix()
{
	RecomputeWorldTransformMatrix();
	return mWorldTransformMatrix;
}
