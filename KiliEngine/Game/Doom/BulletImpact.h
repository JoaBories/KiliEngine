#pragma once
#include "Engine/GameActor.h"

class BulletImpact : public GameActor
{
private:
	float mTime;
	
protected:
	void OnEarlyUpdate() override;
	
public:
	BulletImpact(const Transform& pTransform);
	
};
