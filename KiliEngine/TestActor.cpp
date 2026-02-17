#include "TestActor.h"

void TestActor::OnEarlyUpdate()
{
	SetRotation(GetTransform().GetRotation() + Vector3::unitZ);
}
