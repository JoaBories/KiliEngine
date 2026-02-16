#include "TestActor.h"

void TestActor::OnStart()
{
}

void TestActor::OnUpdate()
{
	for (ActorComponent* comp : mComponents)
	{
		comp->Update();
	}
}
