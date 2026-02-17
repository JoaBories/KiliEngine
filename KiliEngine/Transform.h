#pragma once

#include "ActorComponent.h"

#include "Utils/Vector3.h"
#include "Utils/Matrix4Row.h"
#include "Utils/Quaternion.h"

class Transform
{
private :
	Vector3 mPosition;
	Vector3 mRotation; // Quaternion mRotation;
	Vector3 mScale;

	Matrix4Row mWorldTransform;
	bool mNeedUpdate;

public :

	Transform();
	Transform(Vector3 position, Vector3 rotation, Vector3 scale);

	inline Vector3 GetPosition() const	{ return mPosition; };
	inline Vector3 GetRotation() const	{ return mRotation; };
	inline Vector3 GetScale() const		{ return mScale; };

	inline void SetPosition(const Vector3& newPos) {
		mPosition = newPos;
		mNeedUpdate = true;
	};

	inline void AddPosition(const Vector3& movement) {
		mPosition += movement;
		mNeedUpdate = true;
	};

	inline void SetRotation(const Vector3& newRot) {
		mRotation = newRot;
		mNeedUpdate = true;
	};

	inline void AddRotation(const Vector3& rotation) {
		mRotation += rotation;
		mNeedUpdate = true;
	};

	inline void SetScale(const Vector3& newScale) {
		mScale = newScale;
		mNeedUpdate = true;
	};

	void RecomputeWorldTransform();
};

