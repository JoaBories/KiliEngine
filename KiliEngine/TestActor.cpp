#include "TestActor.h"
#include "GameTime.h"
#include "MathUtils.h"

using MathUtils::DEG2RAD;

void TestActor::OnEarlyUpdate()
{
	SetRotation(Quaternion::Concatenate(GetTransform().GetRotation(), Quaternion(Vector3::unitZ, GameTime::deltaTime * 60 * DEG2RAD)));
}
