#pragma once

#include <string>
#include "GameRenderer.h"

class Scene
{
protected:
	std::string mTitle;
	GameRenderer* mRenderer;

	inline Scene(std::string pTitle = "Scene") :
		mTitle{pTitle},
		mRenderer{nullptr}
	{
	}
public :
	
	virtual void SetRenderer(GameRenderer* pRenderer) = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnInput(SDL_Event) = 0;
	virtual void Close() = 0;
};

