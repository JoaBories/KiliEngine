#include "BowlingBall.h"

#include "Engine/Tools/GameTime.h"
#include "Engine/Tools/Inputs.h"
#include "Engine/Scene/SceneManager.h"

void BowlingBall::UpdateArrow() const
{
    mArrow->SetLocalScale(Vector3::unit * 6.0f * mForce);
}

void BowlingBall::OnLateUpdate()
{
    if (!mLaunched)
    {
        if (Inputs::IsKeyPressed(SDLK_z))
        {
            mForce = MathUtils::Clamp(mForce + GameTime::DeltaTime, MinForce, MaxForce);
            UpdateArrow();
        }
        else if (Inputs::IsKeyPressed(SDLK_s))
        {
            mForce = MathUtils::Clamp(mForce - GameTime::DeltaTime, MinForce, MaxForce);
            UpdateArrow();
        }

        if (Inputs::IsKeyPressed(SDLK_d))
        {
            Vector3 newPos = GetWorldTransform().GetPosition();
            newPos.y = MathUtils::Clamp(newPos.y + 5 * GameTime::DeltaTime, -MaxY, MaxY);
            SetPosition(newPos);
        }
        else if (Inputs::IsKeyPressed(SDLK_q))
        {
            Vector3 newPos = GetWorldTransform().GetPosition();
            newPos.y = MathUtils::Clamp(newPos.y - 5 * GameTime::DeltaTime, -MaxY, MaxY);
            SetPosition(newPos);
        }
        
        if (Inputs::IsKeyPressed(SDLK_a))
        {
            mYaw = MathUtils::Clamp(mYaw - 5 * GameTime::DeltaTime, -MaxYaw, MaxYaw);
            SetRotation(Quaternion(Vector3::unitZ, mYaw * MathUtils::DEG2RAD));
        }
        else if (Inputs::IsKeyPressed(SDLK_e))
        {
            mYaw = MathUtils::Clamp(mYaw + 5 * GameTime::DeltaTime, -MaxYaw, MaxYaw);
            SetRotation(Quaternion(Vector3::unitZ, mYaw * MathUtils::DEG2RAD));
        }
        
        if (Inputs::IsKeyPressed(SDLK_SPACE))
        {
            mLaunched = true;
            mRb->AddVelocity(GetWorldTransform().GetTransform().GetForwardVector() * mForce * 10.0f);
            SceneManager::ActiveScene()->GetActorOfClass<Camera>()->AddPosition(Vector3(0,0,-2));
            mArrow->SetActive(false);
        }
    }
    else
    {
        Rotate(GetWorldTransform().GetTransform().GetRightVector(), 5.0f * GameTime::DeltaTime);
    }

    if (GetWorldTransform().GetPosition().z <= -10.0f)
    {
        SceneManager::ReloadScene();
    }
    
}

void BowlingBall::OnStart()
{
    for (MeshComponent* mc : GetComponents<MeshComponent>())
    {
        if (mc->GetShaderOverride() == "Decals") mArrow = mc;
        else mBall = mc;
    }
    UpdateArrow();
    
    mRb = GetComponent<RigidBody>();
}
