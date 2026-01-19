#pragma once

#include <string>
#include "GameRenderer.h"
#include "GameActor.h"

class Scene
{
protected:
	std::string mTitle;
	GameRenderer* mRenderer;
	std::vector<GameActor*> mActors;

	inline Scene(std::string pTitle = "Scene") :
		mTitle{pTitle},
		mRenderer{nullptr},
		mActors{}
	{
	}

public :

	GameRenderer* GetRenderer() const { return mRenderer; };
	
	virtual void SetRenderer(GameRenderer* pRenderer) = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnInput(SDL_Event) = 0;
	virtual void Close() = 0;
};

