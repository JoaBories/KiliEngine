#include "BowlingBall.h"

#include "GameTime.h"

void BowlingBall::OnLateUpdate()
{
    Rotate(Vector3::unitY, 1.0f * GameTime::DeltaTime);
}

void BowlingBall::OnStart()
{

}
