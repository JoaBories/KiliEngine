#pragma once
#include "Engine/Camera.h"
#include "Engine/CameraActor.h"
#include "Engine/Components/ActorComponent.h"
#include "Engine/Components/AnimatedComponent.h"
#include "Engine/Components/RigidBody.h"

class DoomPlayerController : public ActorComponent
{
private:
    float mSpeed;
    float mJumpForce;
    Vector2 mSensibility;
    
    bool mCanJump;
    float mJumpCooldown;
    
    Camera* mCamera;
    RigidBody* mRigidBody;
    AnimatedComponent* mSprite;

    Animation mPistol;
    Animation mShotgun;

    bool mHasShotgun;

    void ShootBullet(const Vector3& pPos, const Vector3& pDir, bool pShotgun) const;
    
protected:
    void OnStart() override;
    void OnUpdate() override;
    
public:
    DoomPlayerController() = delete;
    DoomPlayerController(GameActor* pOwner, float pSpeed, float pJumpForce, Vector2 pSensibility);


};
