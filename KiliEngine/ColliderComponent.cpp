#include "ColliderComponent.h"
#include "GameActor.h"
#include "RigidBody.h"

#ifdef _DEBUG
#include "SceneManager.h"
#endif

ColliderComponent::ColliderComponent(GameActor* pOwner, const Transform& pTransform, const short pUpdateOrder) :
    ActorComponent(pOwner, pTransform, pUpdateOrder)
{
#ifdef _DEBUG
    SceneManager::ActiveScene()->GetRenderer()->AddCollider(this);
#endif
}

ColliderComponent::~ColliderComponent()
{
#ifdef _DEBUG
    SceneManager::ActiveScene()->GetRenderer()->RemoveCollider(this);
#endif
}

void ColliderComponent::OnCollide(Collision pColl, ColliderComponent* pOtherCollider)
{
    if (RigidBody* rb = mOwner->GetComponent<RigidBody>())
    {
        rb->OnCollide(pColl, pOtherCollider);
    }

    mCollided = true;
}
