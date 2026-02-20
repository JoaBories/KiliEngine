#pragma once

#include "Utils/Vector3.h"
#include "Utils/Matrix4Row.h"
#include "Utils/Quaternion.h"

class Transform
{
protected:
	Vector3 mPosition;
	Quaternion mRotation; //Quaternion mRotation
	Vector3 mScale;

public:
	Transform();
	Transform(const Vector3& pPosition, const Quaternion& pRotation, const Vector3& pScale);

	static const Transform Origin;

	[[nodiscard]] Vector3 GetPosition() const { return mPosition; }
	[[nodiscard]] Quaternion GetRotation() const { return mRotation; }
	[[nodiscard]] Vector3 GetScale() const { return mScale; }

	[[nodiscard]] Vector3 GetForwardVector() const { return Vector3::Transform(Vector3::unitX, mRotation);}
	[[nodiscard]] Vector3 GetUpVector() const {return Vector3::Transform(Vector3::unitZ, mRotation);}
	[[nodiscard]] Vector3 GetRightVector() const {return Vector3::Transform(Vector3::unitY, mRotation);}

	void SetPosition(const Vector3& pNewPos) { mPosition = pNewPos; }
	void AddPosition(const Vector3& pMovement) { mPosition += pMovement; }

	void SetRotation(const Quaternion& pNewRot) { mRotation = pNewRot; }
	void AddRotation(const Quaternion& pRotation) { mRotation = Quaternion::Concatenate(mRotation, pRotation); }

	void SetScale(const Vector3& pNewScale) { mScale = pNewScale; }
};

class WorldTransform //todo remove parenting
{
private :
	Transform mTransform;
	mutable Matrix4Row mWorldTransformMatrix;
	mutable bool mNeedUpdate;

public :
	
	WorldTransform();
	explicit WorldTransform(const Transform& pTransform);
	WorldTransform(const Vector3& pPosition, const Quaternion& pRotation, const Vector3& pScale);

	[[nodiscard]] Vector3 GetPosition() const { return mTransform.GetPosition(); }
	[[nodiscard]] Quaternion GetRotation() const { return mTransform.GetRotation(); }
	[[nodiscard]] Vector3 GetScale() const { return mTransform.GetScale(); }

	[[nodiscard]] const Transform& GetTransform() const { return mTransform; }
	
	void SetPosition(const Vector3& pNewPos) {
		mTransform.SetPosition(pNewPos);
		mNeedUpdate = true;
	}

	void AddPosition(const Vector3& pMovement) {
		mTransform.AddPosition(pMovement);
		mNeedUpdate = true;
	}

	void SetRotation(const Quaternion& pNewRot) {
		mTransform.SetRotation(pNewRot);
		mNeedUpdate = true;
	}

	void AddRotation(const Quaternion& pRotation) {
		mTransform.AddRotation(pRotation);
		mNeedUpdate = true;
	}

	void SetScale(const Vector3& pNewScale) {
		mTransform.SetScale(pNewScale);
		mNeedUpdate = true;
	}

	void RecomputeWorldTransformMatrix() const;
	[[nodiscard]] Matrix4Row GetWorldTransformMatrix() const;
};

