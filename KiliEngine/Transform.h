#pragma once

#include "Utils/Vector3.h"
#include "Utils/Matrix4Row.h"
#include "Utils/Quaternion.h"

class Transform
{
protected:
	Vector3 mPosition;
	Vector3 mRotation; //Quaternion mRotation
	Vector3 mScale;

public:
	Transform();
	Transform(Vector3 position, Vector3 rotation, Vector3 scale);

	inline Vector3 GetPosition() const { return mPosition; };
	inline Vector3 GetRotation() const { return mRotation; };
	inline Vector3 GetScale() const { return mScale; };

	inline virtual void SetPosition(const Vector3& newPos) { mPosition = newPos; };
	inline virtual void AddPosition(const Vector3& movement) { mPosition += movement; };

	inline virtual void SetRotation(const Vector3& newRot) { mRotation = newRot; };
	inline virtual void AddRotation(const Vector3& rotation) { mRotation += rotation; };

	inline virtual void SetScale(const Vector3& newScale) { mScale = newScale; };
};

class WorldTransform : public Transform
{
private :
	Matrix4Row mWorldTransformMatrix;
	bool mNeedUpdate;

public :
	WorldTransform();
	WorldTransform(Transform transform);
	WorldTransform(Vector3 position, Vector3 rotation, Vector3 scale);

	inline void SetPosition(const Vector3& newPos) override {
		mPosition = newPos;
		mNeedUpdate = true;
	};

	inline void AddPosition(const Vector3& movement) override {
		mPosition += movement;
		mNeedUpdate = true;
	};

	inline void SetRotation(const Vector3& newRot) override {
		mRotation = newRot;
		mNeedUpdate = true;
	};

	inline void AddRotation(const Vector3& rotation) override {
		mRotation += rotation;
		mNeedUpdate = true;
	};

	inline void SetScale(const Vector3& newScale) override {
		mScale = newScale;
		mNeedUpdate = true;
	};

	void RecomputeWorldTransformMatrix();
	Matrix4Row GetWorldTransformMatrix();
};

