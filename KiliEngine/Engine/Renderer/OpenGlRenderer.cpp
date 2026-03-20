#include "OpenGlRenderer.h"

#include "Engine/Config.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/SpriteComponent.h"
#include "Engine/Tools/Log.h"

GlRenderer::GlRenderer() : 
    mWindow(nullptr),
    mSpriteVao(nullptr), mSpriteMaterial(nullptr),
    mSpriteViewProj(Matrix4Row::Identity),
    mContext(nullptr)
{
}

bool GlRenderer::Initialize(Window& pWindow)
{
    mWindow = &pWindow;
    mSpriteViewProj = Matrix4Row::CreateSimpleViewProj(mWindow->GetDimensions().x, mWindow->GetDimensions().y);

    //Setting OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    //8 bits color buffer
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    mContext = SDL_GL_CreateContext(mWindow->GetSdlWindow());
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        Log::Error(LogType::Video, "Failed to initialize GLEW");
        return false;
    }
    glGetError();

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        Log::Error(LogType::Video, "Failed to initialize SDL_Image");
    }

    mSpriteVao = new VertexArray(PLANE_VERTICES, 4);

    if constexpr (Cfg::FPS_LOCKED == Vsync)
    {
        SDL_GL_SetSwapInterval(1);
    }
    else
    {
        SDL_GL_SetSwapInterval(0);
    }

    glPatchParameteri(GL_PATCH_VERTICES, 3);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    const std::string glVersion = std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    Log::Info("OpenGL Version : " + glVersion);
    const std::string glslVersion = std::string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
    Log::Info("Glsl Version : " + glslVersion);
    
    return true;
}

void GlRenderer::BeginDraw()
{
    glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlRenderer::Draw()
{
    DrawMeshes();
    DrawSprites();

#ifdef _DEBUG
    DrawColliders();
#endif
}

void GlRenderer::DrawMeshes() const
{
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    
#ifdef _DEBUG
    Material* material = nullptr;
    
    switch (RenderMode)
    {
    case Uvs:
        material = AssetManager::GetMaterial("Uv");
        material->Use();
        break;
    case Normals:
        material = AssetManager::GetMaterial("Normal");
        material->Use();
        break;
    case Wireframe:        
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    default:
        break;
    }
    
    for (const auto& [materialName, meshVector] : mMeshes)
    {
        if (RenderMode == DefaultRender || RenderMode == Wireframe)
        {
            material = AssetManager::GetMaterial(materialName);
            material->Use();
        }
        
        for (auto& mesh : meshVector)
        {
            mesh->Draw(mCamera, material);
        }
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#else
    for (const auto& [materialName, meshVector] : mMeshes)
    {
        Material* material = AssetManager::GetMaterial(materialName);
        material->Use();
        
        for (auto& mesh : meshVector)
        {
            mesh->Draw(mCamera, material);
        }
    }
#endif
}

void GlRenderer::DrawSprites()
{
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    
    if (!mSpriteMaterial) mSpriteMaterial = AssetManager::GetMaterial("Sprite");
    mSpriteMaterial->Use();
    
    mSpriteMaterial->SetMatrix4Row("uViewProj", mSpriteViewProj);
    mSpriteVao->SetActive();
    
    for (SpriteComponent* sprite : mSprites)
    {
        sprite->Draw(this);
    }
}

void GlRenderer::EndDraw()
{
    SDL_GL_SwapWindow(mWindow->GetSdlWindow());
}

void GlRenderer::Close()
{
    SDL_GL_DeleteContext(mContext);
    delete mSpriteVao;
}

void GlRenderer::DrawSprite(GameActor* pActor, WorldTransform pTransform, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip pFlip) const
{
    const Matrix4Row scaleMat = Matrix4Row::CreateScale(
        static_cast<float>(pTex.GetWidth()),
        static_cast<float>(pTex.GetHeight()),
        0.0f);
    const Matrix4Row world = scaleMat * pTransform.GetWorldTransformMatrix();
    
    mSpriteMaterial->Use();
    mSpriteMaterial->SetMatrix4Row("uWorldTransform", world);
    pTex.SetActive();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void GlRenderer::AddSprite(SpriteComponent* pSprite)
{
    const int spriteDrawOrder = pSprite->GetDrawOrder();
    std::vector<SpriteComponent*>::iterator iterator;
    for (iterator = mSprites.begin(); iterator != mSprites.end(); ++iterator)
    {
        if (spriteDrawOrder < (*iterator)->GetDrawOrder()) break;
    }
    mSprites.insert(iterator, pSprite);
}

void GlRenderer::RemoveSprite(SpriteComponent* pSprite)
{
    const auto iterator = std::find(mSprites.begin(), mSprites.end(), pSprite);
    mSprites.erase(iterator);
}

void GlRenderer::AddMesh(MeshComponent* pMesh)
{
    const std::string shaderName = pMesh->GetMaterialName();
    if (mMeshes.find(shaderName) != mMeshes.end())
    {
        mMeshes.at(shaderName).push_back(pMesh);
    }
    else
    {
        mMeshes[shaderName] = {pMesh};
    }
}

void GlRenderer::RemoveMesh(const MeshComponent* pMesh)
{
    const std::string shaderName = pMesh->GetMaterialName();
    if (mMeshes.find(shaderName) == mMeshes.end()) return;

    const auto it = std::find(mMeshes.at(shaderName).begin(), mMeshes.at(shaderName).end(), pMesh);
    if (it != mMeshes.at(shaderName).end()) mMeshes.at(shaderName).erase(it);
    if (mMeshes.at(shaderName).empty()) mMeshes.erase(shaderName);
}

RendererType GlRenderer::GetType()
{
	return OpenGl;
}

#ifdef _DEBUG

RenderMode GlRenderer::RenderMode = DefaultRender;

void GlRenderer::AddCollider(ColliderComponent* pCollider)
{
    mColliders.push_back(pCollider);
}

void GlRenderer::RemoveCollider(ColliderComponent* pCollider)
{
    const auto iterator = std::find(mColliders.begin(), mColliders.end(), pCollider);
    mColliders.erase(iterator);
}

void GlRenderer::DrawColliders()
{
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);

    AssetManager::GetMaterial("Collider")->Use();
    
    for (ColliderComponent* collider : mColliders)
    {
        collider->Draw(mCamera->GetViewProjMatrix());
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

#endif
