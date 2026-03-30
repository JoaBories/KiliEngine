#include "DoomPlayerController.h"
#include "Engine/Tools/Inputs.h"
#include "Engine/Tools/Log.h"

void DoomPlayerController::OnStart()
{
    mCamera = mOwner->GetComponent<Camera>();
}

void DoomPlayerController::OnUpdate()
{
    Vector2 mouseInput = Inputs::GetMouseDelta(); 
    mouseInput *= mSensibility * 0.05f;
    
    if (mouseInput != Vector2::zero)
    {
        Vector3 currentEuler = mCamera->GetLocalTransform().GetRotation().AsMatrixRow().GetEulerRotation();
        
        currentEuler.y += mouseInput.y * MathUtils::DEG2RAD;
        currentEuler.y = MathUtils::Clamp(currentEuler.y * MathUtils::RAD2DEG, -20.0f, 50.0f) * MathUtils::DEG2RAD;

        const Quaternion newRotation = Quaternion(Vector3::unitZ, currentEuler.z) * Quaternion(Vector3::unitY, currentEuler.y) * Quaternion(Vector3::unitX, currentEuler.x); 
        mCamera->SetLocalRotation(newRotation);
        
        mOwner->Rotate(Vector3::unitZ, mouseInput.x * MathUtils::DEG2RAD);
        Log::Info(std::to_string(mouseInput.x));
    }
}

DoomPlayerController::DoomPlayerController(GameActor* pOwner, const float pSpeed, const Vector2 pSensibility) :
    ActorComponent(pOwner, Transform::Origin), mSpeed(pSpeed), mSensibility(pSensibility)
{
    SetName("DoomController");
}
