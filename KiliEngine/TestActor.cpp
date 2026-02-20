#include "TestActor.h"
#include "GameTime.h"
#include "MathUtils.h"

using MathUtils::DEG2RAD;

void TestActor::OnEarlyUpdate()
{
	SetRotation(Quaternion::Concatenate(GetWorldTransform().GetRotation(), Quaternion(Vector3::unitZ, GameTime::DeltaTime * 60 * DEG2RAD)));
}