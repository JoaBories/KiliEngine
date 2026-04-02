#include "InstanceComponent.h"

#include "Engine/Tools/GameTime.h"

InstanceComponent::InstanceComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh, const Vector2& pSize, Texture* pTextureOverride) :
    MeshComponent(pOwner, pTransform, pMesh, pTextureOverride, "InstancedGrass"),
    mSize(pSize)
{
    SetName("InstanceComponent");
}

void InstanceComponent::Draw(Camera* pCamera, Material* pMaterial)
{
    if (IsActive())
    {
        pMaterial->SetMatrix4Row("uViewProj", pCamera->GetViewProjMatrix());
        pMaterial->SetMatrix4Row("uWorldTransform", GetWorldTransform().GetWorldTransformMatrix());
        pMaterial->SetVec3("uSize", mSize.x * GetWorldTransform().GetScale().x, mSize.y * GetWorldTransform().GetScale().y, 0.0f);
        pMaterial->SetInt("uInstanceCount", 100000);
        pMaterial->SetFloat("uTime", GameTime::GetTime());

        if(const Texture* texture = GetTexture()) texture->SetActive();
	
        mMesh->GetVertexArray()->SetActive();

        glDrawArraysInstanced(GL_TRIANGLES, 0, mMesh->GetVertexArray()->GetVerticeCount(), 100000);
    }
}
