#include "TerrainComponent.h"

#include "Engine/Scene/SceneManager.h"
#include "Utils/Vertex.h"

// squareNumber : number of quads along each axis (8x8 → pass 8)
// squareSize  : world-space size of one quad
VertexArray* TerrainComponent::CreateTerrainVao(const int pSquareNumber, const float pSquareSize)
{
    const int vertCount = pSquareNumber + 1; 
    const float totalSize = static_cast<float>(pSquareNumber) * pSquareSize;
    const float halfSize = totalSize / 2.0f;
    
    std::vector<Vertex> vertices;
    vertices.reserve(vertCount * vertCount);
    
    for (int row = 0; row < vertCount; row++)
    {
        for (int col = 0; col < vertCount; col++)
        {
            Vertex vertex;
            vertex.Position.x = static_cast<float>(col) * pSquareSize - halfSize;
            vertex.Position.y = static_cast<float>(row) * pSquareSize - halfSize;
            
            vertex.Normal.z = 1.0f;
            
            vertex.Uv.x = static_cast<float>(col);
            vertex.Uv.y = static_cast<float>(row);
            
            vertices.push_back(vertex);
        }
    }
    
    std::vector<unsigned int> indices;
    indices.reserve(pSquareNumber * pSquareNumber * 4);
    
    for (int row = 0; row < pSquareNumber; row++)
    {
        for (int col = 0; col < pSquareNumber; col++)
        {
            unsigned int bottomLeft =   row * vertCount + col;
            unsigned int bottomRight =  row * vertCount + col + 1;
            unsigned int topRight =     (row + 1) * vertCount + col + 1;
            unsigned int topLeft =      (row + 1) * vertCount + col;

            indices.push_back(bottomLeft);
            indices.push_back(topLeft);
            indices.push_back(topRight);
            indices.push_back(bottomRight);
        }
    }

    const float* verticeInfo = ToVerticeArray(vertices);
    VertexArray* vao = new VertexArray(verticeInfo, vertices.size(), indices.data(), indices.size());
    delete[] verticeInfo;
    return vao;
}

TerrainComponent::TerrainComponent(GameActor* pOwner, const Transform& pTransform, Texture* pTexture, Texture* pHeightMap, 
                                   float pSquareSize, int pSquareNumber, const std::string& pMaterialOverride) :
    ActorComponent(pOwner, pTransform),
    mTexture(pTexture), mHeightMap(pHeightMap)
{
    if (pMaterialOverride != "Null") mMaterialName = pMaterialOverride;
    else mMaterialName = "TerrainTess";

    mVao = CreateTerrainVao(pSquareNumber, pSquareSize);
    
    SceneManager::ActiveScene()->GetRenderer()->AddTerrain(this);
}

TerrainComponent::~TerrainComponent()
{
    SceneManager::ActiveScene()->GetRenderer()->RemoveTerrain(this);
}

void TerrainComponent::Draw(Camera* pCamera, Material* pMaterial)
{
    if (IsActive())
    {
        pMaterial->SetMatrix4Row("uViewProj", pCamera->GetViewProjMatrix());
        pMaterial->SetMatrix4Row("uWorldTransform", GetWorldTransform().GetWorldTransformMatrix());
        pMaterial->SetVec2("uTilling", GetWorldTransform().GetScale().y, GetWorldTransform().GetScale().x);
        
        mTexture->SetActive();
        mVao->SetActive();
        
        glDrawElements(GL_PATCHES, mVao->GetIndiceCount(), GL_UNSIGNED_INT, nullptr);
    }
}
