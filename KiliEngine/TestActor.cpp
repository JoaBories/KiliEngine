#include "TestActor.h"

void TestActor::Start()
{
}

void TestActor::Update()
{
	for (ActorComponent* comp : mComponents)
	{
		comp->Update();
	}
}
