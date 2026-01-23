#pragma once

#include "ColliderComponent.h"
#include "Struct.h"
using Struct::Rectangle;

class BoxCollider2D : public ColliderComponent
{

private:
	Rectangle mBoxCollider; // center is local offset

	static std::vector<BoxCollider2D*> allBoxCollider;

public:

	BoxCollider2D(GameActor* owner, short updatePriority, Rectangle box) :
		ColliderComponent(owner, updatePriority),
		mBoxCollider(box)
	{
		allBoxCollider.push_back(this);
	};

	~BoxCollider2D() {
		for (size_t i = 0; i < allBoxCollider.size(); i++)
		{
			if (allBoxCollider.at(i) == this) 
			{
				allBoxCollider.erase(allBoxCollider.begin() + i);
			}
		}
	}

	// Inherited via ActorComponent
	void OnStart() override;
	void Update() override;
	void OnEnd() override;

	Rectangle GetBoxCollider() const;
};

