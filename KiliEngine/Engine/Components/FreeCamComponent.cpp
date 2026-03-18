#include "FreeCamComponent.h"

#include "Engine/Tools/GameTime.h"
#include "Engine/Tools/Inputs.h"
#include "Engine/GameActor.h"

void FreeCamComponent::OnUpdate()
{
    if (Inputs::IsKeyPressed(SDLK_z))
    {
        mOwner->AddPosition(GetWorldTransform().GetTransform().GetForwardVector() * mSpeed * GameTime::DeltaTime);
    }
    else if (Inputs::IsKeyPressed(SDLK_s))
    {
        mOwner->AddPosition(GetWorldTransform().GetTransform().GetForwardVector() * -mSpeed * GameTime::DeltaTime);
    }

    if (Inputs::IsKeyPressed(SDLK_d))
    {
        mOwner->AddPosition(GetWorldTransform().GetTransform().GetRightVector() * mSpeed * GameTime::DeltaTime);
    }
    else if (Inputs::IsKeyPressed(SDLK_q))
    {
        mOwner->AddPosition(GetWorldTransform().GetTransform().GetRightVector() * -mSpeed * GameTime::DeltaTime);
    }

    if (const Vector2 mouseDelta = Inputs::GetMouseDelta(); mouseDelta != Vector2::zero)
    {
        Vector3 currentEuler = mOwner->GetWorldTransform().GetRotation().AsMatrixRow().GetEulerRotation();
        
        currentEuler.z += mouseDelta.x * mSensibility * GameTime::DeltaTime * MathUtils::DEG2RAD;
        currentEuler.y += mouseDelta.y * mSensibility * GameTime::DeltaTime * MathUtils::DEG2RAD;
        
        currentEuler.y = MathUtils::Clamp(currentEuler.y * MathUtils::RAD2DEG, -89.0f, 89.0f) * MathUtils::DEG2RAD;

        const Quaternion newRotation = Quaternion(Vector3::unitZ, currentEuler.z) * Quaternion(Vector3::unitY, currentEuler.y) * Quaternion(Vector3::unitX, currentEuler.x); 
        mOwner->SetRotation(newRotation);
    }
}

FreeCamComponent::FreeCamComponent(GameActor* pOwner, const float pSpeed, const float pSensibility) :
    ActorComponent(pOwner, Transform::Origin),
    mSpeed(pSpeed), mSensibility(pSensibility)
{
    SetName("FreeCamComponent");
}
