#include "Transform.h"

const Transform Transform::Origin = Transform(Vector3(), Quaternion(Vector3(1.0f,0.0f,0.0f), 0), Vector3(1.0f,1.0f,1.0f));

Transform::Transform() :
	mPosition(Vector3::zero), mRotation(Quaternion(Vector3::unitZ, 0)), mScale(Vector3::unit)
{
}

Transform::Transform(const Vector3& pPosition, const Quaternion& pRotation, const Vector3& pScale) :
	mPosition(pPosition), mRotation(pRotation), mScale(pScale)
{
}

void Transform::AddRotation(const Quaternion& pRotation)
{
	mRotation = Quaternion::Concatenate(mRotation, pRotation);
	mRotation.Normalize();
}

void Transform::Rotate(const Vector3& pAxis, const float pAngle)
{
	const Quaternion increment(pAxis, pAngle);
	mRotation = Quaternion::Concatenate(mRotation, increment);
}

WorldTransform::WorldTransform() :
	mTransform(Transform::Origin), mNeedUpdate(true)
{
}

WorldTransform::WorldTransform(const Transform& pTransform):
	mTransform(pTransform), mNeedUpdate(true)
{
}

WorldTransform::WorldTransform(const Vector3& pPosition, const Quaternion& pRotation, const Vector3& pScale) :
	mTransform(pPosition, pRotation, pScale), mNeedUpdate(true)
{
}

void WorldTransform::RecomputeWorldTransformMatrix() const
{
	if (!mNeedUpdate) return;
	mNeedUpdate = false;
	mWorldTransformMatrix = Matrix4Row::CreateScale(mTransform.GetScale());
	mWorldTransformMatrix *= Matrix4Row::CreateFromQuaternion(mTransform.GetRotation());
	mWorldTransformMatrix *= Matrix4Row::CreateTranslation(mTransform.GetPosition());
}

Matrix4Row WorldTransform::GetWorldTransformMatrix() const
{
	RecomputeWorldTransformMatrix();
	return mWorldTransformMatrix;
}
