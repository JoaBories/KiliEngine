#pragma once
#include "GameActor.h"

class Camera : public GameActor
{
private:
    Matrix4Row mViewMatrix;
    Matrix4Row mProjMatrix;
    bool mProjNeedsUpdate;

    float mFov;
    float mNearPane;
    float mFarPane;
    
protected:
    void OnStart() override;
    void OnEarlyUpdate() override;
    void OnLateUpdate() override;

public:
    Camera();
    explicit Camera(const Transform& pTransform, float pFov = 70.0f, float pNear = 0.1f, float pFar = 1000.0f);

    Matrix4Row GetViewMatrix() const { return mViewMatrix; }
    Matrix4Row GetProjMatrix() const { return mProjMatrix; }
    Matrix4Row GetViewProjMatrix() const { return  mViewMatrix * mProjMatrix; }

    float GetFov() const { return mFov; }
    float GetNearPane() const { return mNearPane; }
    float GetFarPane() const { return mFarPane; }

    void SetFov(float pFov) { mFov = pFov; mProjNeedsUpdate = true; }
    void SetNearPane(float pNear) { mNearPane = pNear; mProjNeedsUpdate = true; }
    void SetFarPane(float pFar) { mFarPane = pFar; mProjNeedsUpdate = true; }

    void UseCamera();
};
