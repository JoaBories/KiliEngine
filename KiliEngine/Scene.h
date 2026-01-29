#pragma once

#include <string>
#include "IRenderer.h"
#include "GameActor.h"

class Scene
{
protected:
	std::string mTitle;
	IRenderer* mRenderer;

	std::vector<GameActor*> mActors;
	std::vector<GameActor*> mPendingActors;
	bool mIsUpdatingActors;

	Scene(std::string pTitle = "Scene") :
		mTitle{pTitle},
		mRenderer{nullptr},
		mActors{},
		mPendingActors{},
		mIsUpdatingActors{false}
	{
	}

public :

	static Scene* ActiveScene;

	IRenderer* GetRenderer() const { return mRenderer; };

	void UpdateAllActors();
	void RemoveActor(GameActor* actor);
	void AddActor(GameActor* actor);
	void Killa();

	void Update();
	void Render();
	void Close();
	void Start();

	void SetRenderer(IRenderer* pRenderer);

	virtual void AssetLoad() = 0;
	virtual void Unload();
	
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnClose() = 0;

	GameActor* GetActorByTag(ActorTags tag) const;
	std::vector<GameActor*> GetActorsByTag(ActorTags tag) const;

	template<typename T> T* GetActorOfClass() const
	{
		for (GameActor* a : mActors)
			if (T* actor = dynamic_cast<T*>(a)) return actor;
		return nullptr;
	};

	template<typename T> std::vector<T*> GetActorsOfClass() const
	{
		std::vector<T*> actors = {};
		for (GameActor* a : mActors)
			if (T* actor = dynamic_cast<T*>(a)) actors.push_back(actor);
		return actors;
	};
};

