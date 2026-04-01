#pragma once
#include "Components/ActorComponent.h"

class Camera : public ActorComponent
{
private:
    Matrix4Row mViewMatrix;
    Matrix4Row mProjMatrix;

    float mFov;
    float mNearPane;
    float mFarPane;
    
protected:
    void OnStart() override;
    void OnUpdate() override;

public:
    Camera() = delete;
    explicit Camera(GameActor* pOwner, const Transform& pTransform, float pFov = 70.0f, float pNear = 0.1f, float pFar = 1000.0f);

    Matrix4Row GetViewMatrix() const { return mViewMatrix; }
    Matrix4Row GetProjMatrix() const { return mProjMatrix; }
    Matrix4Row GetViewProjMatrix() const { return  mViewMatrix * mProjMatrix; }

    float GetFov() const { return mFov; }
    float GetNearPane() const { return mNearPane; }
    float GetFarPane() const { return mFarPane; }

    void SetFov(const float pFov) { mFov = pFov; }
    void SetNearPane(const float pNear) { mNearPane = pNear; }
    void SetFarPane(const float pFar) { mFarPane = pFar; }

    void UseCamera();
};
