#include "OpenGlRenderer.h"
#include "SpriteComponent.h"
#include "Log.h"

GlRenderer::GlRenderer() : 
    mWindow(nullptr), mVao(nullptr), 
    mContext(nullptr), mShaderProgram(nullptr),
    mViewProj(Matrix4Row::Identity)
{
}

GlRenderer::~GlRenderer()
{
}

bool GlRenderer::Initialize(Window& rWindow)
{
    mWindow = &rWindow;
    mViewProj = Matrix4Row::CreateSimpleViewProj(mWindow->GetDimensions().x, mWindow->GetDimensions().y);

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

    mVao = new VertexArray(planeVertices, 4, planeIndices, 6);
    mShaderProgram = new ShaderProgram("Simple.vert", "Simple.frag");
    
    return true;
}

void GlRenderer::BeginDraw()
{
    glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (mShaderProgram != nullptr) mShaderProgram->Use();
    mShaderProgram->setMatrix4Row("uViewProj", mViewProj);
    mVao->SetActive();
}

void GlRenderer::Draw()
{
}

void GlRenderer::DrawSprites()
{
    for (SpriteComponent* sc : mSprites)
    {
        sc->Draw(this);
    }
}

void GlRenderer::EndDraw()
{
    SDL_GL_SwapWindow(mWindow->GetSdlWindow());
}

void GlRenderer::Close()
{
    SDL_GL_DeleteContext(mContext);
    delete mVao;
}

void GlRenderer::DrawSprite(GameActor* pActor, WorldTransform pTransform, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip flip) const
{
    Matrix4Row scaleMat = Matrix4Row::CreateScale(
        pTex.GetWidth(),
        pTex.GetHeight(),
        0.0f);
    Matrix4Row world = scaleMat * pTransform.GetWorldTransformMatrix();
    
    mShaderProgram->Use();
    mShaderProgram->setMatrix4Row("uWorldTransform", world);
    pTex.SetActive();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void GlRenderer::AddSprite(SpriteComponent* pSprite)
{
    int spriteDrawOrder = pSprite->GetDrawOrder();
    std::vector<SpriteComponent*>::iterator sc;
    for (sc = mSprites.begin(); sc != mSprites.end(); ++sc)
    {
        if (spriteDrawOrder < (*sc)->GetDrawOrder()) break;
    }
    mSprites.insert(sc, pSprite);
}

void GlRenderer::RemoveSprite(SpriteComponent* pSprite)
{
    std::vector<SpriteComponent*>::iterator sc;
    sc = std::find(mSprites.begin(), mSprites.end(), pSprite);
    mSprites.erase(sc);
}

RendererType GlRenderer::GetType()
{
	return RendererType::OpenGL;
}
