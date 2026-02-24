#include "BowlingBall.h"

#include "GameTime.h"

void BowlingBall::OnLateUpdate()
{
    Rotate(Vector3::unitY, 100.0f * GameTime::DeltaTime);
    //Rotate(Vector3::unitZ, 20.0f * GameTime::DeltaTime);
}

void BowlingBall::OnStart()
{
    Rotate(Vector3::unitZ, 90.0f);
}
