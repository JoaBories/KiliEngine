#pragma once

#include "ActorComponent.h"
#include "Utils.h"
using Struct::Rectangle;

class BoxCollider2D : 
	public ActorComponent
{

private:
	Rectangle mBoxCollider;

	static std::vector<BoxCollider2D*> allBoxCollider;

public:

	BoxCollider2D(GameActor& owner, short updatePriority, Rectangle box) :
		ActorComponent(owner, updatePriority),
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
	inline GameActor& GetOwner() const { return mOwner; };
};

