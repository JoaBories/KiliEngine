#pragma once
#include "Engine/GameActor.h"

class BulletFx : public GameActor
{
private:
    float mTime;
	
protected:
    void OnEarlyUpdate() override;
	
public:
    BulletFx(const Transform& pTransform);
    
};
