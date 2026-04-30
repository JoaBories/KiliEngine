#include "BillboardComponent.h"

#include "Engine/Scene/SceneManager.h"

VertexArray* BillboardComponent::mVao = nullptr;

BillboardComponent::BillboardComponent(GameActor* pOwner, const Transform& pTransform, Texture* pTexture) :
    ActorComponent(pOwner, pTransform), 
    mTexture(pTexture)
{
    if (!mVao)
    {
        mVao = new VertexArray(BillboardVertices, 1);
    }
    
    SetName("BillboardComponent");
    SceneManager::ActiveScene()->GetRenderer()->AddBillboard(this);
}

BillboardComponent::~BillboardComponent()
{
    SceneManager::ActiveScene()->GetRenderer()->RemoveBillboard(this);
}

void BillboardComponent::Draw(Material* pMaterial)
{
    pMaterial->SetVec3("uPosition", GetWorldTransform().GetPosition());
    pMaterial->SetVec3("uScale", GetWorldTransform().GetScale());
    
    mVao->SetActive();
    if (mTexture)
    {
        pMaterial->SetInt("uTexture", 0);
        glActiveTexture(GL_TEXTURE0);
        mTexture->SetActive();
    }
    
    glDrawArrays(GL_POINTS, 0, 1);
}
