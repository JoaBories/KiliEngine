#include "FpsCameraComponent.h"

#include "Engine/Tools/Inputs.h"
#include "Engine/GameActor.h"

void FpsCameraComponent::OnUpdate()
{
    Vector3 newPos = mPlayer->GetWorldTransform().GetPosition() + mPositionOffset;
    mOwner->SetPosition(newPos);
    
    const Vector2 mouseDelta = Inputs::GetMouseDelta();
    Vector3 currentEuler = mOwner->GetWorldTransform().GetRotation().AsMatrixRow().GetEulerRotation();
    Vector3 playerEuler = mPlayer->GetWorldTransform().GetRotation().AsMatrixRow().GetEulerRotation();
    
    currentEuler.y += mouseDelta.y * mSensibility * MathUtils::DEG2RAD * 0.01f;
    currentEuler.y = MathUtils::Clamp(currentEuler.y, -80.0f * MathUtils::DEG2RAD, 80.0f * MathUtils::DEG2RAD);

    currentEuler.x = playerEuler.x;

    const Quaternion newRotation = Quaternion(Vector3::unitZ, currentEuler.z) * Quaternion(Vector3::unitY, currentEuler.y) * Quaternion(Vector3::unitX, currentEuler.x); 
    mOwner->SetRotation(newRotation);
}

FpsCameraComponent::FpsCameraComponent(GameActor* pOwner, const float pSensibility, const Vector3& pPositionOffset) :
    ActorComponent(pOwner, Transform::Origin),
    mSensibility(pSensibility), mPositionOffset(pPositionOffset),
    mPlayer(nullptr)
{
    SetName("FpsCameraComponent");
}
