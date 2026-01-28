#pragma once

#include "Window.h"

#include "Struct.h"
using Struct::Rectangle;
using Struct::Color;
using Struct::Transform2D;

class Texture;

enum RendererType
{
	SDL,
	OpenGL
};

class IRenderer
{

public:

	virtual ~IRenderer() = default;

	virtual bool Initialize(Window& pWindow) = 0;
	virtual void Close() = 0;
	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;
	virtual void Draw() = 0;
	virtual void DrawSprites() = 0;
	virtual RendererType GetType() = 0;
};

