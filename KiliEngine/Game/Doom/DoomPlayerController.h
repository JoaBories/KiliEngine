#pragma once
#include "Engine/Camera.h"
#include "Engine/CameraActor.h"
#include "Engine/Components/ActorComponent.h"

class DoomPlayerController : public ActorComponent
{
private:
    Camera* mCamera;
    float mSpeed;
    Vector2 mSensibility;
    
protected:
    void OnStart() override;
    void OnUpdate() override;
    
public:
    DoomPlayerController() = delete;
    DoomPlayerController(GameActor* pOwner, float pSpeed, Vector2 pSensibility);


};
