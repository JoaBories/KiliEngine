#include "BowlingPin.h"

#include "GameTime.h"

void BowlingPin::OnLateUpdate()
{
    Rotate(Vector3::unitY, 1.0f * GameTime::DeltaTime);
}
