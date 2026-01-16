#pragma once

#include "ActorComponent.h"
#include "Utils.h"
using Struct::Rectangle;

class BoxCollider2D : 
	public ActorComponent
{

private:
	Rectangle mBoxCollider;

public:

	BoxCollider2D(GameActor& owner, short updatePriority, Rectangle box) :
		ActorComponent(owner, updatePriority),
		mBoxCollider(box)
	{
	};

	// Inherited via ActorComponent
	void OnStart() override;
	void Update() override;
	void OnEnd() override;

	Rectangle GetBoxCollider() const;
};

