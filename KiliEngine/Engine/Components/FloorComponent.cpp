#include "FloorComponent.h"

#include "Engine/Scene/SceneManager.h"
#include "Engine/Tools/GameTime.h"

void FloorComponent::OnUpdate()
{
}

void FloorComponent::CleanUp()
{
    delete mMesh;
}

FloorComponent::FloorComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pFloorMesh) :
    MeshComponent(pOwner, pTransform, pFloorMesh)
{
    SetName("FloorComponent");
}

void FloorComponent::Draw(Camera* pCamera, Material* pMaterial)
{
    if (IsActive())
    {
        pMaterial->SetMatrix4Row("uViewProj", pCamera->GetViewProjMatrix());
        pMaterial->SetMatrix4Row("uWorldTransform", GetWorldTransform().GetWorldTransformMatrix());
        pMaterial->SetVec3("uScale", GetWorldTransform().GetScale().x, GetWorldTransform().GetScale().y, 0.0f);

        if(const Texture* texture = GetTexture()) texture->SetActive();
	
        mMesh->GetVertexArray()->SetActive();

        glDrawArrays(GL_TRIANGLE_FAN, 0, mMesh->GetVertexArray()->GetVerticeCount());
    }
}
