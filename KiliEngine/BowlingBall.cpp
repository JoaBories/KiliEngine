#include "BowlingBall.h"

#include "GameTime.h"
#include "Inputs.h"

void BowlingBall::OnLateUpdate()
{
    Rotate(Vector3::unitY, 1.0f * GameTime::DeltaTime);
    
    if (Inputs::IsKeyPressed(SDLK_UP))
    {
        AddPosition(Vector3::unitZ * 0.01f);
    }
    
    if (Inputs::IsKeyPressed(SDLK_DOWN))
    {
        AddPosition(Vector3::unitZ * -0.01f);
    }
    
    if (Inputs::IsKeyPressed(SDLK_RIGHT))
    {
        AddPosition(Vector3::unitY * 0.01f);
    }
    
    if (Inputs::IsKeyPressed(SDLK_LEFT))
    {
        AddPosition(Vector3::unitY * -0.01f);
    }
    
    if (Inputs::IsKeyPressed(SDLK_p))
    {
        AddPosition(Vector3::unitX * 0.01f);
    }
    
    if (Inputs::IsKeyPressed(SDLK_m))
    {
        AddPosition(Vector3::unitX * -0.01f);
    }
}

void BowlingBall::OnStart()
{

}
