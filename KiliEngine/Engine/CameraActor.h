#pragma once
#include "GameActor.h"
#include "Camera.h"

class CameraActor : public GameActor
{
private:
    Camera* mCamera;
    
public:
    CameraActor(const Transform& pTransform, float pFov, float pNear, float pFar);
    
    Camera* GetCamera() const { return mCamera; }
    
};
