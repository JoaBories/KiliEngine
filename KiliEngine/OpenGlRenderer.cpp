#include "OpenGlRenderer.h"

bool OpenGlRenderer::Initialize(Window& pWindow)
{
    return false;
}

void OpenGlRenderer::Close()
{
}

void OpenGlRenderer::BeginDraw()
{
}

void OpenGlRenderer::EndDraw()
{
}

void OpenGlRenderer::Draw()
{
}

void OpenGlRenderer::DrawSprites()
{
}

RendererType OpenGlRenderer::GetType()
{
    return RendererType();
}

void OpenGlRenderer::DrawSprite(GameActor* pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip flip) const
{
}
