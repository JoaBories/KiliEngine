#include "OpenGlRenderer.h"

#include "AssetManager.h"
#include "SpriteComponent.h"
#include "Log.h"

GlRenderer::GlRenderer() : 
    mWindow(nullptr),
    mSpriteVao(nullptr), mSpriteShader(nullptr),
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

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
}

void GlRenderer::DrawMeshes() const
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    
    for (const auto& [shaderName, meshVector] : mMeshes)
    {
        AssetManager::GetShader(shaderName)->Use();
        for (auto& mesh : meshVector)
        {
            mesh->Draw(mCamera->GetViewProjMatrix());
        }
    }
}

void GlRenderer::DrawSprites()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (!mSpriteShader) mSpriteShader = AssetManager::GetShader("Sprite");
    mSpriteShader->Use();
    
    mSpriteShader->SetMatrix4Row("uViewProj", mSpriteViewProj);
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
    
    mSpriteShader->Use();
    mSpriteShader->SetMatrix4Row("uWorldTransform", world);
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
    const std::string shaderName = pMesh->GetMesh()->GetShaderName();
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
    const std::string shaderName = pMesh->GetMesh()->GetShaderName();
    if (mMeshes.find(shaderName) == mMeshes.end()) return;

    const auto it = std::find(mMeshes.at(shaderName).begin(), mMeshes.at(shaderName).end(), pMesh);
    if (it != mMeshes.at(shaderName).end()) mMeshes.at(shaderName).erase(it);
    if (mMeshes.at(shaderName).empty()) mMeshes.erase(shaderName);
}

RendererType GlRenderer::GetType()
{
	return OpenGl;
}
