#pragma once
#include "ActorComponent.h"
#include "Engine/VertexArray.h"
#include "Engine/Assets/Material.h"
#include "Engine/Assets/Texture.h"

constexpr float BillboardVertices[] = {
    0.0,  0.0, 0.0,    0.0,0.0,0.0,    0.0, 0.0,     //top left
};

class BillboardComponent : public ActorComponent
{
private:
    Texture* mTexture;
    
    static VertexArray* mVao;
    
protected:
    void OnUpdate() override {}
    
public:
    BillboardComponent() = delete;
    BillboardComponent(GameActor* pOwner,const Transform& pTransform, Texture* pTexture);
    ~BillboardComponent() override;
    void Draw(Material* pMaterial);
    
    Texture* GetTexture() const { return mTexture; }
    void SetTexture(Texture* pTexture) { mTexture = pTexture; }
    
};
