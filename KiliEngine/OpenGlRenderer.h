#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "glew.h"

class SpriteComponent;

class GlRenderer : public IRenderer
{
private:
	Window* mWindow;
	VertexArray* mVao;
	ShaderProgram* mShaderProgram;

	SDL_GLContext mContext;
	std::vector<SpriteComponent*> mSprites;
public:
	GlRenderer();

	virtual ~GlRenderer();
	GlRenderer(const GlRenderer&) = delete;
	GlRenderer& operator=(const GlRenderer&) = delete;

	bool Initialize(Window& rWindow) override;
	void BeginDraw() override;
	void Draw() override;
	void DrawSprites() override;
	void EndDraw() override;
	void Close() override;

	void DrawSprite(GameActor* pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip flip) const override{};
	void AddSprite(SpriteComponent* pSprite);
	void RemoveSprite(SpriteComponent* pSprite);
	RendererType GetType() override;
};
