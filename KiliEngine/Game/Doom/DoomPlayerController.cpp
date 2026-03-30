#include "DoomPlayerController.h"

#include "Engine/PhysicManager.h"
#include "Engine/Tools/GameTime.h"
#include "Engine/Tools/Inputs.h"
#include "Engine/Tools/Log.h"

void DoomPlayerController::OnStart()
{
    mCamera = mOwner->GetComponent<Camera>();
    mRigidBody = mOwner->GetComponent<RigidBody>();
}

void DoomPlayerController::OnUpdate()
{
    Vector2 mouseInput = Inputs::GetMouseDelta(); 
    mouseInput *= mSensibility * 0.05f;
    
    if (mouseInput != Vector2::zero)
    {
        Vector3 currentEuler = mCamera->GetLocalTransform().GetRotation().AsMatrixRow().GetEulerRotation();

        currentEuler.z += mouseInput.x * MathUtils::DEG2RAD;
        
        currentEuler.y += mouseInput.y * MathUtils::DEG2RAD;
        currentEuler.y = MathUtils::Clamp(currentEuler.y * MathUtils::RAD2DEG, -80.0f, 50.0f) * MathUtils::DEG2RAD;

        const Quaternion newRotation = Quaternion(Vector3::unitZ, currentEuler.z) * Quaternion(Vector3::unitY, currentEuler.y) * Quaternion(Vector3::unitX, currentEuler.x); 
        mCamera->SetLocalRotation(newRotation);
    }

    Vector2 movementInput = { 0.0f, 0.0f };

    if (Inputs::IsKeyPressed(SDLK_q)) movementInput.x = -1.0f;
    else if (Inputs::IsKeyPressed(SDLK_d)) movementInput.x = 1.0f;

    if (Inputs::IsKeyPressed(SDLK_z)) movementInput.y = 1.0f;
    else if (Inputs::IsKeyPressed(SDLK_s)) movementInput.y = -1.0f;

    if (movementInput != Vector2::zero)
    {
        movementInput.normalize();
        movementInput *= mSpeed * GameTime::DeltaTime;

        const Transform camTransform = mCamera->GetWorldTransform().GetTransform();

        const Vector3 forward = Vector3(camTransform.GetForwardVector().x,camTransform.GetForwardVector().y, 0.0f).Normalized();
        const Vector3 right = Vector3(camTransform.GetRightVector().x,camTransform.GetRightVector().y, 0.0f).Normalized();

        mRigidBody->AddVelocity(right * movementInput.x + forward * movementInput.y);
    }

    const Vector3 hitStart = mOwner->GetWorldTransform().GetPosition() - Vector3(0,0,2.0f);
    const Vector3 hitEnd = mOwner->GetWorldTransform().GetPosition() - Vector3(0,0,2.1f);

    if (Hit hit = PhysicManager::Linetrace(hitStart, hitEnd, GetOwner(), 1.0f))
    {
        mCanJump = true;
    }

    if (Inputs::IsKeyPressed(SDLK_SPACE) && mCanJump)
    {
        mCanJump = false;
        mRigidBody->AddVelocity(Vector3::unitZ * mJumpForce);
    }
}

DoomPlayerController::DoomPlayerController(GameActor* pOwner, const float pSpeed, float pJumpForce, const Vector2 pSensibility) :
    ActorComponent(pOwner, Transform::Origin), mSpeed(pSpeed), mJumpForce(pJumpForce), mSensibility(pSensibility),
    mCamera(nullptr), mRigidBody(nullptr)
{
    SetName("DoomController");
}
