#include "Transform.h"

#include "GameActor.h"

Transform::Transform() :
	mPosition(Vector3::zero), mRotation(Vector3::zero), mScale(Vector3::unitX),
	mNeedUpdate(true)
{
}

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) :
	mPosition(position), mRotation(rotation), mScale(scale),
	mNeedUpdate(true)
{
}

void Transform::RecomputeWorldTransform()
{
	if (!mNeedUpdate) return;
	mNeedUpdate = false;
	mWorldTransform = Matrix4Row::CreateScale(mScale);
	mWorldTransform *= Matrix4Row::CreateRotationX(mRotation.x);
	mWorldTransform *= Matrix4Row::CreateRotationY(mRotation.y);
	mWorldTransform *= Matrix4Row::CreateRotationZ(mRotation.z);
	mWorldTransform *= Matrix4Row::CreateTranslation(mPosition);
}