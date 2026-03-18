#include "Player.h"
#include "Engine/Tools/GameTime.h"
#include "Engine/Tools/Inputs.h"

void Player::OnStart()
{
    mRb = GetComponent<RigidBody>();
}

void Player::OnEarlyUpdate()
{
    if (Inputs::IsKeyPressed(SDLK_z))
    {
        mRb->AddVelocity(GetWorldTransform().GetTransform().GetForwardVector() * mSpeed * GameTime::DeltaTime);
    }
    else if (Inputs::IsKeyPressed(SDLK_s))
    {
        mRb->AddVelocity(GetWorldTransform().GetTransform().GetForwardVector() * -mSpeed * GameTime::DeltaTime);
    }
    
    if (Inputs::IsKeyPressed(SDLK_d))
    {
        mRb->AddVelocity(GetWorldTransform().GetTransform().GetRightVector() * mSpeed * GameTime::DeltaTime);
    }
    else if (Inputs::IsKeyPressed(SDLK_q))
    {
        mRb->AddVelocity(GetWorldTransform().GetTransform().GetRightVector() * -mSpeed * GameTime::DeltaTime);
    }
    
    if (const Vector2 mouseDelta = Inputs::GetMouseDelta(); mouseDelta.x != 0.0f)
    {
        Vector3 currentEuler = GetWorldTransform().GetRotation().AsMatrixRow().GetEulerRotation();
        currentEuler.z += mouseDelta.x * 1.0f * MathUtils::DEG2RAD * 0.01f;
    
        const Quaternion newRotation = Quaternion(Vector3::unitZ, currentEuler.z) * Quaternion(Vector3::unitY, currentEuler.y) * Quaternion(Vector3::unitX, currentEuler.x); 
        SetRotation(newRotation);
    }
}

Player::Player() :
    GameActor(Transform::Origin, "Player", ActorPlayer),
    mSpeed(0.0f)
{
}

Player::Player(const Transform& pTransform, float pSpeed) :
    GameActor(pTransform, "Player", ActorPlayer),
    mSpeed(pSpeed)
{
}
