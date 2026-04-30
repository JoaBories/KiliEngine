#include "PlanetMeshComponent.h"

#include "Engine/Assets/AssetManager.h"
#include "Engine/Scene/SceneManager.h"

PlanetMeshComponent::PlanetMeshComponent(
	GameActor* pOwner, const float pScale, Texture* pSeaTexture, Texture* pGroundTexture,
	const float pRotateSpeed, const float pSeaLevel, const float pReliefScale) :

	ActorComponent(pOwner, Transform(Vector3::zero, Quaternion(), Vector3::unit * pScale)),
	mPlanetMeshLod1(AssetManager::GetMesh("cube2")), // subdivided cube
	mPlanetMeshLod0(AssetManager::GetMesh("cube")),	// normal cube
	mSeaTexture(pSeaTexture), mGroundTexture(pGroundTexture),
	mRotateSpeed(pRotateSpeed), mSeaLevel(pSeaLevel), mReliefScale(pReliefScale)
{
	SetName("PlanetMesh");
	SceneManager::ActiveScene()->GetRenderer()->AddPlanetMesh(this);
}

PlanetMeshComponent::~PlanetMeshComponent()
{
	SceneManager::ActiveScene()->GetRenderer()->RemovePlanetMesh(this);
}

void PlanetMeshComponent::DrawFirst(Material* pMat) // planet
{
	pMat->SetMatrix4Row("uWorldTransform", GetWorldTransform().GetWorldTransformMatrix());
	pMat->SetVec3("uScale", GetWorldTransform().GetScale().y, GetWorldTransform().GetScale().x, GetWorldTransform().GetScale().z);
	pMat->SetFloat("uRotateSpeed", mRotateSpeed);
	pMat->SetFloat("uSeaLevel", mSeaLevel);
	pMat->SetFloat("uPerlinScale", mReliefScale);
	
	pMat->SetInt("GroundTexture", 0);
	pMat->SetInt("SeaTexture", 1);
	
	glActiveTexture(GL_TEXTURE0);
	mGroundTexture->SetActive();
	
	glActiveTexture(GL_TEXTURE1);
	mSeaTexture->SetActive();
	
	mPlanetMeshLod1->GetVertexArray()->SetActive();
	
	glDrawArrays(GL_PATCHES, 0, mPlanetMeshLod1->GetVertexArray()->GetVerticeCount());
}

void PlanetMeshComponent::DrawSecond(Material* pMat) // trees
{
	pMat->SetMatrix4Row("uWorldTransform", GetWorldTransform().GetWorldTransformMatrix());
	pMat->SetVec3("uScale", GetWorldTransform().GetScale().y, GetWorldTransform().GetScale().x, GetWorldTransform().GetScale().z);
	pMat->SetFloat("uRotateSpeed", mRotateSpeed);
	pMat->SetFloat("uSeaLevel", mSeaLevel);
	pMat->SetFloat("uPerlinScale", mReliefScale);

	//if(const Texture* texture = GetTexture()) texture->SetActive();
	
	mPlanetMeshLod0->GetVertexArray()->SetActive();
	
	glDrawArrays(GL_PATCHES, 0, mPlanetMeshLod0->GetVertexArray()->GetVerticeCount());
}
